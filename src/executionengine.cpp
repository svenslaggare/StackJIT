#include "executionengine.h"
#include "vmstate.h"
#include "core/function.h"
#include "type/type.h"
#include "loader/functionloader.h"
#include "loader/classloader.h"
#include "bytecode/bytecodeparser.h"
#include "runtime/native.h"
#include "test/test.h"
#include "core/functionsignature.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

namespace stackjit {
	ExecutionEngine::ExecutionEngine(VMState& vmState)
		: mVMState(vmState),
		  mJIT(vmState),
		  mCallStack(2000),
		  mVerifier(vmState),
		  mFunctionLoader(vmState),
		  mClassLoader(vmState) {

	}

	ExecutionEngine::~ExecutionEngine() {
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
	    if (mVMState.binder().isDefined(stackjit::ENTRY_POINT_SIGNATURE)) {
	        return (EntryPointFunction)(mVMState.binder().getFunction(stackjit::ENTRY_POINT_SIGNATURE).entryPoint());
	    } else {
	        throw std::runtime_error("No entry point has been defined.");
	    }
	}

	//Returns the function with the given name inside the given image
	const Loader::Function* getFunction(AssemblyImage& image, std::string funcName) {
		for (auto& current : image.functions()) {
			auto& func = current.second;
			if (func.name() == funcName) {
				return &func;
			}
		}

		return nullptr;
	}

	void ExecutionEngine::loadImage(AssemblyImage* image, AssemblyType assemblyType) {
		if (assemblyType == AssemblyType::Program) {
			auto mainFunc = getFunction(*image, "main");

			if (mainFunc != nullptr) {
				if (!(mainFunc->parameters().size() == 0
					  && mainFunc->returnType() == TypeSystem::toString(PrimitiveTypes::Integer))) {
					throw std::runtime_error("The main function must have the signature: 'main() Int' but got '" + mainFunc->toString() + "'.");
				}
			} else {
				throw std::runtime_error("The main function must be defined.");
			}
		}

		mImageContainer.addImage(image);
	}

	void ExecutionEngine::loadImage(std::ifstream& stream, AssemblyType assemblyType) {
		stream.seekg(0, std::ios::end);
		auto size = (std::size_t)stream.tellg();
		stream.seekg(0, std::ios::beg);

		BinaryData imageData(size);
		if (!stream.read(imageData.data(), size)) {
			throw std::runtime_error("Could not load the image.");
		}

		auto image = new AssemblyImage();
		AssemblyImageLoader::load(imageData, *image);
		loadImage(image, assemblyType);
	}

	void ExecutionEngine::loadAssembly(Loader::Assembly& assembly, AssemblyType assemblyType) {
	    loadImage(new AssemblyImage(assembly), assemblyType);
	}

	bool ExecutionEngine::loadAssembly(std::string filePath, AssemblyType assemblyType) {
		std::ios::openmode openMode = std::ios::in;

		if (filePath.find(".simg") != std::string::npos) {
			openMode = std::ios::binary;
		}

		std::ifstream fileStream(filePath, openMode);

		if (!fileStream.is_open()) {
			std::cout << "Could not load the assembly '" << filePath << "'." << std::endl;
			return false;
		}

		if (openMode == std::ios::binary) {
			loadImage(fileStream, assemblyType);
		} else {
			Loader::Assembly assembly(assemblyType == AssemblyType::Program ? "program": "library");
			Loader::load(fileStream, assembly);
			loadAssembly(assembly, assemblyType);
		}

		return true;
	}

	void ExecutionEngine::loadRuntimeLibrary() {
		if (mVMState.config.loadRuntimeLibrary) {
			bool loaded = loadAssembly(mBaseDir + "rtlib/rtlib.simg");

			if (!loaded) {
				throw std::runtime_error("Could not load the runtime library.");
			}
		}
	}

