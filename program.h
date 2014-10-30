#pragma once
#include <string>
#include <map>
#include <vector>

struct Instruction;
class Type;

//Represents an user defined function
class Function {
private:
	std::vector<Type*> localTypes;
public:
	const std::string name;

	const std::vector<Type*> arguments;
	Type* const returnType;

	std::vector<Instruction> instructions;
	std::vector<unsigned char> generatedCode;

	//Creates a new function
	Function(std::string name, std::vector<Type*> arguments, Type* returnType);

	int numArgs() const;

	int numLocals() const;
	void setNumLocals(int count);
	Type* getLocal(int index) const;
	void setLocal(int index, Type* type);
};

//Represents a program
struct Program {
    std::map<std::string, Function*> functions;
    ~Program();
};