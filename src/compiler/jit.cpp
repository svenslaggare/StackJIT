#include "jit.h"
#include "memory.h"
#include "binder.h"
#include "x64/codegenerator.h"
#include "../vmstate.h"
#include "../helpers.h"
#include "../type/type.h"
#include "../core/function.h"
#include "../core/functionsignature.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>

namespace stackjit {
	JITCompiler::JITCompiler(VMState& vmState)
		: mVMState(vmState), mCodeGenerator(mCallingConvention, mExceptionHandling) {
		mExceptionHandling.generateHandlers(mMemoryManager, mCallingConvention);
		createMacros();
	}

	MemoryManager& JITCompiler::memoryManager() {
		return mMemoryManager;
	}

	void JITCompiler::createMacros() {
		auto& binder = mVMState.binder();
		auto voidType = mVMState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

		FunctionDefinition collectDef("std.gc.collect", {}, voidType);
		if (binder.define(collectDef)) {
			mCodeGenerator.defineMacro(collectDef, [this](MacroFunctionContext context) {
				auto& function = context.functionData.function;
				mCodeGenerator.generateGCCall(function.generatedCode(), function, context.instructionIndex);
			});
		}

		FunctionDefinition collectGenerationDef("std.gc.collectOld", {}, voidType);
		if (binder.define(collectGenerationDef)) {
			mCodeGenerator.defineMacro(collectGenerationDef, [this](MacroFunctionContext context) {
				auto& function = context.functionData.function;
				mCodeGenerator.generateGCCall(function.generatedCode(), function, context.instructionIndex, 1);
			});
		}
	}

	bool JITCompiler::hasCompiled(std::string signature) const {
		return mFunctions.count(signature) > 0;
	}

	const std::unordered_map<std::string, FunctionCompilationData>& JITCompiler::functions() const {
		return mFunctions;
	}

	JitFunction JITCompiler::compileFunction(ManagedFunction* function) {
		auto signature = FunctionSignature::from(function->def()).str();
		mFunctions.emplace(signature, *function);
		auto& functionData = mFunctions.at(signature);

		//Initialize the function
		mCodeGenerator.generateInitializeFunction(functionData);

		//Generate the native instructions for the program
		int i = 0;
		for (auto& current : function->instructions()) {
			mCodeGenerator.generateInstruction(mVMState, functionData, current, i);
			i++;
		}

		//Patch branches with the native targets
		resolveBranches(functionData);

		//Get a pointer & size of the generated instructions
		auto codePtr = function->generatedCode().data();
		auto size = function->generatedCode().size();

		if (mVMState.config.enableDebug && mVMState.config.printFunctionGeneration) {
			auto funcSignature = FunctionSignature::from(function->def()).str();
			std::cout
				<< "Generated function '" << funcSignature << " " << function->def().returnType()->name()
				<< "' of size " << size << " bytes."
				<< std::endl;
		}

		//Indicates if to output the generated code to a file
		if (mVMState.config.outputGeneratedCode) {
			std::ofstream asmFile(function->def().name() + ".jit", std::ios::binary);

			if (asmFile.is_open()) {
				asmFile.write((char*)codePtr, size);
				asmFile.close();
			}
		}

		//Allocate writable and readable memory
		auto memory = mMemoryManager.allocateMemory(size);

		//Copy the instructions
		std::memcpy(memory, codePtr, size);

		//Return the generated instructions as a function pointer
		return (JitFunction)memory;
	}

	void JITCompiler::resolveBranches(FunctionCompilationData& functionData) {
		auto& function = functionData.function;

		//Resolve managed branches
		for (auto branch : functionData.unresolvedBranches) {
			auto source = branch.first;
			auto branchTarget = branch.second;

			auto nativeTarget = functionData.instructionNumMapping[branchTarget.target];

			//Calculate the native jump location
			auto target = (int)nativeTarget - (int)source - (int)branchTarget.instructionSize;

			//Update the source with the native target
			auto sourceOffset = (int)source + (int)branchTarget.instructionSize - sizeof(int);
			Helpers::setValue(function.generatedCode(), sourceOffset, target);
		}

		functionData.unresolvedBranches.clear();
	}

	void JITCompiler::resolveNativeBranches(FunctionCompilationData& functionData) {
		//Get a pointer to the functions native instructions
		auto codePtr = functionData.function.def().entryPoint();

		//Resolved native branches
		for (auto branch : functionData.unresolvedNativeBranches) {
			auto source = branch.first;
			auto target = branch.second;

			//Calculate the native jump location
			auto nativeTarget = (int)(target - (PtrValue)(codePtr + source) - 6);

			//Update the source with the native target
			auto sourceOffset = source + 6 - sizeof(int);
			Helpers::setValue(codePtr, sourceOffset, nativeTarget);
		}

		functionData.unresolvedNativeBranches.clear();
	}

	void JITCompiler::resolveCallTargets(FunctionCompilationData& functionData) {
		//Get a pointer to the functions native instructions
		auto codePtr = functionData.function.def().entryPoint();

		for (auto& unresolvedCall : functionData.unresolvedCalls) {
			auto callType = unresolvedCall.type;
			auto offset = unresolvedCall.callOffset;

			//The address of the called function
			auto calledFuncPtr = unresolvedCall.funcToCall.entryPoint();

			//Update the call target
			if (callType == FunctionCallType::Absolute) {
				Helpers::setValue(codePtr, offset + 2, calledFuncPtr);
			} else if (callType == FunctionCallType::Relative) {
				int target = (int)(calledFuncPtr - (codePtr + offset + 5));
				Helpers::setValue(codePtr, offset + 1, target);
			}
		}

		functionData.unresolvedCalls.clear();
	}

	void JITCompiler::resolveSymbols(std::string signature) {
		if (mFunctions.count(signature) > 0) {
			auto& func = mFunctions.at(signature);
			resolveCallTargets(func);
			resolveNativeBranches(func);
		}
	}

	void JITCompiler::resolveSymbols() {
		for (auto& funcEntry : mFunctions) {
			resolveCallTargets(funcEntry.second);
			resolveNativeBranches(funcEntry.second);
		}
	}

	void JITCompiler::makeExecutable() {
		//Check that all calls has been resolved
		for (auto& funcEntry : mFunctions) {
			auto& funcData = funcEntry.second;
			auto signature = FunctionSignature::from(funcData.function.def()).str();

			if (funcData.unresolvedCalls.size() > 0) {
				throw std::runtime_error("The function '" + signature + "' has unresolved calls.");
			}
		}

		//Make the functions memory executable, but not writable.
		mMemoryManager.makeMemoryExecutable();
	}
}
