#pragma once
#include <vector>
#include <deque>
#include <string>
#include "instructions.h"

class Type;

//Represents an user defined function
class Function {
private:
	std::string mName;

	const std::vector<const Type*> mArguments;
	const Type* mReturnType;

	std::vector<const Type*> mLocalTypes;

	int mStackSize;
public:
	std::vector<Instruction> instructions;
	std::vector<unsigned char> generatedCode;
	std::vector<std::deque<const Type*>> instructionOperandTypes;	
	std::vector<std::deque<const Type*>> postInstructionOperandTypes;	

	//Creates a new function
	Function(std::string name, std::vector<const Type*> arguments, const Type* returnType);

	//The name of the function
	std::string name() const;

	//The arguments
	const std::vector<const Type*>& arguments() const;

	//The number of arguments
	int numArgs() const;

	//The return type
	const Type* returnType() const;

	//The number of locals
	int numLocals() const;

	//Sets the number of locals
	void setNumLocals(int count);
	
	//Returns the local at the given index
	const Type* getLocal(int index) const;

	//Sets the type for the local at the given index
	void setLocal(int index, const Type* type);

	//The size of the stack
	int stackSize() const;

	//Sets the size of the stack
	void setStackSize(int size);
};

//Represents a definition for a function
class FunctionDefinition {
private:
	std::vector<const Type*> mArguments;
	const Type* mReturnType;

	long mEntryPoint;
	int mFunctionSize;

	bool mIsManaged;
public:
	//Creates a new managed function definition
	FunctionDefinition(std::vector<const Type*> arguments, const Type* returnType, long entryPoint, int funcSize);

	//Creates a new external function definition
	FunctionDefinition(std::vector<const Type*> arguments, const Type* returnType, long entryPoint);

	FunctionDefinition();

	//Returns the type of the return value
	const Type* returnType() const;

	//Returns the types of the arguments
	const std::vector<const Type*>& arguments() const;

	//Sets the function body (for managed functions)
	void setFunctionBody(long entryPoint, int functionSize);

	//Indicates if the function is implemented in managed code
	bool isManaged() const;

	//The entry point
	long entryPoint() const;

	//The size of the function
	int functionSize() const;

	//Frees the allocted memory for the function (if managed)
	void deleteCodeMemory();
};