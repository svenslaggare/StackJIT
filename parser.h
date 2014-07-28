#pragma once
#include <vector>
#include <map>
#include <string>

struct Instruction;

//Represents a function definition
struct DefinedFunction {
	int NumArgs = 0;
	std::vector<Instruction>* Instructions;
};

//Represents a program
struct Program {
    std::map<std::string, DefinedFunction> Functions;
};

//The parser
namespace Parser {
	//Tokenizes from the given stream
	std::vector<std::string> tokenize(std::istream& stream);
	
	//Parses the given tokens
	void parseTokens(const std::vector<std::string>& tokens, Program& program);
}