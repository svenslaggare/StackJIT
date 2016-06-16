#pragma once
#include "parser.h"
#include <vector>
#include <ostream>

using BinaryData = std::vector<char>;

//Represents an assembler
class Assembler {
	//Generates a binary representation of the given attributes
	void generateAttributes(BinaryData& data, const stackjit::AssemblyParser::AttributeContainer& attributes);

	//Generates a binary representation of the given function body
	void generateFunctionBody(BinaryData& data, stackjit::AssemblyParser::Function& function);

	//Generates a binary representation of the given function definition
	void generateFunctionDefinition(BinaryData& data, stackjit::AssemblyParser::Function& function);

	//Generates a binary representation of the given class body
	void generateClassBody(BinaryData& data, stackjit::AssemblyParser::Class& classDef);

	//Generates a binary representation of the given class definition
	void generateClassDefinition(BinaryData& data, stackjit::AssemblyParser::Class& classDef);
public:
	//Generates an image for the given assemblies
	void generateImage(std::vector<stackjit::AssemblyParser::Assembly>& assemblies, std::ostream& stream);
};
