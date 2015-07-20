#include "jit.h"
#include "amd64.h"
#include "codegenerator.h"
#include "type.h"
#include "typechecker.h"
#include "vmstate.h"
#include "binder.h"
#include "function.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <assert.h>

BranchTarget::BranchTarget(unsigned int target, unsigned int instructionSize)
	: target(target), instructionSize(instructionSize) {

}

UnresolvedFunctionCall::UnresolvedFunctionCall(FunctionCallType type, std::string functionName, std::size_t callOffset)
	: type(type), functionName(functionName), callOffset(callOffset) {

}

bool UnresolvedFunctionCall::operator<(const UnresolvedFunctionCall& rhs) const {
	if (functionName < rhs.functionName) {
		return true;
	} else if (functionName > rhs.functionName) {
		return true;
	} else {
		return callOffset < rhs.callOffset;
	}
}

bool UnresolvedFunctionCall::operator==(const UnresolvedFunctionCall& rhs) const {
	return functionName == rhs.functionName && callOffset == rhs.callOffset;
}

UnresolvedFunctionCall::Hash_t UnresolvedFunctionCall::Hash = [](const UnresolvedFunctionCall& call) {
	return std::hash<std::string>()(call.functionName) + call.callOffset;
};

FunctionCompilationData::FunctionCompilationData(Function& function)
    : function(function), unresolvedCalls(7, UnresolvedFunctionCall::Hash), operandStackSize(0) {

}

JITCompiler::JITCompiler(VMState& vmState)
	: mVMState(vmState), mCodeGen(mCallingConvention, mExceptionHandling) {
	mExceptionHandling.generateHandlers(mMemoryManager);
	createMacros();
}

MemoryManager& JITCompiler::memoryManager() {
    return mMemoryManager;
}

void JITCompiler::createMacros() {
	auto& binder = mVMState.binder();
	auto voidType = mVMState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));
	binder.define(FunctionDefinition("std.gc.collect", {}, voidType, [this](MacroFunctionContext context) {
		auto& function = context.functionData.function;
		mCodeGen.generateGCCall(function.generatedCode, function, context.instIndex);
	}));
}

JitFunction JITCompiler::generateFunction(Function* function) {
	auto signature = mVMState.binder().functionSignature(*function);
	mFunctions.emplace(signature, FunctionCompilationData(*function));
	auto& functionData = mFunctions.at(signature);

    functionData.operandStackSize = function->operandStackSize();
    
    //Initialize the function
    mCodeGen.initializeFunction(functionData);

    //Generate the native instructions for the program
    int i = 0;
    for (auto current : function->instructions) {
        mCodeGen.generateInstruction(functionData, mVMState, current, i);
        i++;
    }

    //Patch branches with the native targets
    resolveBranches(functionData);

    //Get a pointer & size of the generated instructions
    unsigned char* code = function->generatedCode.data();
    std::size_t length = function->generatedCode.size();

    if (mVMState.enableDebug) {
        std::string argsStr = "";
        bool isFirst = true;

        for (auto param : function->parameters()) {
            if (isFirst) {
                isFirst = false;
            } else {
                argsStr += " ";
            }

            argsStr += TypeChecker::typeToString(param);
        }

        std::cout
            << "Generated function '" << function->name() << "(" + argsStr + ") " << TypeChecker::typeToString(function->returnType())
            << "' of size " << length << " bytes."
            << std::endl;
    }

    //Indicates if to output the generated code to a file
    if (mVMState.outputGeneratedCode) {
        std::ofstream asmFile (function->name() + ".jit", std::ios::binary);

        if (asmFile.is_open()) {
            asmFile.write((char*)code, length);
            asmFile.close();
        }
    }

    //Allocate writable and readable memory
    void* mem = mMemoryManager.allocateMemory(length);

    //Copy the instructions
    memcpy(mem, code, length);

    //Return the generated instructions as a function pointer
    return (JitFunction)mem;
}


void JITCompiler::resolveBranches(FunctionCompilationData& functionData) {
	auto& function = functionData.function;

	//Resolve managed branches
	for (auto branch : functionData.unresolvedBranches) {
		unsigned int source = branch.first;
		auto branchTarget = branch.second;

		unsigned int nativeTarget = functionData.instructionNumMapping[branchTarget.target];

		//Calculate the native jump location
		IntToBytes converter;
		converter.intValue = nativeTarget - source - branchTarget.instructionSize;

		unsigned int sourceOffset = branchTarget.instructionSize - sizeof(int);

		//Update the source with the native target
		for (std::size_t i = 0; i < sizeof(int); i++) {
			function.generatedCode[source + sourceOffset + i] = converter.byteValues[i];
		}
	}

	functionData.unresolvedBranches.clear();
}

void JITCompiler::resolveNativeBranches(FunctionCompilationData& functionData) {
	auto& function = functionData.function;

	//Get a pointer to the functions native instructions
	auto funcSignature = mVMState.binder().functionSignature(function);
	unsigned char* funcCodePtr = (unsigned char*)mVMState.binder().getFunction(funcSignature).entryPoint();

	//Resolved native branches
	for (auto branch : functionData.unresolvedNativeBranches) {
		auto source = branch.first;
		auto target = branch.second;

		//Calculate the native jump location
		IntToBytes converter;
		converter.intValue = target - ((long)funcCodePtr + source) - 6;

		unsigned int sourceOffset = 6 - sizeof(int);

		//Update the source with the native target
		for (std::size_t i = 0; i < sizeof(int); i++) {
			funcCodePtr[source + sourceOffset + i] = converter.byteValues[i];
		}
	}

	functionData.unresolvedNativeBranches.clear();
}

void JITCompiler::resolveCallTargets(FunctionCompilationData& functionData) {
	for (auto call : functionData.unresolvedCalls) {
		auto callType = call.first.type;
		auto funcName = call.first.functionName;
		auto offset = call.first.callOffset;
		auto calledFunc = call.second;

		//The address of the called function
		long calledFuncAddr = mVMState.binder().getFunction(calledFunc).entryPoint();

		//Get a pointer to the functions native instructions
		unsigned char* funcCodePtr = (unsigned char*)(mVMState.binder().getFunction(funcName).entryPoint());

		//Update the call target
		if (callType == FunctionCallType::Absolute) {
			LongToBytes converter;
			converter.longValue = calledFuncAddr;

			std::size_t base = offset + 2;
			for (std::size_t i = 0; i < sizeof(long); i++) {
				funcCodePtr[base + i] = converter.byteValues[i];
			}
		} else if (callType == FunctionCallType::Relative) {
			IntToBytes converter;
			converter.intValue = (int)(calledFuncAddr - ((long)funcCodePtr + offset + 5));

			std::size_t base = offset + 1;
			for (std::size_t i = 0; i < sizeof(int); i++) {
				funcCodePtr[base + i] = converter.byteValues[i];
			}
		}
	}

	functionData.unresolvedCalls.clear();
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
       	auto signature = mVMState.binder().functionSignature(funcData.function);

        if (funcData.unresolvedCalls.size() > 0) {
            throw std::runtime_error("The function '" + signature + "' has unresolved calls.");
	    }
    }

    //Make the functions memory executable, but not writable.
    mMemoryManager.makeMemoryExecutable();
}