#pragma once
#include "../loader/parser.h"
#include <string>
#include <vector>

namespace stackjit {
	//Represents a byte code parser
	class ByteCodeParser {
	private:
		std::vector<std::string> mTokens;
		std::size_t mTokenIndex;

		bool mLocalsSet = false;

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
		void parseFunctionDefinition(AssemblyParser::Function& function);

		//Reads the call parameters
		void readCallParameters(std::vector<std::string>& parameters);

		//Parses an attribute
		void parseAttribute(AssemblyParser::AttributeContainer& container);

		//Parses an instruction
		void parseInstruction(AssemblyParser::Function& currentFunction);

		//Parses a function body
		void parseFunctionBody(AssemblyParser::Assembly& assembly, AssemblyParser::Function& currentFunction);

		//Parses a class body
		void parseClassBody(AssemblyParser::Assembly& assembly, AssemblyParser::Class& currentClass);
	public:
		//Creates a new byte code parser using the given tokens
		ByteCodeParser(std::vector<std::string> tokens);

		//Parses the loaded tokens into the given assembly
		void parse(AssemblyParser::Assembly& assembly);
	};

	//The assembly parser
	namespace AssemblyParser {
		//Tokenizes from the given stream
		std::vector<std::string> tokenize(std::istream& stream);

		//Loads an assembly from the given stream
		void load(std::istream& stream, AssemblyParser::Assembly& assembly);
	}
}