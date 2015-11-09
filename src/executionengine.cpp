#include "executionengine.h"
#include "vmstate.h"
#include "binder.h"
#include "function.h"
#include "verifier.h"
#include "type.h"
#include "loader.h"
#include "native.h"
#include "imageloader.h"
#include "test.h"
#include "functionsignature.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

ImageContainer::ImageContainer() {

}

ImageContainer::~ImageContainer() {
	for (auto image : mImages) {
		delete image;
	}
}

const std::vector<AssemblyImage*>& ImageContainer::images() const {
	return mImages;
}

void ImageContainer::addImage(AssemblyImage* image) {
	mImages.push_back(image);

	for (auto& classDef : image->classes()) {
		mClassToImage.insert({ classDef.first, image });
	}

	for (auto& func : image->functions()) {
		mFuncToImage.insert({ func.first, image });
	}
}

const AssemblyParser::Function* ImageContainer::getFunction(std::string function) const {
	if (mFuncToImage.count(function) > 0) {
		return &mFuncToImage.at(function)->functions().at(function);
	}

	return nullptr;
}

void ImageContainer::loadFunctionBody(std::string function) {
	if (mFuncToImage.count(function) > 0) {
		mFuncToImage[function]->loadFunctionBody(function);
	}
}

void ImageContainer::loadClassBody(std::string className) {
	if (mClassToImage.count(className) > 0) {
		mClassToImage[className]->loadClassBody(className);
	}
}

ExecutionEngine::ExecutionEngine(VMState& vmState)
	: mVMState(vmState), mJIT(vmState), mCallStack(2000) {

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
    if (mVMState.binder().isDefined("main()")) {
        return (EntryPointFunction)(mVMState.binder().getFunction("main()").entryPoint());
    } else {
        throw std::runtime_error("No entry point has been defined.");
    }
}

//Returns the function with the given name
const AssemblyParser::Function* getFunction(AssemblyImage& image, std::string funcName) {
	for (auto& current : image.functions()) {
		auto& func = current.second;
		if (func.name == funcName) {
			return &func;
		}
	}

	return nullptr;
}

void ExecutionEngine::loadImage(AssemblyImage* image, AssemblyType assemblyType) {
	if (assemblyType == AssemblyType::Program) {
		auto mainFunc = getFunction(*image, "main");

		if (mainFunc != nullptr) {
			if (!(mainFunc->parameters.size() == 0
				  && mainFunc->returnType == TypeSystem::toString(PrimitiveTypes::Integer))) {
				throw std::runtime_error("The main function must have the following signature: 'main() Int'.");
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
		throw std::runtime_error("Could not load image.");
	}

	auto image = new AssemblyImage();
	AssemblyImageLoader::load(imageData, *image);
	loadImage(image, assemblyType);
}

void ExecutionEngine::loadAssembly(AssemblyParser::Assembly& assembly, AssemblyType assemblyType) {
    loadImage(new AssemblyImage(assembly), assemblyType);
}

bool ExecutionEngine::loadAssembly(std::string filePath, AssemblyType assemblyType) {
	std::ios::openmode openMode = std::ios::in;

	if (filePath.find(".simg") != std::string::npos) {
		openMode = std::ios::binary;
	}

	std::ifstream fileStream(filePath, openMode);

	if (!fileStream.is_open()) {
		std::cout << "Could not load assembly '" << filePath << "'." << std::endl;
		return false;
	}

	if (openMode == std::ios::binary) {
		loadImage(fileStream, assemblyType);
	} else {
		AssemblyParser::Assembly assembly;
		Loader::load(fileStream, mVMState, assembly);
		loadAssembly(assembly, assemblyType);
	}

	return true;
}

void ExecutionEngine::loadRuntimeLibrary() {
	if (mVMState.loadRuntimeLibrary) {
		bool loaded = loadAssembly(mBaseDir + "rtlib/rtlib.simg");

		if (!loaded) {
			throw std::runtime_error("Could not load runtime library.");
		}
	}
}

void ExecutionEngine::load(bool loadBody) {
	auto& binder = mVMState.binder();

	//Load runtime library
	loadRuntimeLibrary();

	//Load classes
	Loader::loadClasses(mVMState, mImageContainer);

	//Load native functions
	NativeLibrary::add(mVMState);

	if (mVMState.testMode) {
		//Load test functions
		TestLibrary::add(mVMState);
	}

	//Load functions
	for (auto& image : mImageContainer.images()) {
		for (auto& current : image->functions()) {
			auto& currentFunc = current.second;
			FunctionDefinition funcDef;

			if (loadBody) {
				image->loadFunctionBody(current.first);
			}

			if (!currentFunc.isExternal) {
				Loader::generateDefinition(mVMState, currentFunc, funcDef);

				auto signature = FunctionSignature::from(funcDef).str();
				if (binder.isDefined(signature)) {
					throw std::runtime_error("The function '" + signature + "' is already defined.");
				}
			} else {
				Loader::loadExternalFunction(mVMState, currentFunc, funcDef);
			}

			binder.define(funcDef);
		}
	}
}

void ExecutionEngine::compileFunction(ManagedFunction* function, std::string signature, bool resolveSymbols) {
	//Type check the function
	Verifier verifier(mVMState);
	verifier.verifyFunction(*function);

	//Compile it
	auto funcPtr = mJIT.compileFunction(function);

	if (mVMState.enableDebug && mVMState.printFunctionGeneration) {
		std::cout
			<< "Defined function '" << function->def().name() << "' at 0x" << std::hex << (PtrValue)funcPtr << std::dec << "."
			<< std::endl;
	}

	if (signature == "") {
		signature = FunctionSignature::from(function->def()).str();
	}

	//Set the entry point & size for the function
	mVMState.binder().getFunction(signature).setEntryPoint((unsigned char*)funcPtr);

	if (resolveSymbols) {
		//Fix unresolved symbols
		mJIT.resolveSymbols(signature);
	}
}

bool ExecutionEngine::compileFunction(std::string signature) {
	auto funcDef = mImageContainer.getFunction(signature);

	if (funcDef != nullptr && !mJIT.hasCompiled(signature)) {
		//Load the function
		mImageContainer.loadFunctionBody(signature);
		auto func = Loader::loadManagedFunction(mVMState, *funcDef, false);
		mLoadedFunctions.insert({ FunctionSignature::from(func->def()).str(), func });

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
