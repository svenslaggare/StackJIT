#pragma once
#include "jit.h"

class FunctionCompilationData;
class VMState;
class Function;
struct Instruction;

//The code generator
namespace CodeGenerator {
	//Initalizes the given function
	void initalizeFunction(FunctionCompilationData& functionData);

	//Moves the arguments to the stack
	void moveArgsToStack(FunctionCompilationData& functionData);

	//Zeroes the locals
	void zeroLocals(FunctionCompilationData& functionData);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
}