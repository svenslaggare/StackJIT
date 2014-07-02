#pragma once
#include <string>

enum OpCodes
{
    PUSH_INT,
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD_LOCAL,
    STORE_LOCAL, 
    CALL
};

struct Instruction {
    OpCodes OpCode;
    int Value;
    std::string StrValue;
};

Instruction makeInstruction(OpCodes opCode);
Instruction makePushInt(int value);
Instruction makeLoadLocal(int local);
Instruction makeStoreLocal(int local);
Instruction makeCall(std::string funcName, int numArgs);