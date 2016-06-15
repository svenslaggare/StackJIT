#include "instruction.h"

namespace stackjit {
	Instruction::Instruction()
	    : mOpCode(OpCodes::NOP), floatValue(0), intValue(0), charValue(0) {

	}

	Instruction::Instruction(OpCodes opCode)
	    : mOpCode(opCode), floatValue(0), intValue(0), charValue(0) {

	}

	OpCodes Instruction::opCode() const {
		return mOpCode;
	}

	bool Instruction::isCallInstance() const {
		return mOpCode == OpCodes::CALL_INSTANCE || mOpCode == OpCodes::CALL_VIRTUAL;
	}

	const std::vector<const Type*>& Instruction::operandTypes() const {
		return mOperandTypes;
	}

	void Instruction::setOperandTypes(const std::vector<const Type*>& operandTypes) {
		mOperandTypes = operandTypes;
	}
}
