#pragma once
#include "../loader/loader.h"
#include <string>
#include <vector>

namespace stackjit {
	//Represents a byte code parser
	class ByteCodeParser {
	private:
		std::vector<std::string> mTokens;
		std::size_t mTokenIndex;

		bool mLocalsSet = false;

		//Creates a new byte code parser using the given tokens
		ByteCodeParser(std::vector<std::string> tokens);

		//Returns the current token
		std::string currentToken() const;

		//Returns a lower case version of the current token
		std::string currentTokenToLower() const;

		//Advances to the next token and returns the next
		std::string nextToken();

		//Returns the next token without advancing to it
		std::string peekNextToken();

		//Advances to the next token at a token that can be at the end
		void nextTokenAtEnd();

		//Parses a function definition
		void parseFunctionDefinition(Loader::Function& function);

		//Reads the call parameters
		void readCallParameters(std::vector<std::string>& parameters);

		//Parses an attribute
		void parseAttribute(Loader::AttributeContainer& container);

		//Parses an instruction
		void parseInstruction(Loader::Function& currentFunction);

		//Parses a function body
		void parseFunctionBody(Loader::Assembly& assembly, Loader::Function& currentFunction);

		//Parses a class body
		void parseClassBody(Loader::Assembly& assembly, Loader::Class& currentClass);
	public:
		//Parses the byte code in the given stream
		ByteCodeParser(std::istream& stream);

		//Parses the loaded tokens into the given assembly
		void parse(Loader::Assembly& assembly);
	};

	namespace Loader {
		//Loads an assembly from the given stream
		void load(std::istream& stream, Loader::Assembly& assembly);
	}
}