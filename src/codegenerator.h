#pragma once
#include "amd64.h"
#include <string>

struct FunctionCompilationData;
class VMState;
class Instruction;
class CallingConvention;
class MemoryManager;
class Function;
class ExceptionHandling;
class FunctionDefinition;

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

	//Indicates if the given function needs to be compiled at runtime
	bool compileAtRuntime(const VMState& vmState, const FunctionDefinition& funcToCall, std::string funcSignature);

	//Zeroes the locals
	void zeroLocals(FunctionCompilationData& functionData);

	//Pushes a function to the call stack
	void pushFunc(const VMState& vmState, FunctionCompilationData& functionData, int instIndex);

	//Pops a function from the call stack
	void popFunc(const VMState& vmState, CodeGen& generatedCode);
public:
	//Creates a new code generator
	CodeGenerator(const CallingConvention& callingConvention, const ExceptionHandling& exceptionHandling);

	//Generates a call to the given function
	void generateCall(CodeGen& codeGen, unsigned char* funcPtr, Registers addrReg = Registers::AX);

	//Generates a call to the garbage collect runtime function
	void generateGCCall(CodeGen& generatedCode, Function& function, int instIndex);

	//Initializes the given function
	void initializeFunction(FunctionCompilationData& functionData);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
};