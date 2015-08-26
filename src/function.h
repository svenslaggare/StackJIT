#pragma once
#include "instructions.h"
#include <vector>
#include <string>
#include <functional>

class Type;
class MemoryManager;
struct FunctionCompilationData;
class VMState;
class CallingConvention;
class ExceptionHandling;

//Represents an user defined function
class Function {
private:
	std::string mName;

	const std::vector<const Type*> mParameters;
	const Type* mReturnType;

	std::vector<const Type*> mLocalTypes;

	std::size_t mStackSize;
	std::size_t mOperandStackSize;

	bool mIsMemberFunction;
	bool mIsConstructor;
public:
	//The instructions
	std::vector<Instruction> instructions;

	//The generated code
	std::vector<unsigned char> generatedCode;

	//Creates a new function
	Function(
		std::string name,
		std::vector<const Type*> parameters,
		const Type* returnType,
		bool isMemberFunction = false,
		bool isConstructor = false);

	//The name of the function
	std::string name() const;

	//The parameters
	const std::vector<const Type*>& parameters() const;

	//The number of parameters
	std::size_t numParams() const;

	//The return type
	const Type* returnType() const;

	//Indicates if the function is a member function
	bool isMemberFunction() const;

	//Indicates if the function is a constructor
	bool isConstructor() const;

	//The number of locals
	std::size_t numLocals() const;

	//Sets the number of locals
	void setNumLocals(std::size_t count);
	
	//Returns the local at the given index
	const Type* getLocal(std::size_t index) const;

	//Sets the type for the local at the given index
	void setLocal(std::size_t index, const Type* type);

	//The size of the stack
	std::size_t stackSize() const;

	//Sets the size of the stack
	void setStackSize(std::size_t size);

	//The size of the operand stack
	std::size_t operandStackSize() const;

	//Sets the size of the operand stack
	void setOperandStackSize(std::size_t size);
};

//Represents context for a macro function
struct MacroFunctionContext {
	const VMState& vmState;

	const CallingConvention& callingConvention;
	const ExceptionHandling& exceptionHandling;

	FunctionCompilationData& functionData;

	const Instruction& inst;
	const int instIndex;

	MacroFunctionContext(
		const VMState& vmState,
		const CallingConvention& callingConvention,
		const ExceptionHandling& exceptionHandling,
		FunctionCompilationData& functionData,
		const Instruction& inst,
		const int instIndex);
};

//Represents a macro function
using MacroFunction = std::function<void (MacroFunctionContext)>;

//Represents a definition for a function
class FunctionDefinition {
private:
	std::string mName;
	std::vector<const Type*> mParameters;
	const Type* mReturnType;

	unsigned char* mEntryPoint;

	bool mIsManaged;
	bool mIsMemberFunction;

	bool mIsMacroFunction;
	MacroFunction mMacroFunction;
public:
	//Creates a new managed function definition
	FunctionDefinition(
		std::string name,
		std::vector<const Type*> parameters,
		const Type* returnType,
		bool isMemberFunction = false);

	//Creates a new external function definition
	FunctionDefinition(
		std::string name,
		std::vector<const Type*> parameters,
		const Type* returnType,
		unsigned char* entryPoint,
		bool isMemberFunction = false);

	//Creates a new macro function definition
	FunctionDefinition(
		std::string name,
		std::vector<const Type*> parameters,
		const Type* returnType,
		MacroFunction macroFunction);

	FunctionDefinition();

	//Returns the name
	std::string name() const;

	//Returns the type of the return value
	const Type* returnType() const;

	//Returns the types of the arguments
	const std::vector<const Type*>& parameters() const;

	//Indicates if the function is implemented in managed code
	bool isManaged() const;

	//Indicates if the function is a member function
	bool isMemberFunction() const;

	//Sets the entry point
	void setEntryPoint(unsigned char* entryPoint);

	//The entry point
	unsigned char* entryPoint() const;

	//Indicates if the current function is macro
	bool isMacroFunction() const;

	//Returns the macro function
	MacroFunction macroFunction() const;
};