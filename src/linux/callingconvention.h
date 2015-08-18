#pragma once
#ifdef __unix__

struct FunctionCompilationData;
class FunctionDefinition;
class Type;

//Represents calling conventions
class CallingConvention {
public:
	//Moves the argument to the stack for the given function
	void moveArgsToStack(FunctionCompilationData& functionData) const;

	//Generates code for calling with the given argument
	void callFunctionArgument(FunctionCompilationData& functionData,
							  int argIndex,
							  const Type* argType,
							  const FunctionDefinition& funcToCall,
							  int numStackOperands) const;

	//Generates code for calling the given function
	void callFunctionArguments(FunctionCompilationData& functionData,
							   const FunctionDefinition& funcToCall,
							   int numStackOperands) const;

	//Calculates how much the stack must be aligned to perform the call
	int calculateStackAlignment(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const;

	//Generates code for handling making return value for a function
	void makeReturnValue(FunctionCompilationData& functionData, int numStackOperands) const;

	//Generates code for handling a return value from a function
	void handleReturnValue(FunctionCompilationData& functionData,
						   const FunctionDefinition& funcToCall,
						   int numStackOperands) const;
};
#endif