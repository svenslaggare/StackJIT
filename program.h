#pragma once
#include <string>
#include <map>
#include <vector>

struct Instruction;
typedef std::pair<std::string, unsigned int> FunctionCall;

//Represents an user defined function
struct Function {
	std::string Name;
	int NumArgs;
	int NumLocals;
	std::map<FunctionCall, std::string> CallTable;
	std::vector<Instruction> Instructions;
	std::vector<unsigned char> GeneratedCode;
};

//Represents a program
struct Program {
    std::map<std::string, Function*> Functions;
    ~Program();
};