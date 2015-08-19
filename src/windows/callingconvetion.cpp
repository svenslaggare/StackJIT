#if defined(_WIN64) || defined(__MINGW32__)
#include "callingconvention.h"
#include "../amd64.h"
#include "../jit.h"
#include "../function.h"
#include "../type.h"
#include <iostream>

namespace {
	//The maximum number of register for argument passing
	const int NUM_NONE_FLOAT_ARGUMENT_REGISTERS = 4;
	const int NUM_FLOAT_ARGUMENT_REGISTERS = 4;

	//Returns the float argument index for the given argument index
	int getFloatArgIndex(const std::vector<const Type*>& parameters, int argIndex) {
		return argIndex;
	}

	//Returns the none float arg for the given argument index
	int getNoneFloatArgIndex(const std::vector<const Type*>& parameters, int argIndex) {
		return argIndex;
	}

	//Calculates the number of arguments that are passed via the stack
	int numStackArguments(const std::vector<const Type*>& parameters) {
		int stackArgs = 0;

		int argIndex = 0;
		for (auto param : parameters) {
			if (TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
				if (getFloatArgIndex(parameters, argIndex) >= NUM_FLOAT_ARGUMENT_REGISTERS) {
					stackArgs++;
				}
			} else {
				if (getNoneFloatArgIndex(parameters, argIndex) >= NUM_NONE_FLOAT_ARGUMENT_REGISTERS) {
					stackArgs++;
				}
			}

			argIndex++;
		}

		return stackArgs;
	}

	//Returns the stack argument index for the given argument
	int getStackArgumentIndex(FunctionCompilationData& functionData, int argIndex) {
		int stackArgIndex = 0;
		auto& parameters = functionData.function.parameters();

		int index = 0;
		for (auto param : parameters) {
			if (index == argIndex) {
				break;
			}

			if (TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
				if (getFloatArgIndex(parameters, index) >= NUM_FLOAT_ARGUMENT_REGISTERS) {
					stackArgIndex++;
				}
			} else {
				if (getNoneFloatArgIndex(parameters, index) >= NUM_NONE_FLOAT_ARGUMENT_REGISTERS) {
					stackArgIndex++;
				}
			}

			index++;
		}

		return stackArgIndex;
	}

	//Moves a relative none float argument to the stack. The argument is relative to the type of the register.
	void moveNoneFloatArgToStack(FunctionCompilationData& functionData, int argIndex, int relativeArgIndex) {
		auto& function = functionData.function;

		int argStackOffset = -(1 + argIndex) * Amd64Backend::REG_SIZE;

		if (relativeArgIndex >= NUM_NONE_FLOAT_ARGUMENT_REGISTERS) {
			int stackArgIndex = getStackArgumentIndex(functionData, argIndex);
			Amd64Backend::moveMemoryRegWithOffsetToReg(
				function.generatedCode,
				Registers::AX,
				Registers::BP,
				Amd64Backend::REG_SIZE * (stackArgIndex + 6)); //mov rax, [rbp+REG_SIZE*<arg offset>]

			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, Registers::AX); //mov [rbp+<arg offset>], rax
		}

		if (relativeArgIndex == 3) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, RegisterCallArguments::Arg3); //mov [rbp+<arg offset>], rcx
		}

		if (relativeArgIndex == 2) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, RegisterCallArguments::Arg2); //mov [rbp+<arg offset>], rdx
		}

		if (relativeArgIndex == 1) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, RegisterCallArguments::Arg1); //mov [rbp+<arg offset>], rsi
		}

		if (relativeArgIndex == 0) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, RegisterCallArguments::Arg0); //mov [rbp+<arg offset>], rdi
		}
	}

	//Moves a relative float argument to the stack. The argument is relative to the type of the register.
	void moveFloatArgToStack(FunctionCompilationData& functionData, int argIndex, int relativeArgIndex) {
		auto& function = functionData.function;

		int argStackOffset = -(1 + argIndex) * Amd64Backend::REG_SIZE;

		if (relativeArgIndex >= NUM_FLOAT_ARGUMENT_REGISTERS) {
			int stackArgIndex = getStackArgumentIndex(functionData, argIndex);
			Amd64Backend::moveMemoryRegWithOffsetToReg(
				function.generatedCode,
				Registers::AX,
				Registers::BP,
				Amd64Backend::REG_SIZE * (stackArgIndex + 6)); //mov rax, [rbp+REG_SIZE*<arg offset>]

			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, Registers::AX); //mov [rbp+<arg offset>], rax
		}

		if (relativeArgIndex == 3) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisterCallArguments::Arg3); //movss [rbp+<arg offset>], xmm3
		}

		if (relativeArgIndex == 2) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisterCallArguments::Arg2); //movss [rbp+<arg offset>], xmm2
		}

		if (relativeArgIndex == 1) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisterCallArguments::Arg1); //movss [rbp+<arg offset>], xmm1
		}

		if (relativeArgIndex == 0) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisterCallArguments::Arg0); //movss [rbp+<arg offset>], xmm0
		}
	}
}

