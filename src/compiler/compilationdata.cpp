#include "compilationdata.h"
#include "../core/function.h"
#include "../helpers.h"

namespace stackjit {
	BranchTarget::BranchTarget(unsigned int target, unsigned int instructionSize)
		: target(target), instructionSize(instructionSize) {

	}

	UnresolvedFunctionCall::UnresolvedFunctionCall(FunctionCallType type,
												   std::size_t callOffset,
												   const FunctionDefinition& funcToCall)
		: type(type), callOffset(callOffset), funcToCall(funcToCall) {

	}

	FunctionCompilationData::FunctionCompilationData(ManagedFunction& function)
		: function(function), operandStack(function) {

	}

	OperandStack::OperandStack(ManagedFunction& function)
		: mFunction(function) {

	}

	int OperandStack::topIndex() const {
		return mTopIndex;
	}

	void OperandStack::assertNotEmpty() {
		if (mTopIndex <= -1) {
			throw std::runtime_error("The operand stack is empty");
		}
	}

	int OperandStack::getStackOperandOffset(int operandIndex) {
		return -(int)(Amd64Backend::REGISTER_SIZE *
					  (1 + mFunction.def().numParams() + mFunction.numLocals() + operandIndex));
	}

	void OperandStack::reserveSpace() {
		mTopIndex++;
	}

	void OperandStack::duplicate() {
		assertNotEmpty();

		Amd64Assembler assembler(mFunction.generatedCode());
		int stackOffset1 = getStackOperandOffset(mTopIndex);
		int stackOffset2 = getStackOperandOffset(mTopIndex + 1);
		assembler.move(Registers::AX, { Registers::BP, stackOffset1 });
		assembler.move({ Registers::BP, stackOffset2 }, Registers::AX);
		mTopIndex++;
	}

	void OperandStack::popReg(IntRegister reg) {
		assertNotEmpty();

		Amd64Assembler assembler(mFunction.generatedCode());
		int stackOffset = getStackOperandOffset(mTopIndex);
		assembler.move(reg, { Registers::BP, stackOffset });
		mTopIndex--;
	}

	void OperandStack::popReg(FloatRegisters reg) {
		assertNotEmpty();

		Amd64Assembler assembler(mFunction.generatedCode());
		int stackOffset = getStackOperandOffset(mTopIndex);
		assembler.move(reg, { Registers::BP, stackOffset });
		mTopIndex--;
	}

	void OperandStack::pushReg(IntRegister reg) {
		mTopIndex++;

		Amd64Assembler assembler(mFunction.generatedCode());
		int stackOffset = getStackOperandOffset(mTopIndex);
		assembler.move({ Registers::BP, stackOffset }, reg);
	}

	void OperandStack::pushReg(FloatRegisters reg) {
		mTopIndex++;

		Amd64Assembler assembler(mFunction.generatedCode());
		int stackOffset = getStackOperandOffset(mTopIndex);
		assembler.move({ Registers::BP, stackOffset }, reg);
	}

	void OperandStack::pushInt(int value, bool increaseStack) {
		if (increaseStack) {
			mTopIndex++;
		}

		Amd64Assembler assembler(mFunction.generatedCode());
		int stackOffset = getStackOperandOffset(mTopIndex);
		assembler.move({ Registers::BP, stackOffset }, value);
	}
}
