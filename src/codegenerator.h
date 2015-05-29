#pragma once
#include "amd64.h"

class FunctionCompilationData;
class VMState;
struct Instruction;
class CallingConvention;
class MemoryManager;

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

	//Initializes the given function
	void initializeFunction(FunctionCompilationData& functionData);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
};