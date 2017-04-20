#ifdef __unix__
#include "callingconvention.h"
#include "../compiler/callingconvention.h"
#include "../compiler/jit.h"
#include "../core/function.h"
#include "../type/type.h"
#include "../compiler/x64/amd64assembler.h"
#include <iostream>

namespace stackjit {
	namespace {
		//The maximum number of register for argument passing
		const int NUM_NONE_FLOAT_ARGUMENT_REGISTERS = 6;
		const int NUM_FLOAT_ARGUMENT_REGISTERS = 8;

		const std::vector<IntRegister> INT_CALL_ARGUMENTS = {
			RegisterCallArguments::Arg0,
			RegisterCallArguments::Arg1,
			RegisterCallArguments::Arg2,
			RegisterCallArguments::Arg3,
			RegisterCallArguments::Arg4,
			RegisterCallArguments::Arg5,
		};

		const std::vector<FloatRegisters> FLOAT_CALL_ARGUMENTS = {
			FloatRegisterCallArguments::Arg0,
			FloatRegisterCallArguments::Arg1,
			FloatRegisterCallArguments::Arg2,
			FloatRegisterCallArguments::Arg3,
			FloatRegisterCallArguments::Arg4,
			FloatRegisterCallArguments::Arg5,
			FloatRegisterCallArguments::Arg6,
			FloatRegisterCallArguments::Arg7,
		};

		//Returns the float argument index for the given argument index
		int getFloatArgIndex(const std::vector<const Type*>& parameters, int argIndex) {
			int floatArgIndex = 0;

			int index = 0;
			for (auto param : parameters) {
				if (index == argIndex) {
					break;
				}

				if (TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
					floatArgIndex++;
				}

				index++;
			}

			return floatArgIndex;
		}

		//Returns the none float arg for the given argument index
		int getNoneFloatArgIndex(const std::vector<const Type*>& parameters, int argIndex) {
			int noneFloatArgIndex = 0;

			int index = 0;
			for (auto param : parameters) {
				if (index == argIndex) {
					break;
				}

				if (!TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
					noneFloatArgIndex++;
				}

				index++;
			}

			return noneFloatArgIndex;
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
			auto& parameters = functionData.function.def().parameters();

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
			Amd64Assembler assembler(function.generatedCode());

			int argStackOffset = -(1 + argIndex) * Amd64Backend::REGISTER_SIZE;

			if (relativeArgIndex >= NUM_NONE_FLOAT_ARGUMENT_REGISTERS) {
				int stackArgIndex = getStackArgumentIndex(functionData, argIndex);
				assembler.move(Registers::AX, { Registers::BP, Amd64Backend::REGISTER_SIZE * (stackArgIndex + 2) });
				assembler.move({ Registers::BP, argStackOffset }, Registers::AX);
			} else {
				assembler.move({ Registers::BP, argStackOffset }, INT_CALL_ARGUMENTS[relativeArgIndex]);
			}
		}

		//Moves a relative float argument to the stack. The argument is relative to the type of the register.
		void moveFloatArgToStack(FunctionCompilationData& functionData, int argIndex, int relativeArgIndex) {
			auto& function = functionData.function;
			Amd64Assembler assembler(function.generatedCode());

			int argStackOffset = -(1 + argIndex) * Amd64Backend::REGISTER_SIZE;

			if (relativeArgIndex >= NUM_FLOAT_ARGUMENT_REGISTERS) {
				int stackArgIndex = getStackArgumentIndex(functionData, argIndex);
				assembler.move(Registers::AX, { Registers::BP, Amd64Backend::REGISTER_SIZE * (stackArgIndex + 2) });
				assembler.move({ Registers::BP, argStackOffset }, Registers::AX);
			} else {
				assembler.move({ Registers::BP, argStackOffset }, FLOAT_CALL_ARGUMENTS[relativeArgIndex]);
			}
		}
	}

