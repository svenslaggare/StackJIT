#include "instructions.h"

Instruction::Instruction()
    : opCode(OpCodes::NOP), floatValue(0), intValue(0), charValue(0) {

}

Instruction::Instruction(OpCodes opCode)
    : opCode(opCode), floatValue(0), intValue(0), charValue(0) {

}

bool Instruction::hasEliminatedNullCheck() const {
    return mHasEliminatedNullCheck;
}

void Instruction::eliminateNullCheck() {
    mHasEliminatedNullCheck = true;
}