void CallingConvention::moveArgsToStack(FunctionCompilationData& functionData) const {
	auto& function = functionData.function;
	auto& parameters = function.parameters();

	for (int arg = (int)function.numParams() - 1; arg >= 0; arg--) {
		if (TypeSystem::isPrimitiveType(function.parameters()[arg], PrimitiveTypes::Float)) {
			moveFloatArgToStack(functionData, arg, getFloatArgIndex(parameters, arg));
		} else {
			moveNoneFloatArgToStack(functionData, arg, getNoneFloatArgIndex(parameters, arg));
		}
	}
}

void CallingConvention::callFunctionArgument(FunctionCompilationData& functionData,
												  int argIndex, const Type* argType, const FunctionDefinition& funcToCall,
												  int numStackOperands) const {
	auto& generatedCode = functionData.function.generatedCode;
	int numArgs = (int)funcToCall.parameters().size();

	if (TypeSystem::isPrimitiveType(argType, PrimitiveTypes::Float)) {
		//Arguments of index >= 8 are passed via the stack.
		int relativeIndex = getFloatArgIndex(funcToCall.parameters(), argIndex);
		int argOperandOffset = numStackOperands - (numArgs - argIndex);

		if (relativeIndex >= 4) {
			//Move from the operand stack to the normal stack
			OperandStack::popReg(functionData.function, argOperandOffset, Registers::AX);
			Amd64Backend::pushReg(generatedCode, Registers::AX);
		}

		if (relativeIndex == 3) {
			OperandStack::popReg(functionData.function, argOperandOffset, FloatRegisterCallArguments::Arg3);
		}

		if (relativeIndex == 2) {
			OperandStack::popReg(functionData.function, argOperandOffset, FloatRegisterCallArguments::Arg2);
		}

		if (relativeIndex == 1) {
			OperandStack::popReg(functionData.function, argOperandOffset, FloatRegisterCallArguments::Arg1);
		}

		if (relativeIndex == 0) {
			OperandStack::popReg(functionData.function, argOperandOffset, FloatRegisterCallArguments::Arg0);
		}
	} else {
		//Arguments of index >= 6 are passed via the stack
		int relativeIndex = getNoneFloatArgIndex(funcToCall.parameters(), argIndex);
		int argOperandOffset = numStackOperands - (numArgs - argIndex);

		if (relativeIndex >= 4) {
			//Move from the operand stack to the normal stack
			OperandStack::popReg(functionData.function, argOperandOffset, Registers::AX);
			Amd64Backend::pushReg(generatedCode, Registers::AX);
		}

		if (relativeIndex == 3) {
			OperandStack::popReg(functionData.function, argOperandOffset, RegisterCallArguments::Arg3);
		}

		if (relativeIndex == 2) {
			OperandStack::popReg(functionData.function, argOperandOffset, RegisterCallArguments::Arg2);
		}

		if (relativeIndex == 1) {
			OperandStack::popReg(functionData.function, argOperandOffset, RegisterCallArguments::Arg1);
		}

		if (relativeIndex == 0) {
			OperandStack::popReg(functionData.function, argOperandOffset, RegisterCallArguments::Arg0);
		}
	}
}

void CallingConvention::callFunctionArguments(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall,
												   int numStackOperands) const {
	int numArgs = (int)funcToCall.parameters().size();

	//Set the function arguments
	for (int arg = numArgs - 1; arg >= 0; arg--) {
		callFunctionArgument(functionData, arg, funcToCall.parameters().at(arg), funcToCall, numStackOperands);
	}
}

int CallingConvention::calculateStackAlignment(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const {
	int numStackArgs = numStackArguments(funcToCall.parameters());
	return ((numStackArgs % 2) + 0) * Amd64Backend::REG_SIZE;
}

int CallingConvention::calculateShadowStackSize(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const {
	return 4 * Amd64Backend::REG_SIZE;
}

void CallingConvention::makeReturnValue(FunctionCompilationData& functionData,	int numStackOperands) const {
	auto& function = functionData.function;

	if (!TypeSystem::isPrimitiveType(function.returnType(), PrimitiveTypes::Void)) {
		//Pop the return value
		if (TypeSystem::isPrimitiveType(function.returnType(), PrimitiveTypes::Float)) {
			OperandStack::popReg(function, numStackOperands - 1, FloatRegisters::XMM0);
		} else {
			OperandStack::popReg(function, numStackOperands - 1, Registers::AX);
		}
	}
}

void CallingConvention::handleReturnValue(FunctionCompilationData& functionData,
											   const FunctionDefinition& funcToCall,
											   int numStackOperands) const {
	auto& generatedCode = functionData.function.generatedCode;

	//If we have passed arguments via the stack, adjust the stack pointer.
	int numStackArgs = numStackArguments(funcToCall.parameters());

	if (numStackArgs > 0) {
		Amd64Backend::addConstantToReg(generatedCode, Registers::SP, numStackArgs * Amd64Backend::REG_SIZE);
	}

	if (!TypeSystem::isPrimitiveType(funcToCall.returnType(), PrimitiveTypes::Void)) {
		if (TypeSystem::isPrimitiveType(funcToCall.returnType(), PrimitiveTypes::Float)) {
			OperandStack::pushReg(functionData.function, numStackOperands, FloatRegisters::XMM0);
		} else {
			OperandStack::pushReg(functionData.function, numStackOperands, Registers::AX);
		}
	}
}
#endif
