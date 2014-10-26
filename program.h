#pragma once
#include <string>
#include <map>
#include <vector>

struct Instruction;
class Type;

//Represents an user defined function
struct Function {
	const std::string name;

	const std::vector<Type*> arguments;
	Type* const returnType;

	int numLocals;

	std::vector<Instruction> instructions;
	std::vector<unsigned char> generatedCode;

	//Creates a new function
	Function(std::string name, std::vector<Type*> arguments, Type* returnType);

	int numArgs() const;
};

//Represents a program
struct Program {
    std::map<std::string, Function*> functions;
    ~Program();
};