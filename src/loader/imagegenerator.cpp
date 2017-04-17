#include "imagegenerator.h"

namespace stackjit {
	namespace {
		//Adds the given data
		template<typename T>
		void addData(BinaryData& data, T value) {
			auto valuePtr = reinterpret_cast<char*>(&value);

			for (std::size_t i = 0; i < sizeof(T); i++) {
				data.push_back(valuePtr[i]);
			}
		}

		//Adds the given string
		void addString(BinaryData& data, const std::string& str) {
			addData(data, str.length());
			for (char c : str) {
				data.push_back(c);
			}
		}

		//Sets the given data starting at the given index
		template<typename T>
		void setData(BinaryData& data, std::size_t startIndex, T value) {
			auto valuePtr = reinterpret_cast<char*>(&value);
			for (std::size_t i = 0; i < sizeof(T); i++) {
				data[startIndex + i] = valuePtr[i];
			}
		}
	}

	void AssemblyImageGenerator::generateAttributes(BinaryData& data, const Loader::AttributeContainer& attributes) {
		addData(data, attributes.size());

		for (auto& current : attributes) {
			auto& attribute = current.second;
			addString(data, attribute.name);

			addData(data, attribute.values.size());
			for (auto keyValue : attribute.values) {
				addString(data, keyValue.first);
				addString(data, keyValue.second);
			}
		}
	}

	void AssemblyImageGenerator::generateFunctionBody(BinaryData& data, Loader::Function& function) {
		//Attributes
		generateAttributes(data, function.attributes);

		//Locals
		addData<std::size_t>(data, function.localTypes.size());
		for (auto& local : function.localTypes) {
			addString(data, local);
		}

		//Body
		addData<std::size_t>(data, function.instructions.size());

		for (auto& inst : function.instructions) {
			addData<char>(data, (char)inst.format);
			addData<unsigned char>(data, (unsigned char)inst.opCode);

			switch (inst.format) {
				case Loader::InstructionFormats::OpCodeOnly:
					break;
				case Loader::InstructionFormats::IntData:
					addData(data, inst.intValue);
					break;
				case Loader::InstructionFormats::FloatData:
					addData(data, inst.floatValue);
					break;
				case Loader::InstructionFormats::CharData:
					addData(data, inst.charValue);
					break;
				case Loader::InstructionFormats::StringData:
					addString(data, inst.stringValue);
					break;
				case Loader::InstructionFormats::StringConstantData:
					addString(data, inst.stringValue);
					break;
				case Loader::InstructionFormats::Call:
					addString(data, inst.stringValue);
					addData(data, inst.parameters.size());

					for (auto& param : inst.parameters) {
						addString(data, param);
					}
					break;
				case Loader::InstructionFormats::CallInstance:
					addString(data, inst.stringValue);
					addString(data, inst.calledClassType);
					addData(data, inst.parameters.size());

					for (auto& param : inst.parameters) {
						addString(data, param);
					}
					break;
			}
		}
	}

	void AssemblyImageGenerator::generateFunctionDefinition(BinaryData& data, Loader::Function& function) {
		addData<bool>(data, function.isExternal);
		addData<bool>(data, function.isMemberFunction);

		if (function.isMemberFunction) {
			addString(data, function.className);
			addString(data, function.memberFunctionName);
		} else {
			addString(data, function.name);
		}

		addData(data, function.parameters.size());
		for (auto& param : function.parameters) {
			addString(data, param);
		}

		addString(data, function.returnType);
	}

	void AssemblyImageGenerator::generateClassBody(BinaryData& data, Loader::Class& classDef) {
		//Inheritance
		addString(data, classDef.parentClassName);

		//Class attributes
		generateAttributes(data, classDef.attributes);

		//Fields
		addData(data, classDef.fields.size());
		for (auto& field : classDef.fields) {
			generateAttributes(data, field.attributes);
			addString(data, field.name);
			addString(data, field.type);
		}
	}

	void AssemblyImageGenerator::generateClassDefinition(BinaryData& data, Loader::Class& classDef) {
		addString(data, classDef.name);
	}

	void AssemblyImageGenerator::generateImage(std::vector<Loader::Assembly>& assemblies, std::ostream& stream) {
		BinaryData data;

		//Compute the number of functions & classes
		std::size_t numFuncs = 0;
		std::size_t numClasses = 0;
		for (auto& assembly : assemblies) {
			numFuncs += assembly.functions.size();
			numClasses += assembly.classes.size();
		}

		//Header
		addData(data, numFuncs);
		addData(data, numClasses);

		//Functions definitions
		std::unordered_map<std::string, std::size_t> funcBodyOffsets;

		for (auto& assembly : assemblies) {
			for (auto& func : assembly.functions) {
				generateFunctionDefinition(data, func);
				funcBodyOffsets.insert({ Loader::getSignature(func), data.size() });
				addData<std::size_t>(data, 0);
			}
		}

		//Class definitions
		std::unordered_map<std::string, std::size_t> classBodyOffsets;

		for (auto& assembly : assemblies) {
			for (auto& classDef : assembly.classes) {
				generateClassDefinition(data, classDef);
				classBodyOffsets.insert({ classDef.name, data.size() });
				addData<std::size_t>(data, 0);
			}
		}

		//Functions bodies
		for (auto& assembly : assemblies) {
			for (auto& func : assembly.functions) {
				//Patch the offset
				setData<std::size_t>(data, funcBodyOffsets.at(Loader::getSignature(func)), data.size());
				generateFunctionBody(data, func);
			}
		}

		//Class bodies
		for (auto& assembly : assemblies) {
			for (auto& classDef : assembly.classes) {
				//Patch the offset
				setData<std::size_t>(data, classBodyOffsets.at(classDef.name), data.size());
				generateClassBody(data, classDef);
			}
		}

		//Write to the stream
		stream.write(data.data(), data.size());
	}

}