	void ExecutionEngine::load(bool loadFunctionBodies) {
		auto& binder = mVMState.binder();

		if (!mHasMainInitialized) {
			//Load runtime library
			loadRuntimeLibrary();
		}

		//Load classes
		mClassLoader.loadClasses(mImageContainer);

		if (!mHasMainInitialized) {
			//Load native functions
			NativeLibrary::add(mVMState);

			//Load test functions
			if (mVMState.config.testMode) {
				TestLibrary::add(mVMState);
			}

			mHasMainInitialized = true; //Mark that the main initialization has been made
		}

		//Load functions
		for (auto& image : mImageContainer.images()) {
			if (image->hasLoadedDefinitions()) {
				continue;
			}

			for (auto& current : image->functions()) {
				auto& currentFunc = current.second;
				FunctionDefinition funcDef;

				if (loadFunctionBodies) {
					image->loadFunctionBody(current.first);
				}

				if (!currentFunc.isExternal()) {
					mFunctionLoader.generateDefinition(currentFunc, funcDef);

					auto signature = FunctionSignature::from(funcDef).str();
					if (binder.isDefined(signature)) {
						throw std::runtime_error("The function '" + signature + "' is already defined.");
					}
				} else {
					mFunctionLoader.loadExternal(currentFunc, funcDef);
				}

				binder.define(funcDef);

				//Add virtual functions to the class
				if (funcDef.isVirtual()) {
					funcDef.classType()->metadata()->addVirtualFunction(binder.getFunction(current.first));
				}
			}

			image->loadedDefinitions();
		}

		//Create virtual function tables
		mVMState.classProvider().createVirtualFunctionTables(mVMState);
	}

	JitFunction ExecutionEngine::compileFunction(ManagedFunction* function, bool resolveSymbols) {
		//Type check the function
		mVerifier.verifyFunction(*function);

		//Compile it
		auto funcPtr = mJIT.compileFunction(function);

		if (mVMState.config.enableDebug && mVMState.config.printFunctionGeneration) {
			std::cout
				<< "Defined function '" << function->def().name()
				<< "' at 0x" << std::hex << (PtrValue)funcPtr << std::dec << "."
				<< std::endl;
		}

		auto signature = FunctionSignature::from(function->def()).str();

		//Set the entry point & size for the function
		mVMState.binder().getFunction(signature).setEntryPoint((BytePtr)funcPtr);

		//Fix unresolved symbols
		if (resolveSymbols) {
			mJIT.resolveSymbols(signature);
		}

		//If virtual, bind to virtual func table.
		if (function->def().isVirtual()) {
			function->def().classType()->metadata()->bindVirtualFunction(
				function->def(),
				(BytePtr)funcPtr);
		}

		return funcPtr;
	}

	bool ExecutionEngine::compileFunction(const std::string& signature, JitFunction& entryPoint) {
		auto funcImage = mImageContainer.getFunction(signature);

		if (funcImage != nullptr && !mJIT.hasCompiled(signature)) {
			auto& funcDef = mVMState.binder().getFunction(signature);

			//Load the function
			mImageContainer.loadFunctionBody(signature);
			auto func = mFunctionLoader.loadManaged(*funcImage, funcDef);
			mLoadedFunctions.insert({ FunctionSignature::from(func->def()).str(), func });

			//Compile it
			entryPoint = compileFunction(func, true);
			return true;
		}

		return false;
	}

	bool ExecutionEngine::compileFunction(const std::string& signature) {
		JitFunction entryPoint;
		return compileFunction(signature, entryPoint);
	}

	void ExecutionEngine::generateCode() {
		//Generate instructions for all functions
		for (auto& image : mImageContainer.images()) {
			for (auto& currentFunc : image->functions()) {
				if (!currentFunc.second.isExternal()) {
					auto& funcDef = mVMState.binder().getFunction(currentFunc.first);
					auto funcImage = mImageContainer.getFunction(currentFunc.first);
					auto func = mFunctionLoader.loadManaged(*funcImage, funcDef);
					mLoadedFunctions.insert({ FunctionSignature::from(func->def()).str(), func });
					compileFunction(func, false);
				}
			}
		}

		//Fix unresolved symbols
		mJIT.resolveSymbols();
	}

	void ExecutionEngine::loadAndCompileAll() {
		load(true);
		generateCode();
		mJIT.makeExecutable();
	}

	CallStack& ExecutionEngine::callStack() {
		return mCallStack;
	}

	const CallStack& ExecutionEngine::callStack() const {
		return mCallStack;
	}
}
