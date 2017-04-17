#pragma once
#include "../stackjit.h"
#include "loader.h"
#include <vector>
#include <ostream>

namespace stackjit {
	//Represents an assembly image generator
	class AssemblyImageGenerator {
		//Generates a binary representation of the given attributes
		void generateAttributes(BinaryData& data, const Loader::AttributeContainer& attributes);

		//Generates a binary representation of the given function body
		void generateFunctionBody(BinaryData& data, Loader::Function& function);

		//Generates a binary representation of the given function definition
		void generateFunctionDefinition(BinaryData& data, Loader::Function& function);

		//Generates a binary representation of the given class body
		void generateClassBody(BinaryData& data, Loader::Class& classDef);

		//Generates a binary representation of the given class definition
		void generateClassDefinition(BinaryData& data, Loader::Class& classDef);
	public:
		//Generates an image for the given assemblies
		void generateImage(std::vector <Loader::Assembly>& assemblies, std::ostream& stream);
	};
}