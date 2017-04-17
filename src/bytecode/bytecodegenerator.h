#pragma once
#include <iostream>
#include <functional>
#include "../loader/loader.h"

namespace stackjit {
	//Generates byte code
	namespace ByteCodeGenerator {
		//Returns an escaped version of the given string
		std::string escapedString(std::string str);

		//Generates byte code for the given attributes
		void generateAttributes(std::ostream& stream, const Loader::AttributeContainer& attributes);

		//Generates byte code for the given function
		void generateFunction(std::ostream& stream, const Loader::Function& function);

		//Generates byte code for the given class
		void generateClass(std::ostream& stream, const Loader::Class& classDef);
	};
}