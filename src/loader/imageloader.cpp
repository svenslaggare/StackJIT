#include "imageloader.h"
#include <fstream>

namespace stackjit {
	namespace {
		//Loads the given data
		template<typename T>
		T loadData(BinaryData& data, std::size_t& index) {
			char valueData[sizeof(T)];

			for (std::size_t i = 0; i < sizeof(T); i++, index++) {
				valueData[i] = data.at(index);
			}

			return *reinterpret_cast<T*>(valueData);
		}

		//Loads the given string
		std::string loadString(BinaryData& data, std::size_t& index) {
			auto size = loadData<std::size_t>(data, index);
			std::string str;
			str.reserve(size);

			for (std::size_t i = 0; i < size; i++, index++) {
				str.push_back(data.at(index));
			}

			return str;
		}
	}

	AssemblyImage::AssemblyImage() {

	}

	AssemblyImage::AssemblyImage(std::vector<char> imageData,
								 std::unordered_map<std::string, std::size_t> functionBodyOffset,
								 std::unordered_map<std::string, std::size_t> classBodyOffsets,
								 std::unordered_map<std::string, Loader::Function> functions,
								 std::unordered_map<std::string, Loader::Class> classes)
		: mImageData(std::move(imageData)),
		  mFunctionBodyOffsets(std::move(functionBodyOffset)),
		  mClassBodyOffsets(std::move(classBodyOffsets)),
		  mFunctions(std::move(functions)),
		  mClasses(std::move(classes)) {

	}

	AssemblyImage::AssemblyImage(const Loader::Assembly& assembly) {
		for (auto func : assembly.functions) {
			auto signature = Loader::getSignature(func);

			if (mFunctions.count(signature) > 0) {
				throw std::runtime_error("The function '" + signature + "' is already defined.");
			}

			mFunctions.emplace(signature, func);
		}

		for (auto classDef : assembly.classes) {
			if (mClasses.count(classDef.name) > 0) {
				throw std::runtime_error("The class '" + classDef.name + "' is already defined.");
			}

			mClasses.emplace(classDef.name, classDef);
		}
	}

	const std::unordered_map<std::string, Loader::Function>& AssemblyImage::functions() const {
		return mFunctions;
	}

	const std::unordered_map<std::string, Loader::Class>& AssemblyImage::classes() const {
		return mClasses;
	}

	bool AssemblyImage::loadFunctionBody(std::string function) {
		if (mFunctionBodyOffsets.count(function) > 0) {
			auto bodyOffset = mFunctionBodyOffsets[function];

			Loader::Function& func = mFunctions[function];
			func.attributes = AssemblyImageLoader::loadAttributes(mImageData, bodyOffset);

			auto numLocals = loadData<std::size_t>(mImageData, bodyOffset);
			for (std::size_t i = 0; i < numLocals; i++) {
				auto local = loadString(mImageData, bodyOffset);
				func.localTypes.push_back(local);
			}

			auto numInst = loadData<std::size_t>(mImageData, bodyOffset);
			for (std::size_t i = 0; i < numInst; i++) {
				auto format = (Loader::InstructionFormats)loadData<char>(mImageData, bodyOffset);
				auto opCode = (OpCodes)loadData<unsigned char>(mImageData, bodyOffset);

				switch (format) {
					case Loader::InstructionFormats::OpCodeOnly:
						func.instructions.push_back(Loader::Instruction::make(opCode));
						break;
					case Loader::InstructionFormats::IntData: {
							auto value = loadData<int>(mImageData, bodyOffset);
							func.instructions.push_back(Loader::Instruction::makeWithInt(opCode, value));
						}
						break;
					case Loader::InstructionFormats::FloatData:	{
							auto value = loadData<float>(mImageData, bodyOffset);
							func.instructions.push_back(Loader::Instruction::makeWithFloat(opCode, value));
						}
						break;
					case Loader::InstructionFormats::CharData: {
							auto value = loadData<char>(mImageData, bodyOffset);
							func.instructions.push_back(Loader::Instruction::makeWithChar(opCode, value));
						}
						break;
					case Loader::InstructionFormats::StringData: {
							auto value = loadString(mImageData, bodyOffset);
							func.instructions.push_back(Loader::Instruction::makeWithString(opCode, value));
						}
						break;
					case Loader::InstructionFormats::StringConstantData: {
							auto value = loadString(mImageData, bodyOffset);
							func.instructions.push_back(Loader::Instruction::makeWithStringConstant(opCode, value));
						}
						break;
					case Loader::InstructionFormats::Call: {
							auto funcName = loadString(mImageData, bodyOffset);
							auto numParams = loadData<std::size_t>(mImageData, bodyOffset);
							std::vector<std::string> params;

							for (std::size_t j = 0; j < numParams; j++) {
								params.push_back(loadString(mImageData, bodyOffset));
							}

							func.instructions.push_back(Loader::Instruction::makeCall(funcName, params));
						}
						break;
					case Loader::InstructionFormats::CallInstance: {
							auto funcName = loadString(mImageData, bodyOffset);
							auto calledClassType = loadString(mImageData, bodyOffset);
							auto numParams = loadData<std::size_t>(mImageData, bodyOffset);
							std::vector<std::string> params;

							for (std::size_t j = 0; j < numParams; j++) {
								params.push_back(loadString(mImageData, bodyOffset));
							}

							if (opCode == OpCodes::NEW_OBJECT) {
								func.instructions.push_back(Loader::Instruction::makeNewObject(
									calledClassType,
									params));
							} else {
								func.instructions.push_back(Loader::Instruction::makeCallInstance(
									calledClassType,
									funcName,
									params));
							}
						}
						break;
				}
			}

			mFunctionBodyOffsets.erase(function);
			return true;
		}

		return false;
	}

