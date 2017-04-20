#pragma once
#include <string>
#include <unordered_map>
#include "x64/amd64.h"
#include "x64/amd64assembler.h"

namespace stackjit {
	class FunctionDefinition;
	class ManagedFunction;
	enum class FunctionCallType : unsigned char;

	//Represents a branch target
	struct BranchTarget {
		//The target of the branch
		const unsigned int target;

		//The size of the branch instruction
		const unsigned int instructionSize;

		//Creates a new branch target
		BranchTarget(unsigned int target, unsigned int instructionSize);
	};

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
		Amd64Assembler mAssembler;
		int mTopIndex = -1;

		//Asserts that the stack is not empty
		void assertNotEmpty();
	public:
		//Creates a new operand stack for the given function
		OperandStack(ManagedFunction& function);

		//Returns the index of the top
		int topIndex() const;

		//Calculates the offset in the stack frame for the given stack operand
		int getStackOperandOffset(int operandIndex);

		//Reserves space for an operand on the stack
		void reserveSpace();

		//Duplicates the top operand
		void duplicate();

		//Pops an operand from the operand stack to the given register
		void popReg(IntRegister reg);
		void popReg(FloatRegisters reg);

		//Pushes the given register to the operand stack
		void pushReg(IntRegister reg);
		void pushReg(FloatRegisters reg);

		//Pushes the given value to the operand stack
		void pushInt(int value, bool increaseStack = true);
	};

	//Holds compilation data for a function
	struct FunctionCompilationData {
		ManagedFunction& function;
		OperandStack operandStack;
		Amd64Assembler assembler;

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
}
