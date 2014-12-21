#pragma once
#include <string>
#include <map>
#include <vector>
#include <deque>

struct Instruction;
class Type;

//Represents an user defined function
class Function {
private:
	std::string mName;

	std::vector<Type*> mArguments;
	Type* mReturnType;

	std::vector<Type*> mLocalTypes;
public:
	std::vector<Instruction> instructions;
	std::vector<unsigned char> generatedCode;
	std::vector<std::deque<Type*>> instructionOperandTypes;	

	//Creates a new function
	Function(std::string name, std::vector<Type*> arguments, Type* returnType);

	std::string name() const;

	const std::vector<Type*>& arguments() const;
	int numArgs() const;

	Type* returnType() const;

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