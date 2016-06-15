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
								 std::map<std::string, AssemblyParser::Function> functions,
								 std::map<std::string, AssemblyParser::Class> classes)
		: mImageData(std::move(imageData)),
		  mFunctionBodyOffsets(std::move(functionBodyOffset)),
		  mClassBodyOffsets(std::move(classBodyOffsets)),
		  mFunctions(std::move(functions)),
		  mClasses(std::move(classes)) {

	}

	AssemblyImage::AssemblyImage(const AssemblyParser::Assembly& assembly) {
		for (auto func : assembly.functions) {
			auto signature = AssemblyParser::getSignature(func);

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

	const std::map<std::string, AssemblyParser::Function>& AssemblyImage::functions() const {
		return mFunctions;
	}

	const std::map<std::string, AssemblyParser::Class>& AssemblyImage::classes() const {
		return mClasses;
	}

	bool AssemblyImage::loadFunctionBody(std::string function) {
		if (mFunctionBodyOffsets.count(function) > 0) {
			auto bodyOffset = mFunctionBodyOffsets[function];

			AssemblyParser::Function& func = mFunctions[function];
			func.attributes = AssemblyImageLoader::loadAttributes(mImageData, bodyOffset);

			auto numLocals = loadData<std::size_t>(mImageData, bodyOffset);
			for (std::size_t i = 0; i < numLocals; i++) {
				auto local = loadString(mImageData, bodyOffset);
				func.localTypes.push_back(local);
			}

			auto numInst = loadData<std::size_t>(mImageData, bodyOffset);
			for (std::size_t i = 0; i < numInst; i++) {
				auto format = (AssemblyParser::InstructionFormats)loadData<char>(mImageData, bodyOffset);
				auto opCode = (OpCodes)loadData<unsigned char>(mImageData, bodyOffset);

				switch (format) {
					case AssemblyParser::InstructionFormats::OpCodeOnly:
						func.instructions.push_back(AssemblyParser::Instruction::make(opCode));
						break;
					case AssemblyParser::InstructionFormats::IntData: {
							auto value = loadData<int>(mImageData, bodyOffset);
							func.instructions.push_back(AssemblyParser::Instruction::makeWithInt(opCode, value));
						}
						break;
					case AssemblyParser::InstructionFormats::FloatData:	{
							auto value = loadData<float>(mImageData, bodyOffset);
							func.instructions.push_back(AssemblyParser::Instruction::makeWithFloat(opCode, value));
						}
						break;
					case AssemblyParser::InstructionFormats::CharData: {
							auto value = loadData<char>(mImageData, bodyOffset);
							func.instructions.push_back(AssemblyParser::Instruction::makeWithChar(opCode, value));
						}
						break;
					case AssemblyParser::InstructionFormats::StrData: {
							auto value = loadString(mImageData, bodyOffset);
							func.instructions.push_back(AssemblyParser::Instruction::makeWithStr(opCode, value));
						}
						break;
					case AssemblyParser::InstructionFormats::Call: {
							auto funcName = loadString(mImageData, bodyOffset);
							auto numParams = loadData<std::size_t>(mImageData, bodyOffset);
							std::vector<std::string> params;

							for (std::size_t j = 0; j < numParams; j++) {
								params.push_back(loadString(mImageData, bodyOffset));
							}

							func.instructions.push_back(AssemblyParser::Instruction::makeCall(funcName, params));
						}
						break;
					case AssemblyParser::InstructionFormats::CallInstance: {
							auto funcName = loadString(mImageData, bodyOffset);
							auto calledClassType = loadString(mImageData, bodyOffset);
							auto numParams = loadData<std::size_t>(mImageData, bodyOffset);
							std::vector<std::string> params;

							for (std::size_t j = 0; j < numParams; j++) {
								params.push_back(loadString(mImageData, bodyOffset));
							}

							if (opCode == OpCodes::NEW_OBJECT) {
								func.instructions.push_back(AssemblyParser::Instruction::makeNewObject(
									calledClassType,
									params));
							} else {
								func.instructions.push_back(AssemblyParser::Instruction::makeCallInstance(
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

			AssemblyParser::Class& classDef = mClasses[className];
			classDef.parentClassName = loadString(mImageData, bodyOffset);
			classDef.attributes = AssemblyImageLoader::loadAttributes(mImageData, bodyOffset);

			auto numFields = loadData<std::size_t>(mImageData, bodyOffset);
			for (std::size_t i = 0; i < numFields; i++) {
				AssemblyParser::Field field;
				field.attributes = AssemblyImageLoader::loadAttributes(mImageData, bodyOffset);
				field.name = loadString(mImageData, bodyOffset);
				field.type = loadString(mImageData, bodyOffset);
				classDef.fields.emplace_back(field);
			}

			mClassBodyOffsets.erase(className);
			return true;
		}

		return false;
	}

	AssemblyParser::AttributeContainer AssemblyImageLoader::loadAttributes(BinaryData& data, std::size_t& index) {
		AssemblyParser::AttributeContainer attributes;
		std::size_t numAttributes = loadData<std::size_t>(data, index);
		for (std::size_t i = 0; i < numAttributes; i++) {
			AssemblyParser::Attribute attribute;
			attribute.name = loadString(data, index);

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

	AssemblyParser::Function AssemblyImageLoader::loadFunctionDefinition(BinaryData& data, std::size_t& index) {
		AssemblyParser::Function func;

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

	AssemblyParser::Class AssemblyImageLoader::loadClassDefinition(BinaryData& data, std::size_t& index) {
		AssemblyParser::Class classDef;
		classDef.name = loadString(data, index);
		return classDef;
	}

	void AssemblyImageLoader::load(BinaryData& imageData, AssemblyImage& image) {
		std::unordered_map<std::string, std::size_t> functionBodyOffset;
		std::unordered_map<std::string, std::size_t> classBodyOffsets;
		std::map<std::string, AssemblyParser::Function> functions;
		std::map<std::string, AssemblyParser::Class> classes;

		std::size_t index = 0;

		auto numFuncs = loadData<std::size_t>(imageData, index);
		auto numClasses = loadData<std::size_t>(imageData, index);

		//Load funcs defs
		for (std::size_t i = 0; i < numFuncs; i++) {
			auto func = loadFunctionDefinition(imageData, index);
			auto bodyOffset = loadData<std::size_t>(imageData, index);
			auto signature = AssemblyParser::getSignature(func);

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

		image = std::move(AssemblyImage(
			  std::move(imageData),
			  std::move(functionBodyOffset),
			  std::move(classBodyOffsets),
			  std::move(functions),
			  std::move(classes)
		));
	}
}
