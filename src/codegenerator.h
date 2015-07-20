#pragma once
#include "amd64.h"

class FunctionCompilationData;
class VMState;
struct Instruction;
class CallingConvention;
class MemoryManager;
class Function;

//Handles exceptions
class ExceptionHandling {
private:
	unsigned char* mNullCheckHandler;
	unsigned char* mArrayBoundsCheckHandler;
	unsigned char* mArrayCreationCheckHandler;
public:
	//Generates the exception handlers
	void generateHandlers(MemoryManager& memoryManger);

	//Adds a null check
	void addNullCheck(FunctionCompilationData& function, Registers refReg = Registers::AX, Registers cmpReg = Registers::SI) const;

	//Adds an array bounds check
	void addArrayBoundsCheck(FunctionCompilationData& function) const;

	//Adds an array creation check
	void addArrayCreationCheck(FunctionCompilationData& function) const;
};

//Manages the operand stack
namespace OperandStack {
	//Pops an operand from the operand stack to the given register
	void popReg(Function& function, int operandStackIndex, Registers reg);
	void popReg(Function& function, int operandStackIndex, NumberedRegisters reg);
	void popReg(Function& function, int operandStackIndex, FloatRegisters reg);

	//Pushes the given register to the operand stack
	void pushReg(Function& function, int operandStackIndex, Registers reg);
	void pushReg(Function& function, int operandStackIndex, FloatRegisters reg);

	//Pushes the given value to the operand stack
	void pushInt(Function& function, int operandStackIndex, int value);
}

//Represents a code generator
class CodeGenerator {
private:
	const CallingConvention& mCallingConvention;
	const ExceptionHandling& mExceptionHandling;

	//Zeroes the locals
	void zeroLocals(FunctionCompilationData& functionData);
public:
	//Creates a new code generator
	CodeGenerator(const CallingConvention& callingConvention, const ExceptionHandling& exceptionHandling);

	//Generates a call to the given function
	void generateCall(CodeGen& codeGen, long funcPtr, Registers addrReg = Registers::AX);

	//Generates a call to the garbage collect runtime function
	void generateGCCall(CodeGen& generatedCode, Function& function, int instIndex);

	//Initializes the given function
	void initializeFunction(FunctionCompilationData& functionData);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
};