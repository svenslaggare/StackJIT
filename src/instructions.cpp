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

Instruction Instructions::makeWithChar(OpCodes opCode, char value) {
    Instruction inst;
    inst.Value.Char = value;
    inst.OpCode = opCode;
    return inst;
}

Instruction Instructions::makeWithStr(OpCodes opCode, std::string value) {
    Instruction inst;
    inst.StrValue = value;
    inst.OpCode = opCode;
    return inst;
}

Instruction Instructions::makeCall(std::string funcName, std::vector<const Type*> parameters) {
    Instruction inst;
    inst.StrValue = funcName;
    inst.Parameters = parameters;
    inst.OpCode = OpCodes::CALL;
    return inst;
}

Instruction Instructions::makeCallInstance(const StructType* structType, std::string funcName, std::vector<const Type*> parameters) {
    Instruction inst;
    inst.CalledStructType = structType;
    inst.StrValue = funcName;
    inst.Parameters = parameters;
    inst.OpCode = OpCodes::CALL_INSTANCE;
    return inst;
}

 Instruction Instructions::makeNewObject(const StructType* structType, std::vector<const Type*> parameters) {
    Instruction inst;
    inst.CalledStructType = structType;
    inst.StrValue = ".constructor";
    inst.Parameters = parameters;
    inst.OpCode = OpCodes::NEW_OBJECT;
    return inst;
 }