#pragma once
#include <functional>

struct FunctionCompilationData;
class FunctionDefinition;
class Type;

//Represents a calling convention
class CallingConvention {
public:
	//Moves the argument to the stack for the given function
	virtual void moveArgsToStack(FunctionCompilationData& functionData) const = 0;

	//Generates code for calling with the given argument
	virtual void callFunctionArgument(FunctionCompilationData& functionData,
									  int argIndex, const Type* argType, const FunctionDefinition& funcToCall,
									  int numStackOperands) const = 0;

	//Generates code for calling the given function
	virtual void callFunctionArguments(FunctionCompilationData& functionData,
									   const FunctionDefinition& funcToCall, int numStackOperands) const = 0;

	//Calculates how much the stack must be aligned to perform the call
	virtual int calculateStackAlignment(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const = 0;

	//Generates code for handling making return value for a function
	virtual void makeReturnValue(FunctionCompilationData& functionData, int numStackOperands) const = 0;

	//Generates code for handling a return value from a function
	virtual void handleReturnValue(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall,
								   int numStackOperands) const = 0;
};