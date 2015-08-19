#pragma once
#ifdef __unix__
#include "../amd64.h"

//The register for function arguments
namespace RegisterCallArguments {
	const Registers Arg0 = Registers::DI;
	const Registers Arg1 = Registers::SI;
	const Registers Arg2 = Registers::DX;
	const Registers Arg3 = Registers::CX;
	const NumberedRegisters Arg4 = NumberedRegisters::R8;
	const NumberedRegisters Arg5 = NumberedRegisters::R9;
}

namespace FloatRegisterCallArguments {
	const FloatRegisters Arg0 = FloatRegisters::XMM0;
	const FloatRegisters Arg1 = FloatRegisters::XMM1;
	const FloatRegisters Arg2 = FloatRegisters::XMM2;
	const FloatRegisters Arg3 = FloatRegisters::XMM3;
	const FloatRegisters Arg4 = FloatRegisters::XMM4;
	const FloatRegisters Arg5 = FloatRegisters::XMM5;
	const FloatRegisters Arg6 = FloatRegisters::XMM6;
	const FloatRegisters Arg7 = FloatRegisters::XMM7;
}

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

	//Calculates how much shadow stack size is needed
	int calculateShadowStackSize(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const;

	//Generates code for handling making return value for a function
	void makeReturnValue(FunctionCompilationData& functionData, int numStackOperands) const;

	//Generates code for handling a return value from a function
	void handleReturnValue(FunctionCompilationData& functionData,
						   const FunctionDefinition& funcToCall,
						   int numStackOperands) const;
};
#endif