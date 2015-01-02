#pragma once
#include <string>

//The OP codes for the instuctios
enum OpCodes {
    NOP,
    PUSH_INT,
    PUSH_FLOAT,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    PUSH_TRUE,
    PUSH_FALSE,
    AND,
    OR,
    NOT,
    COMPARE_EQUAL,
    COMPARE_NOT_EQUAL,
    COMPARE_GREATER_THAN,
    COMPARE_GREATER_THAN_OR_EQUAL,
    COMPARE_LESS_THAN,
    COMPARE_LESS_THAN_OR_EQUAL,
    LOAD_LOCAL,
    STORE_LOCAL, 
    CALL,
    RET,
    LOAD_ARG,
    BRANCH,
    BRANCH_EQUAL,
    BRANCH_NOT_EQUAL,
    BRANCH_GREATER_THAN,
    BRANCH_GREATER_THAN_OR_EQUAL,
    BRANCH_LESS_THAN,
    BRANCH_LESS_THAN_OR_EQUAL,
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

    union {
        float Float;
        int Int;
    } Value;

    std::string StrValue;
};

namespace Instructions {
    //Creates a new instruction with the given op code
    Instruction make(OpCodes opCode);

    //Creates a new instruction with an int as value
    Instruction makeWithInt(OpCodes opCode, int value);

    //Creates a new instruction with a float as value
    Instruction makeWithFloat(OpCodes opCode, float value);

    //Creates a new instruction with a string as the value
    Instruction makeWithStr(OpCodes opCode, std::string value);

    //Creates a new call instruction
    Instruction makeCall(std::string funcName);
}