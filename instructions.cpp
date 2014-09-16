#include "instructions.h"

Instruction makeInstruction(OpCodes opCode) {
    Instruction inst;
    inst.OpCode = opCode;
    return inst;
}

Instruction makeInstWithInt(OpCodes opCode, int value) {
    Instruction inst;
    inst.Value = value;
    inst.OpCode = opCode;
    return inst;
}

Instruction makeInstWithStr(OpCodes opCode, std::string value) {
    Instruction inst;
    inst.StrValue = value;
    inst.OpCode = opCode;
    return inst;
}

Instruction makeCall(std::string funcName) {
    Instruction inst;
    inst.StrValue = funcName;
    inst.OpCode = OpCodes::CALL;
    return inst;
}