#include "instruction.h"

Instruction::Instruction()
    : mOpCode(OpCodes::NOP), floatValue(0), intValue(0), charValue(0) {

}

Instruction::Instruction(OpCodes opCode)
    : mOpCode(opCode), floatValue(0), intValue(0), charValue(0) {

}

OpCodes Instruction::opCode() const {
	return mOpCode;
}

const std::vector<const Type*>& Instruction::operandTypes() const {
	return mOperandTypes;
}

void Instruction::setOperandTypes(const std::vector<const Type*>& operandTypes) {
	mOperandTypes = operandTypes;
}