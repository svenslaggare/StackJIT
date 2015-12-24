#pragma once
#include "instruction.h"
#include "../type/classmetadata.h"
#include <vector>
#include <string>
#include <functional>

class Type;
class ClassType;
class MemoryManager;
struct FunctionCompilationData;
class VMState;
class CallingConvention;
class ExceptionHandling;

//Represents a definition for a function
class FunctionDefinition {
private:
	std::string mName;
	std::vector<const Type*> mParameters;
	const Type* mReturnType;

	unsigned char* mEntryPoint;

	bool mIsManaged;

	bool mIsMemberFunction;
	const ClassType* mClassType;
	AccessModifier mAccessModifier;
	bool mIsConstructor;
public:
	//Creates a new managed function definition
	FunctionDefinition(
		std::string name,
		std::vector<const Type*> parameters,
		const Type* returnType,
	    const ClassType* classType = nullptr,
	    AccessModifier accessModifier = ClassMetadata::DEFAULT_ACCESS_MODIFIER,
		bool isConstructor = false);

	//Creates a new external function definition
	FunctionDefinition(
		std::string name,
		std::vector<const Type*> parameters,
		const Type* returnType,
		unsigned char* entryPoint,
		const ClassType* classType = nullptr,
		AccessModifier accessModifier = ClassMetadata::DEFAULT_ACCESS_MODIFIER,
		bool isConstructor = false);

	FunctionDefinition();

	//Returns the name
	std::string name() const;

	//Returns the type of the return value
	const Type* returnType() const;

	//Returns the types of the arguments
	const std::vector<const Type*>& parameters() const;

	//The number of parameters
	std::size_t numParams() const;

	//Indicates if the function is implemented in managed code
	bool isManaged() const;

	//Indicates if the function is a member function
	bool isMemberFunction() const;

	//Returns the type of the class if a member function
	const ClassType* classType() const;

	//Returns the access modifier
	AccessModifier accessModifier() const;

	//Indicates if the function is a constructor
	bool isConstructor() const;

	//Sets the entry point
	void setEntryPoint(unsigned char* entryPoint);

	//The entry point
	unsigned char* entryPoint() const;
};

//Represents an user defined function
class ManagedFunction {
private:
	const FunctionDefinition& mDefinition;
	std::vector<const Type*> mLocalTypes;
	std::size_t mOperandStackSize;
	std::vector<Instruction> mInstructions;
	std::vector<unsigned char> mGeneratedCode;
public:
	//Creates a new managed function
	ManagedFunction(const FunctionDefinition& definition);

	//Returns the definition of the function
	const FunctionDefinition& def() const;

	//Returns the instructions
	std::vector<Instruction>& instructions();
	const std::vector<Instruction>& instructions() const;

	//Returns the generated code
	std::vector<unsigned char>& generatedCode();
	const std::vector<unsigned char>& generatedCode() const;

	//The number of locals
	std::size_t numLocals() const;

	//Sets the number of locals
	void setNumLocals(std::size_t count);

	//Returns the local at the given index
	const Type* getLocal(std::size_t index) const;

	//Sets the type for the local at the given index
	void setLocal(std::size_t index, const Type* type);

	//The size of the operand stack
	std::size_t operandStackSize() const;

	//Sets the size of the operand stack
	void setOperandStackSize(std::size_t size);
};