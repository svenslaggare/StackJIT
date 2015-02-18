#pragma once

class FunctionCompilationData;
class VMState;
class Function;
struct Instruction;
class CallingConvention;

//Represents a code generator
class CodeGenerator {
private:
	const CallingConvention& mCallingConvention;

	//Zeroes the locals
	void zeroLocals(FunctionCompilationData& functionData);
public:
	//Creates a new code generator
	CodeGenerator(const CallingConvention& callingConvention);

	//Initalizes the given function
	void initalizeFunction(FunctionCompilationData& functionData);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
};