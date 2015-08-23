#pragma once
#include <iostream>
#include <unordered_map>
#include <map>
#include "parser.h"
#include "assembler.h"

//Represents an assembly image
class AssemblyImage {
private:
	BinaryData mImageData;

	std::unordered_map<std::string, std::size_t> mFunctionBodyOffsets;
	std::unordered_map<std::string, std::size_t> mClassBodyOffsets;

	std::map<std::string, AssemblyParser::Function> mFunctions;
	std::map<std::string, AssemblyParser::Class> mClasses;
public:
	//Creates a new image
	AssemblyImage(
		BinaryData imageData,
		std::unordered_map<std::string, std::size_t> functionBodyOffset,
		std::unordered_map<std::string, std::size_t> classBodyOffsets,
		std::map<std::string, AssemblyParser::Function> functions,
		std::map<std::string, AssemblyParser::Class> classes);

	//Returns the functions
	const std::map<std::string, AssemblyParser::Function>& functions() const;

	//Returns the classes
	const std::map<std::string, AssemblyParser::Class>& classes() const;

	//Loads the body of the given function
	void loadFunctionBody(std::string function);

	//Loads the body of the given class
	void loadClassBody(std::string className);
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
	AssemblyImage load(BinaryData& imageData);
};
