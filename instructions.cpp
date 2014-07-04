#include "instructions.h"

Instruction makeInstruction(OpCodes opCode) {
    Instruction inst;
    inst.OpCode = opCode;
    return inst;
}

Instruction makePushInt(int value) {
    Instruction inst;
    inst.OpCode = OpCodes::PUSH_INT;
    inst.Value = value;
    return inst;
}

Instruction makeLoadLocal(int local) {
    Instruction inst;
    inst.Value = local;
    inst.OpCode = OpCodes::LOAD_LOCAL;
    return inst;
}

Instruction makeStoreLocal(int local) {
    Instruction inst;
    inst.Value = local;
    inst.OpCode = OpCodes::STORE_LOCAL;
    return inst;
}

Instruction makeCall(std::string funcName, int numArgs) {
    Instruction inst;
    inst.StrValue = funcName;
    inst.Value = numArgs;
    inst.OpCode = OpCodes::CALL;
    return inst;
}

Instruction makeLoadArg(int argNum) {
    Instruction inst;
    inst.Value = argNum;
    inst.OpCode = OpCodes::LOAD_ARG;
    return inst;
}