	bool AssemblyImage::loadClassBody(std::string className) {
		if (mClassBodyOffsets.count(className) > 0) {
			auto bodyOffset = mClassBodyOffsets[className];

			Loader::Class& classDef = mClasses[className];
			classDef.parentClassName = loadString(mImageData, bodyOffset);
			classDef.attributes = AssemblyImageLoader::loadAttributes(mImageData, bodyOffset);

			auto numFields = loadData<std::size_t>(mImageData, bodyOffset);
			for (std::size_t i = 0; i < numFields; i++) {
				auto attributes = AssemblyImageLoader::loadAttributes(mImageData, bodyOffset);
				auto fieldName = loadString(mImageData, bodyOffset);
				auto fieldType = loadString(mImageData, bodyOffset);
				Loader::Field field(fieldName, fieldType);
				field.attributes = attributes;
				classDef.fields.emplace_back(field);
			}

			mClassBodyOffsets.erase(className);
			return true;
		}

		return false;
	}

	bool AssemblyImage::hasLoadedDefinitions() const {
		return mLoadedDefinitions;
	}

	void AssemblyImage::loadedDefinitions() {
		mLoadedDefinitions = true;
	}

	Loader::AttributeContainer AssemblyImageLoader::loadAttributes(BinaryData& data, std::size_t& index) {
		Loader::AttributeContainer attributes;
		std::size_t numAttributes = loadData<std::size_t>(data, index);
		for (std::size_t i = 0; i < numAttributes; i++) {
			Loader::Attribute attribute(loadString(data, index));

			std::size_t numValues = loadData<std::size_t>(data, index);
			for (std::size_t j = 0; j < numValues; j++) {
				std::string key = loadString(data, index);
				std::string value = loadString(data, index);
				attribute.values.emplace(key, value);
			}

			attributes.emplace(attribute.name, attribute);
		}

		return attributes;
	}

	Loader::Function AssemblyImageLoader::loadFunctionDefinition(BinaryData& data, std::size_t& index) {
		Loader::Function func;

		func.isExternal = loadData<bool>(data, index);
		func.isMemberFunction = loadData<bool>(data, index);

		if (func.isMemberFunction) {
			func.className = loadString(data, index);
			func.memberFunctionName = loadString(data, index);
			func.name = func.className + "::" + func.memberFunctionName;
		} else {
			func.name = loadString(data, index);
		}

		auto numParams = loadData<std::size_t>(data, index);
		for (std::size_t i = 0; i < numParams; i++) {
			std::string param = loadString(data, index);
			func.parameters.push_back(param);
		}

		func.returnType = loadString(data, index);

		return func;
	}

	Loader::Class AssemblyImageLoader::loadClassDefinition(BinaryData& data, std::size_t& index) {
		Loader::Class classDef(loadString(data, index));
		return classDef;
	}

	void AssemblyImageLoader::load(BinaryData& imageData, AssemblyImage& image) {
		std::unordered_map<std::string, std::size_t> functionBodyOffset;
		std::unordered_map<std::string, std::size_t> classBodyOffsets;
		std::unordered_map<std::string, Loader::Function> functions;
		std::unordered_map<std::string, Loader::Class> classes;

		std::size_t index = 0;

		auto numFuncs = loadData<std::size_t>(imageData, index);
		auto numClasses = loadData<std::size_t>(imageData, index);

		//Load funcs defs
		for (std::size_t i = 0; i < numFuncs; i++) {
			auto func = loadFunctionDefinition(imageData, index);
			auto bodyOffset = loadData<std::size_t>(imageData, index);
			auto signature = Loader::getSignature(func);

			if (functions.count(signature) > 0) {
				throw std::runtime_error("The function '" + signature + "' is already defined.");
			}

			functionBodyOffset.emplace(signature, bodyOffset);
			functions.emplace(signature, func);
		}

		//Load class defs
		for (std::size_t i = 0; i < numClasses; i++) {
			auto classDef = loadClassDefinition(imageData, index);
			auto bodyOffset = loadData<std::size_t>(imageData, index);

			if (classes.count(classDef.name) > 0) {
				throw std::runtime_error("The class '" + classDef.name + "' is already defined.");
			}

			classBodyOffsets.emplace(classDef.name, bodyOffset);
			classes.emplace(classDef.name, classDef);
		}

		image = AssemblyImage(
			  std::move(imageData),
			  std::move(functionBodyOffset),
			  std::move(classBodyOffsets),
			  std::move(functions),
			  std::move(classes));
	}
}
