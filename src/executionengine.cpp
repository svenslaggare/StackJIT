#include "executionengine.h"
#include "vmstate.h"
#include "binder.h"
#include "assembly.h"
#include "function.h"
#include "verifier.h"
#include "type.h"
#include "loader.h"

#include <iostream>
#include <stdexcept>

CallStackEntry::CallStackEntry(Function* function, int callPoint)
	: function(function), callPoint(callPoint) {

}

CallStackEntry::CallStackEntry()
	: function(nullptr), callPoint(0) {

}

CallStack::CallStack(std::size_t size)
	: mSize(size), mStart(new CallStackEntry[size]), mTop(mStart) {

}

CallStack::~CallStack() {
	delete[] mStart;
}

void CallStack::push(Function* function, int callPoint) {
	if (mTop + 1 < mStart + mSize) {
		mTop++;
		*mTop = CallStackEntry(function, callPoint);
	} else {
		throw std::runtime_error("Stack overflow.");
	}
}

CallStackEntry CallStack::pop() {
	if (mTop == mStart) {
		throw std::runtime_error("Stack underflow.");
	}

	auto top = *mTop;
	mTop--;
	return top;
}

std::size_t CallStack::size() const {
	return mSize;
}

CallStackEntry* CallStack::start() {
	return mStart;
}

CallStackEntry* const CallStack::start() const {
	return mStart;
}

CallStackEntry* CallStack::top() {
	return mTop;
}

CallStackEntry* const * const CallStack::topPtr() const {
	return &mTop;
}

ExecutionEngine::ExecutionEngine(VMState& vmState)
	: mVMState(vmState), mJIT(vmState), mCallStack(2000) {

}

ExecutionEngine::~ExecutionEngine() {
	for (auto assembly : mAssemblies) {
		delete assembly;
	}

	for (auto func : mLoadedFunctions) {
		delete func.second;
	}
}

JITCompiler& ExecutionEngine::jitCompiler() {
	return mJIT;
}


const JITCompiler& ExecutionEngine::jitCompiler() const {
	return mJIT;
}

EntryPointFunction ExecutionEngine::entryPoint() const {
    if (mVMState.binder().isDefined("main()") > 0) {
        return (EntryPointFunction)(mVMState.binder().getFunction("main()").entryPoint());
    } else {
        throw std::runtime_error("No entry point has been defined.");
    }
}

//Returns the function with the given name
AssemblyParser::Function* getFunction(AssemblyParser::Assembly& assembly, std::string funcName) {
	for (auto& func : assembly.functions) {
		if (func.name == funcName) {
			return &func;
		}
	}

	return nullptr;
}

void ExecutionEngine::loadAssembly(AssemblyParser::Assembly& assembly, AssemblyType assemblyType) {
    if (assemblyType == AssemblyType::Program) {
		auto mainFunc = getFunction(assembly, "main");

		if (mainFunc != nullptr) {
			if (!(mainFunc->parameters.size() == 0
				  && mainFunc->returnType == TypeSystem::toString(PrimitiveTypes::Integer))) {
				throw std::runtime_error("The main function must have the following signature: 'main() Int'.");
			}
		} else {
			throw std::runtime_error("The main function must be defined.");
		}
    }

	//Add the loaded assembly
	mAssemblies.push_back(&assembly);
}

void ExecutionEngine::load() {
	//Load classes
	Loader::loadClasses(mVMState, mAssemblies);

	auto& binder = mVMState.binder();

	//Load functions
	for (auto assembly : mAssemblies) {
		for (auto& currentFunc : assembly->functions) {
			auto func = Loader::loadFunction(mVMState, currentFunc);

			if (!currentFunc.isExternal) {
				mLoadedFunctions.insert({ binder.functionSignature(*func), func });
			}

			FunctionDefinition funcDef(
				func->name(),
				func->parameters(),
				func->returnType(),
				func->isMemberFunction());

			binder.define(funcDef);
		}
	}
}

bool ExecutionEngine::compileFunction(std::string signature) {
	if (mLoadedFunctions.count(signature) > 0 && !mJIT.hasCompiled(signature)) {
		auto func = mLoadedFunctions[signature];

		//Type check the function
		Verifier::verifyFunction(*func, mVMState);

		auto funcPtr = mJIT.compileFunction(func);

		if (mVMState.enableDebug && mVMState.printFunctionGeneration) {
			std::cout <<
			"Defined function '" << func->name() << "' at 0x" << std::hex << (long)funcPtr << std::dec << "."
			<< std::endl;
		}

		//Set the entry point & size for the function
		mVMState.binder().getFunction(signature).setEntryPoint((long)funcPtr);

		//Fix unresolved symbols
		mJIT.resolveSymbols(signature);

		return true;
	}

	return false;
}

void ExecutionEngine::generateCode() {
	//Generate instructions for all functions
	for (auto loadedFunc : mLoadedFunctions) {
		auto func = loadedFunc.second;

		//Type check the function
		Verifier::verifyFunction(*func, mVMState);

		auto funcPtr = mJIT.compileFunction(func);

		if (mVMState.enableDebug && mVMState.printFunctionGeneration) {
			std::cout <<
			"Defined function '" << func->name() << "' at 0x" << std::hex << (long)funcPtr << std::dec << "."
			<< std::endl;
		}

		auto signature = mVMState.binder().functionSignature(func->name(), func->parameters());

		//Set the entry point & size for the function
		mVMState.binder().getFunction(signature).setEntryPoint((long)funcPtr);
	}

	//Fix unresolved symbols
	mJIT.resolveSymbols();
}

void ExecutionEngine::compile() {
	load();
	generateCode();
    mJIT.makeExecutable();
}

CallStack& ExecutionEngine::callStack() {
	return mCallStack;
}

const CallStack& ExecutionEngine::callStack() const {
	return mCallStack;
}
