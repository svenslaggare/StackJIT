#include "assembler.h"
#include <iostream>

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

void Assembler::generateAttributes(BinaryData& data, const stackjit::AssemblyParser::AttributeContainer& attributes) {
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

void Assembler::generateFunctionBody(BinaryData& data, stackjit::AssemblyParser::Function& function) {
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
			case stackjit::AssemblyParser::InstructionFormats::OpCodeOnly:
				break;
			case stackjit::AssemblyParser::InstructionFormats::IntData:
				addData(data, inst.intValue);
				break;
			case stackjit::AssemblyParser::InstructionFormats::FloatData:
				addData(data, inst.floatValue);
				break;
			case stackjit::AssemblyParser::InstructionFormats::CharData:
				addData(data, inst.charValue);
				break;
			case stackjit::AssemblyParser::InstructionFormats::StringData:
				addString(data, inst.stringValue);
				break;
			case stackjit::AssemblyParser::InstructionFormats::StringConstantData:
				addString(data, inst.stringValue);
				break;
			case stackjit::AssemblyParser::InstructionFormats::Call:
				addString(data, inst.stringValue);
				addData(data, inst.parameters.size());

				for (auto& param : inst.parameters) {
					addString(data, param);
				}
				break;
			case stackjit::AssemblyParser::InstructionFormats::CallInstance:
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

void Assembler::generateFunctionDefinition(BinaryData& data, stackjit::AssemblyParser::Function& function) {
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

void Assembler::generateClassBody(BinaryData& data, stackjit::AssemblyParser::Class& classDef) {
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

void Assembler::generateClassDefinition(BinaryData& data, stackjit::AssemblyParser::Class& classDef) {
	addString(data, classDef.name);
}

void Assembler::generateImage(std::vector<stackjit::AssemblyParser::Assembly>& assemblies, std::ostream& stream) {
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
			funcBodyOffsets.insert({ stackjit::AssemblyParser::getSignature(func), data.size() });
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
			setData<std::size_t>(data, funcBodyOffsets.at(stackjit::AssemblyParser::getSignature(func)), data.size());
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
