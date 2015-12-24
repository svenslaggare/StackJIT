#pragma once
#include <stack>
#include <string>
#include "../vmstate.h"
#include "../core/instruction.h"

class ManagedFunction;
class VMState;
class Type;

typedef std::stack<const Type*> InstructionTypes;

//Represents a branch check
struct BranchCheck {
	const std::size_t source;
	const std::size_t target;
	const InstructionTypes branchTypes;

	BranchCheck(std::size_t source, std::size_t target, InstructionTypes branchTypes)
		: source(source), target(target), branchTypes(branchTypes) {

	}
};

//Verifies the semantics of functions
class Verifier {
private:
	VMState& mVMState;

	const Type* mIntType;
	const Type* mFloatType;
	const Type* mBoolType;
	const Type* mCharType;
	const Type* mVoidType;
	const Type* mNullType;
	const Type* mStringType;

	//Verifies the given instruction
	void verifyInstruction(ManagedFunction& function, Instruction inst, std::size_t index,
						   InstructionTypes& operandStack, std::vector<BranchCheck>& branches);
public:
	Verifier(VMState& vmState);

	//Verifies the given function
	void verifyFunction(ManagedFunction& function);
};