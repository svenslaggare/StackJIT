#pragma once
#include <string>
#include <map>
#include <vector>

struct Instruction;
class Type;

//Represents an user defined function
struct Function {
	std::string Name;

	int NumArgs;
	std::vector<Type*> Arguments;
	Type* ReturnType;

	int NumLocals;

	std::vector<Instruction> Instructions;
	std::vector<unsigned char> GeneratedCode;
};

//Represents a program
struct Program {
    std::map<std::string, Function*> Functions;
    ~Program();
};