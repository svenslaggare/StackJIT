#pragma once
#include <string>

//The OP codes for the instuctios
enum OpCodes {
    PUSH_INT,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD_LOCAL,
    STORE_LOCAL, 
    CALL,
    LOAD_ARG,
    BR,
    BEQ,
    BNE,
    BGT,
    BGE,
    BLT,
    BLE,
    NEW_ARRAY,
    LOAD_ELEMENT,
    STORE_ELEMENT,
    LOAD_ARRAY_LENGTH
};

//Represents an instruction
struct Instruction {
    OpCodes OpCode;
    int Value;
    std::string StrValue;
};

//Creates a new instruction with the given op code
Instruction makeInstruction(OpCodes opCode);

//Creates a new push int instruction
Instruction makePushInt(int value);

//Creates a new load local instruction
Instruction makeLoadLocal(int local);

//Creates a new store local instruction
Instruction makeStoreLocal(int local);

//Creates a new call instruction
Instruction makeCall(std::string funcName);

//Creates a new load argument instruction
Instruction makeLoadArg(int argNum);

//Creates a new branch instruction
Instruction makeBr(int target);

//Creates a new instruction with an int as value
Instruction makeInstWithInt(OpCodes opCode, int value);