#include "instructions.h"

Instruction Instructions::make(OpCodes opCode) {
    Instruction inst;
    inst.opCode = opCode;
    return inst;
}

Instruction Instructions::makeWithInt(OpCodes opCode, int value) {
    Instruction inst;
    inst.intValue = value;
    inst.opCode = opCode;
    return inst;
}

Instruction Instructions::makeWithFloat(OpCodes opCode, float value) {
    Instruction inst;
    inst.floatValue = value;
    inst.opCode = opCode;
    return inst;
}

Instruction Instructions::makeWithChar(OpCodes opCode, char value) {
    Instruction inst;
    inst.charValue = value;
    inst.opCode = opCode;
    return inst;
}

Instruction Instructions::makeWithStr(OpCodes opCode, std::string value) {
    Instruction inst;
    inst.strValue = value;
    inst.opCode = opCode;
    return inst;
}

Instruction Instructions::makeCall(std::string funcName, std::vector<const Type*> parameters) {
    Instruction inst;
    inst.strValue = funcName;
    inst.parameters = parameters;
    inst.opCode = OpCodes::CALL;
    return inst;
}

Instruction Instructions::makeCallInstance(const StructType* structType, std::string funcName, std::vector<const Type*> parameters) {
    Instruction inst;
    inst.calledStructType = structType;
    inst.strValue = funcName;
    inst.parameters = parameters;
    inst.opCode = OpCodes::CALL_INSTANCE;
    return inst;
}

 Instruction Instructions::makeNewObject(const StructType* structType, std::vector<const Type*> parameters) {
    Instruction inst;
    inst.calledStructType = structType;
    inst.strValue = ".constructor";
    inst.parameters = parameters;
    inst.opCode = OpCodes::NEW_OBJECT;
    return inst;
 }