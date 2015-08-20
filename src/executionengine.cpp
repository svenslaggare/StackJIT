#include "executionengine.h"
#include "vmstate.h"
#include "binder.h"
#include "function.h"
#include "verifier.h"
#include "type.h"
#include "loader.h"
#include "native.h"
#include "test.h"

#include <iostream>
#include <stdexcept>
#include <fstream>

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

void ExecutionEngine::setBaseDir(std::string baseDir) {
	mBaseDir = baseDir;
}

EntryPointFunction ExecutionEngine::entryPoint() const {
    if (mVMState.binder().isDefined("main()")) {
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

bool ExecutionEngine::loadLibrary(std::string filePath) {
	std::ifstream fileStream(filePath);

	if (!fileStream.is_open()) {
		std::cout << "Could not load library '" << filePath << "'." << std::endl;
		return false;
	}

	auto lib = new AssemblyParser::Assembly;
	Loader::load(fileStream, mVMState, *lib);
	loadAssembly(*lib, AssemblyType::Library);
	return true;
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

void ExecutionEngine::loadRuntimeLibrary() {
	if (mVMState.loadRuntimeLibrary) {
		bool loaded = false;

		loaded = loadLibrary(mBaseDir + "rtlib/native.sbc");
		loaded = loadLibrary(mBaseDir + "rtlib/string.sbc");

		if (!loaded) {
			throw std::runtime_error("Could not load runtime library.");
		}
	}
}

void ExecutionEngine::load() {
	auto& binder = mVMState.binder();

	//Load runtime library
	loadRuntimeLibrary();

	//Load classes
	Loader::loadClasses(mVMState, mAssemblies);

	//Load native functions
	NativeLibrary::add(mVMState);

	if (mVMState.testMode) {
		//Load test functions
		TestLibrary::add(mVMState);
	}

	//Load functions
	for (auto assembly : mAssemblies) {
		for (auto& currentFunc : assembly->functions) {
			FunctionDefinition funcDef;

			if (!currentFunc.isExternal) {
				auto func = Loader::loadManagedFunction(mVMState, currentFunc);

				mLoadedFunctions.insert({ binder.functionSignature(*func), func });

				funcDef = FunctionDefinition(
					func->name(),
					func->parameters(),
					func->returnType(),
					func->isMemberFunction());
			} else {
				Loader::loadExternalFunction(mVMState, currentFunc, funcDef);
			}

			binder.define(funcDef);
		}
	}
}

void ExecutionEngine::loadDefinitions() {
	auto& binder = mVMState.binder();

	//Load runtime library
	loadRuntimeLibrary();

	//Load classes
	Loader::loadClasses(mVMState, mAssemblies);

	//Load native functions
	NativeLibrary::add(mVMState);

	if (mVMState.testMode) {
		//Load test functions
		TestLibrary::add(mVMState);
	}

	//Load functions
	for (auto assembly : mAssemblies) {
		for (auto& currentFunc : assembly->functions) {
			FunctionDefinition funcDef;

			if (!currentFunc.isExternal) {
				Loader::generateDefinition(mVMState, currentFunc, funcDef);

				auto signature = binder.functionSignature(funcDef);
				if (binder.isDefined(signature)) {
					throw std::runtime_error("The function '" + signature + "' is already defined.");
				}

				mLoadedDefinitions.insert({ signature, currentFunc });
			} else {
				Loader::loadExternalFunction(mVMState, currentFunc, funcDef);
			}

			binder.define(funcDef);
		}
	}
}

void ExecutionEngine::compileFunction(Function* function, std::string signature, bool resolveSymbols) {
	//Type check the function
	Verifier::verifyFunction(*function, mVMState);

	//Compile it
	auto funcPtr = mJIT.compileFunction(function);

	if (mVMState.enableDebug && mVMState.printFunctionGeneration) {
		std::cout
			<< "Defined function '" << function->name() << "' at 0x" << std::hex << (PtrValue)funcPtr << std::dec << "."
			<< std::endl;
	}

	if (signature == "") {
		signature = mVMState.binder().functionSignature(*function);
	}

	//Set the entry point & size for the function
	mVMState.binder().getFunction(signature).setEntryPoint((unsigned char*)funcPtr);

	if (resolveSymbols) {
		//Fix unresolved symbols
		mJIT.resolveSymbols(signature);
	}
}

bool ExecutionEngine::compileFunction(std::string signature) {
	if (mLoadedDefinitions.count(signature) > 0 && !mJIT.hasCompiled(signature)) {
		//Load the function
		auto funcDef = mLoadedDefinitions[signature];
		auto func = Loader::loadManagedFunction(mVMState, funcDef, false);
		mLoadedFunctions.insert({ mVMState.binder().functionSignature(*func), func });

		//Compile it
		compileFunction(func, signature, true);
		return true;
	}

	return false;
}

void ExecutionEngine::generateCode() {
	//Generate instructions for all functions
	for (auto loadedFunc : mLoadedFunctions) {
		compileFunction(loadedFunc.second);
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
