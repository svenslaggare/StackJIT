#pragma once
#include "instructions.h"
#include "codegenerator.h"
#include <vector>
#include <deque>
#include <string>
#include <functional>

class Type;
class MemoryManager;
class FunctionCompilationData;
class VMState;
class CallingConvention;
class ExceptionHandling;

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
	//The instructions
	std::vector<Instruction> instructions;

	//The generated code
	std::vector<unsigned char> generatedCode;

	//Creates a new function
	Function(std::string name, std::vector<const Type*> arguments, const Type* returnType, bool isMemberFunction = false, bool isConstructor = false);

	//The name of the function
	std::string name() const;

	//The arguments
	const std::vector<const Type*>& arguments() const;

	//The number of arguments
	std::size_t numArgs() const;

	//The return type
	const Type* returnType() const;

	//Indicates if the function is a member function
	bool isMemberFunction() const;

	//Indicates if the function is a constructor
	bool isConstructor() const;

	//The number of locals
	std::size_t numLocals() const;

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
	std::vector<const Type*> mArguments;
	const Type* mReturnType;

	long mEntryPoint;
	int mFunctionSize;

	bool mIsManaged;
	bool mIsMemberFunction;

	bool mIsMacroFunction;
	MacroFunction mMacroFunction;
public:
	//Creates a new managed function definition
	FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, long entryPoint, int funcSize, bool isMemberFunction = false);

	//Creates a new external function definition
	FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, long entryPoint);

	//Creates a new macro function definition
	FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, MacroFunction macroFunction);

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

	//Indicates if the current function is macro
	bool isMacroFunction() const;

	//Returns the macro function
	MacroFunction macroFunction() const;
};