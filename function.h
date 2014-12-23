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

	std::string name() const;

	const std::vector<const Type*>& arguments() const;
	int numArgs() const;

	const Type* returnType() const;

	int numLocals() const;
	void setNumLocals(int count);
	
	const Type* getLocal(int index) const;
	void setLocal(int index, const Type* type);

	int stackSize() const;
	void setStackSize(int size);
};

//Represents a definition for a function
class FunctionDefinition {
private:
	long mEntryPoint;
	int mFunctionSize;

	bool mIsManaged;

	const Type* mReturnType;
	std::vector<const Type*> mArguments;
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

	//Frees the allocted memory for the function (if mananaged)
	void deleteCodeMemory();
};