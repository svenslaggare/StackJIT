#pragma once
#include <string>

//The OP codes for the instuctios
enum OpCodes {
    NOP,
    PUSH_INT,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD_LOCAL,
    STORE_LOCAL, 
    CALL,
    RET,
    LOAD_ARG,
    BR,
    BEQ,
    BNE,
    BGT,
    BGE,
    BLT,
    BLE,
    PUSH_NULL,
    NEW_ARRAY,
    LOAD_ELEMENT,
    STORE_ELEMENT,
    LOAD_ARRAY_LENGTH,
    NEW_OBJECT,
    LOAD_FIELD,
    STORE_FIELD
};

//Represents an instruction
struct Instruction {
    OpCodes OpCode;
    int Value;
    std::string StrValue;
};

//Creates a new instruction with the given op code
Instruction makeInstruction(OpCodes opCode);

//Creates a new instruction with an int as value
Instruction makeInstWithInt(OpCodes opCode, int value);

//Creates a new instruction with a string as the value
Instruction makeInstWithStr(OpCodes opCode, std::string value);

//Creates a new call instruction
Instruction makeCall(std::string funcName);