	void CallingConvention::moveArgsToStack(FunctionCompilationData& functionData) const {
		auto& function = functionData.function;
		auto& parameters = function.def().parameters();

		for (int arg = (int)function.def().numParameters() - 1; arg >= 0; arg--) {
			if (TypeSystem::isPrimitiveType(function.def().parameters()[arg], PrimitiveTypes::Float)) {
				moveFloatArgToStack(functionData, arg, getFloatArgIndex(parameters, arg));
			} else {
				moveNoneFloatArgToStack(functionData, arg, getNoneFloatArgIndex(parameters, arg));
			}
		}
	}

	void CallingConvention::callFunctionArgument(FunctionCompilationData& functionData,
												 int argIndex,
												 const Type* argType,
												 const FunctionDefinition& funcToCall) const {
		auto& generatedCode = functionData.function.generatedCode();
		auto& operandStack = functionData.operandStack;
		Amd64Assembler assembler(generatedCode);

		if (TypeSystem::isPrimitiveType(argType, PrimitiveTypes::Float)) {
			//Arguments of index >= 8 are passed via the stack.
			int relativeIndex = getFloatArgIndex(funcToCall.parameters(), argIndex);

			if (relativeIndex >= NUM_FLOAT_ARGUMENT_REGISTERS) {
				//Move from the operand stack to the normal stack
				operandStack.popReg(Registers::AX);
				assembler.push(Registers::AX);
			} else {
				operandStack.popReg(FLOAT_CALL_ARGUMENTS[relativeIndex]);
			}
		} else {
			//Arguments of index >= 6 are passed via the stack
			int relativeIndex = getNoneFloatArgIndex(funcToCall.parameters(), argIndex);

			if (relativeIndex >= NUM_NONE_FLOAT_ARGUMENT_REGISTERS) {
				//Move from the operand stack to the normal stack
				operandStack.popReg(Registers::AX);
				assembler.push(Registers::AX);
			} else {
				operandStack.popReg(INT_CALL_ARGUMENTS[relativeIndex]);
			}
		}
	}

	void CallingConvention::callFunctionArguments(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const {
		int numArgs = (int)funcToCall.parameters().size();

		//Set the function arguments
		for (int arg = numArgs - 1; arg >= 0; arg--) {
			callFunctionArgument(functionData, arg, funcToCall.parameters().at((std::size_t)arg), funcToCall);
		}
	}

	int CallingConvention::calculateStackAlignment(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const {
		int numStackArgs = numStackArguments(funcToCall.parameters());
		return (numStackArgs % 2) * Amd64Backend::REGISTER_SIZE;
	}

	int CallingConvention::calculateShadowStackSize() const {
		return 0;
	}

	void CallingConvention::makeReturnValue(FunctionCompilationData& functionData) const {
		auto& function = functionData.function;
		auto& operandStack = functionData.operandStack;

		if (!TypeSystem::isPrimitiveType(function.def().returnType(), PrimitiveTypes::Void)) {
			//Pop the return value
			if (TypeSystem::isPrimitiveType(function.def().returnType(), PrimitiveTypes::Float)) {
				operandStack.popReg(FloatRegisterCallArguments::ReturnValue);
			} else {
				operandStack.popReg(RegisterCallArguments::ReturnValue);
			}
		}
	}

	void CallingConvention::handleReturnValue(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const {
		auto& generatedCode = functionData.function.generatedCode();
		auto& operandStack = functionData.operandStack;
		Amd64Assembler assembler(generatedCode);

		//If we have passed arguments via the stack, adjust the stack pointer.
		int numStackArgs = numStackArguments(funcToCall.parameters());

		if (numStackArgs > 0) {
			assembler.add(Registers::SP, numStackArgs * Amd64Backend::REGISTER_SIZE);
		}

		if (!TypeSystem::isPrimitiveType(funcToCall.returnType(), PrimitiveTypes::Void)) {
			//Push the return value
			if (TypeSystem::isPrimitiveType(funcToCall.returnType(), PrimitiveTypes::Float)) {
				operandStack.pushReg(FloatRegisterCallArguments::ReturnValue);
			} else {
				operandStack.pushReg(RegisterCallArguments::ReturnValue);
			}
		}
	}
}
#endif
