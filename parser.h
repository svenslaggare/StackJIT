#pragma once
#include <vector>
#include <map>
#include <string>

struct Instruction;

struct DefinedFunction
{
	int NumArgs;
	std::vector<Instruction>* Instructions;
};

struct Program {
    std::map<std::string, DefinedFunction> Functions;
};

namespace Parser {
	std::vector<std::string> tokenizeInput();
	
	void parseTokens(const std::vector<std::string>& tokens, Program& program);
}