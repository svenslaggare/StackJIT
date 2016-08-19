#pragma once
#include <iostream>
#include <functional>
#include "../loader/parser.h"

namespace stackjit {
	//Generates StackByteCode from the assembler parser structure
	namespace ByteCodeGenerator {
		//Returns an escaped version of the given string
		std::string escapedString(std::string str);

		//Generates byte code for the given attributes
		void generateAttributes(std::ostream& stream, const AssemblyParser::AttributeContainer& attributes);

		//Generates byte code for the given function
		void generateFunction(std::ostream& stream, const AssemblyParser::Function& function);

		//Generates byte code for the given class
		void generateClass(std::ostream& stream, const AssemblyParser::Class& classDef);
	};
}