#pragma once
#include "instructions.h"
#include <vector>
#include <deque>
#include <string>

class Type;
class MemoryManager;

//Represents an user defined function
class Function {
private:
	std::string mName;

	const std::vector<const Type*> mArguments;
	const Type* mReturnType;

	std::vector<const Type*> mLocalTypes;

	std::size_t mStackSize;
	std::size_t mOperandStackSize;

	bool mIsMemberFunction;
	bool mIsConstructor;
public:
	std::vector<Instruction> instructions;
	std::vector<unsigned char> generatedCode;
	std::vector<std::deque<const Type*>> preInstructionOperandTypes;	
	std::vector<std::deque<const Type*>> postInstructionOperandTypes;	

	//Creates a new function
	Function(std::string name, std::vector<const Type*> arguments, const Type* returnType, bool isMemberFunction = false, bool isConstructor = false);

	//The name of the function
	std::string name() const;

	//The arguments
	const std::vector<const Type*>& arguments() const;

	//The number of arguments
	int numArgs() const;

	//The return type
	const Type* returnType() const;

	//Indicates if the function is a member function
	bool isMemberFunction() const;

	//Indicates if the function is a constructor
	bool isConstructor() const;

	//The number of locals
	int numLocals() const;

	//Sets the number of locals
	void setNumLocals(int count);
	
	//Returns the local at the given index
	const Type* getLocal(int index) const;

	//Sets the type for the local at the given index
	void setLocal(int index, const Type* type);

	//The size of the stack
	std::size_t stackSize() const;

	//Sets the size of the stack
	void setStackSize(std::size_t size);

	//The size of the operand stack
	std::size_t operandStackSize() const;

	//Sets the size of the operand stack
	void setOperandStackSize(std::size_t size);
};

//Represents a definition for a function
class FunctionDefinition {
private:
	std::string mName;
	std::vector<const Type*> mArguments;
	const Type* mReturnType;

	long mEntryPoint;
	int mFunctionSize;

	bool mIsManaged;
	bool mIsMemberFunction;
public:
	//Creates a new managed function definition
	FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, long entryPoint, int funcSize, bool isMemberFunction = false);

	//Creates a new external function definition
	FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, long entryPoint);

	FunctionDefinition();

	//Returns the name
	std::string name() const;

	//Returns the type of the return value
	const Type* returnType() const;

	//Returns the types of the arguments
	const std::vector<const Type*>& arguments() const;

	//Indicates if the function is implemented in managed code
	bool isManaged() const;

	//Indicates if the function is a member function
	bool isMemberFunction() const;

	//Sets the function body (for managed functions)
	void setFunctionBody(long entryPoint, int functionSize);

	//The entry point
	long entryPoint() const;

	//The size of the function
	int functionSize() const;

	//Frees the allocted memory for the function (if managed)
	void deleteCodeMemory(MemoryManager& memoryManager);
};