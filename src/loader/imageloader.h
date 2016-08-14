#pragma once
#include "parser.h"
#include <iostream>
#include <unordered_map>

namespace stackjit {
	using BinaryData = std::vector<char>;

	//Represents an assembly image
	class AssemblyImage {
	private:
		BinaryData mImageData;

		std::unordered_map<std::string, std::size_t> mFunctionBodyOffsets;
		std::unordered_map<std::string, std::size_t> mClassBodyOffsets;

		std::unordered_map<std::string, AssemblyParser::Function> mFunctions;
		std::unordered_map<std::string, AssemblyParser::Class> mClasses;

		bool mLoadedDefinitions = false;
	public:
		//Creates a new image
		AssemblyImage();

		//Creates a new image
		AssemblyImage(
			BinaryData imageData,
			std::unordered_map<std::string, std::size_t> functionBodyOffset,
			std::unordered_map<std::string, std::size_t> classBodyOffsets,
			std::unordered_map<std::string, AssemblyParser::Function> functions,
			std::unordered_map<std::string, AssemblyParser::Class> classes);

		//Creates a new image from the given loaded assembly
		AssemblyImage(const AssemblyParser::Assembly& assembly);

		//Returns the functions
		const std::unordered_map<std::string, AssemblyParser::Function>& functions() const;

		//Returns the classes
		const std::unordered_map<std::string, AssemblyParser::Class>& classes() const;

		//Loads the body of the given function
		bool loadFunctionBody(std::string function);

		//Loads the body of the given class
		bool loadClassBody(std::string className);

		//Indicates if the definitions has been loaded
		bool hasLoadedDefinitions() const;

		//Marks that the definitions has been loaded
		void loadedDefinitions();
	};

	//Loads assembly images
	namespace AssemblyImageLoader {
		//Loads the given attributes
		AssemblyParser::AttributeContainer loadAttributes(BinaryData& data, std::size_t& index);

		//Loads the given function definition
		AssemblyParser::Function loadFunctionDefinition(BinaryData& data, std::size_t& index);

		//Loads the given class definition
		AssemblyParser::Class loadClassDefinition(BinaryData& data, std::size_t& index);

		//Loads an assembly image from given data
		void load(BinaryData& imageData, AssemblyImage& image);
	};
}
