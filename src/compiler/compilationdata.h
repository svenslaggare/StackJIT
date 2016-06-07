#pragma once
#include <string>
#include <unordered_map>
#include "amd64.h"

class FunctionDefinition;
class ManagedFunction;

//Represents a branch target
struct BranchTarget {
	//The target of the branch
	const unsigned int target;

	//The size of the branch instruction
	const unsigned int instructionSize;

	//Creates a new branch target
	BranchTarget(unsigned int target, unsigned int instructionSize);
};

enum class FunctionCallType : unsigned char;

//Represents an unresolved function call
struct UnresolvedFunctionCall {
	const FunctionCallType type;

	//The offset for the call instruction
	const std::size_t callOffset;

	//The function to call
	const FunctionDefinition& funcToCall;

	//Creates a new unresolved function call
	UnresolvedFunctionCall(FunctionCallType type, std::size_t callOffset, const FunctionDefinition& funcToCall);
};

//Manages the operand stack
class OperandStack {
private:
	ManagedFunction& mFunction;
	int mTopIndex = -1;

	//Asserts that the stack is not empty
	void assertNotEmpty();

	//Calculates the offset in the stack frame for the given stack operand
	int getStackOperandOffset(int operandIndex);
public:
	//Creates a new operand stack for the given function
	OperandStack(ManagedFunction& function);

	//Reserves space for an operand on the stack
	void reserveSpace();

	//Duplicates the top operand
	void duplicate();

	//Pops an operand from the operand stack to the given register
	void popReg(Registers reg);
	void popReg(ExtendedRegisters reg);
	void popReg(FloatRegisters reg);

	//Pushes the given register to the operand stack
	void pushReg(Registers reg);
	void pushReg(FloatRegisters reg);

	//Pushes the given value to the operand stack
	void pushInt(int value, bool increaseStack = true);
};

//Holds compilation data for a function
struct FunctionCompilationData {
	ManagedFunction& function;
	OperandStack operandStack;

	//Unresolved branches
	std::unordered_map<std::size_t, BranchTarget> unresolvedBranches;

	//Unresolved native branches
	std::unordered_map<std::size_t, PtrValue> unresolvedNativeBranches;

	//Mapping from instruction number to native instruction offset
	std::vector<std::size_t> instructionNumMapping;

	//Unresolved function calls
	std::vector<UnresolvedFunctionCall> unresolvedCalls;

	//Holds compilation data for the given function
	FunctionCompilationData(ManagedFunction& function);
};
