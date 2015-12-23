#pragma once
#include <iostream>
#include <functional>
#include "loader/parser.h"

//Generates StackByteCode from the assembler parser structure
namespace ByteCodeGenerator {
	//Generates byte code for the given attributes
	void generateAttributes(std::ostream& stream, const AssemblyParser::AttributeContainer attributes);

	//Generates byte code for the given function
	void generateFunction(std::ostream& stream, const AssemblyParser::Function& function);

	//Generates byte code for the given class
	void generateClass(std::ostream& stream, const AssemblyParser::Class& classDef);
};