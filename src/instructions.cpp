#include "instructions.h"

Instruction Instructions::make(OpCodes opCode) {
    Instruction inst;
    inst.OpCode = opCode;
    return inst;
}

Instruction Instructions::makeWithInt(OpCodes opCode, int value) {
    Instruction inst;
    inst.Value.Int = value;
    inst.OpCode = opCode;
    return inst;
}

Instruction Instructions::makeWithFloat(OpCodes opCode, float value) {
    Instruction inst;
    inst.Value.Float = value;
    inst.OpCode = opCode;
    return inst;
}

Instruction Instructions::makeWithStr(OpCodes opCode, std::string value) {
    Instruction inst;
    inst.StrValue = value;
    inst.OpCode = opCode;
    return inst;
}

Instruction Instructions::makeCall(std::string funcName) {
    Instruction inst;
    inst.StrValue = funcName;
    inst.OpCode = OpCodes::CALL;
    return inst;
}