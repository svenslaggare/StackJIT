#pragma once
#include <functional>

class FunctionCompilationData;
class FunctionDefinition;
class Type;

//Represents a function for the getting the type of an argument
using GetArgumentType = std::function<const Type*(int)>;

//Represents a calling convention
class CallingConvention {
public:
	//Moves the argument to the stack for the given function
	virtual void moveArgsToStack(FunctionCompilationData& functionData) const = 0;

	//Generates code for calling with the given argument
	virtual void callFunctionArgument(FunctionCompilationData& functionData,
									  int argIndex, const Type* argType, const FunctionDefinition& funcToCall) const = 0;

	//Generates code for calling the given function
	virtual void callFunctionArguments(FunctionCompilationData& functionData,
									   const FunctionDefinition& funcToCall, GetArgumentType getArgumentType) const = 0;

	//Generates code for returning a value from a function
	virtual void returnValue(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const = 0;
};