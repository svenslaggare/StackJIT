#include "instructions.h"

Instruction::Instruction()
    : mOpCode(OpCodes::NOP), floatValue(0), intValue(0), charValue(0) {

}

Instruction::Instruction(OpCodes opCode)
    : mOpCode(opCode), floatValue(0), intValue(0), charValue(0) {

}

OpCodes Instruction::opCode() const {
	return mOpCode;
}

bool Instruction::hasEliminatedNullCheck() const {
    return mHasEliminatedNullCheck;
}

void Instruction::eliminateNullCheck() {
    mHasEliminatedNullCheck = true;
}

const std::deque<const Type*>& Instruction::operandTypes() const {
	return mOperandTypes;
}

void Instruction::setOperandTypes(std::deque<const Type*> operandTypes) {
	mOperandTypes = operandTypes;
}