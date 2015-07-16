#include "executionengine.h"
#include "vmstate.h"
#include "binder.h"
#include "assembly.h"
#include "function.h"
#include "typechecker.h"
#include "type.h"
#include "loader.h"

#include <iostream>
#include <stdexcept>

ExecutionEngine::ExecutionEngine(VMState& vmState)
	: mVMState(vmState), mJIT(vmState) {

}

ExecutionEngine::~ExecutionEngine() {
	for (auto assembly : mAssemblies) {
		delete assembly;
	}

	for (auto func : mLoadedFunctions) {
		delete func;
	}
}

EntryPointFunction ExecutionEngine::entryPoint() const {
    if (mVMState.binder().isDefined("main()") > 0) {
        return (EntryPointFunction)(mVMState.binder()["main()"].entryPoint());
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
	//Load structs
	Loader::loadStructs(mVMState, mAssemblies);

	//Load functions
	for (auto assembly : mAssemblies) {
		for (auto& currentFunc : assembly->functions) {
			auto func = Loader::loadFunction(mVMState, currentFunc);

			if (!currentFunc.isExternal) {
				mLoadedFunctions.push_back(func);
			}

			FunctionDefinition funcDef(
				func->name(),
				func->parameters(),
				func->returnType(),
				0, 0, func->isMemberFunction());

			auto& binder = mVMState.binder();
			binder.define(funcDef);
		}
	}
}

void ExecutionEngine::generateCode() {
	//Generate instructions for all functions
	for (auto func : mLoadedFunctions) {
		//Type check the function
		TypeChecker::typeCheckFunction(*func, mVMState, mVMState.enableDebug && mVMState.printTypeChecking);

		auto funcPtr = mJIT.generateFunction(func);

		if (mVMState.enableDebug) {
			std::cout <<
			"Defined function '" << func->name() << "' at 0x" << std::hex << (long)funcPtr << std::dec << "."
			<< std::endl;
		}

		auto signature = mVMState.binder().functionSignature(func->name(), func->parameters());

		//Set the entry point & size for the function
		mVMState.binder().getFunction(signature).setFunctionBody((long)funcPtr, (int)func->generatedCode.size());
	}

	//Fix unresolved symbols
	mJIT.resolveSymbols();
}

void ExecutionEngine::compile() {
	load();
	generateCode();
    mJIT.makeExecutable();
}

const std::deque<CallStackEntry>& ExecutionEngine::callStack() const {
    return mCallStack;
}

CallStackEntry ExecutionEngine::popFunc() {
    auto top = std::make_pair(mCallStack.front().first, mCallStack.front().second);
    mCallStack.pop_front();
    return top;
}

void ExecutionEngine::pushFunc(Function* func, int instIndex) {
    auto newEntry = std::make_pair(func, instIndex);
    mCallStack.push_front(newEntry);
}