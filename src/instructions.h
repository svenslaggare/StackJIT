#pragma once
#include <string>
#include <vector>

//The OP codes for the instuctios
enum OpCodes {
    NOP,
    PUSH_INT,
    PUSH_FLOAT,
    PUSH_CHAR,
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
    CONVERT_INT_TO_FLOAT,
    CONVERT_FLOAT_TO_INT,
    COMPARE_EQUAL,
    COMPARE_NOT_EQUAL,
    COMPARE_GREATER_THAN,
    COMPARE_GREATER_THAN_OR_EQUAL,
    COMPARE_LESS_THAN,
    COMPARE_LESS_THAN_OR_EQUAL,
    LOAD_LOCAL,
    STORE_LOCAL, 
    CALL,
    CALL_INSTANCE,
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
    GARBAGE_COLLECT,
    NEW_ARRAY,
    LOAD_ELEMENT,
    STORE_ELEMENT,
    LOAD_ARRAY_LENGTH,
    NEW_OBJECT,
    LOAD_FIELD,
    STORE_FIELD,
    LOAD_STRING
};

class Type;
class StructType;

//Represents an instruction
struct Instruction {
    OpCodes opCode;

    float floatValue;
    int intValue;
    char charValue;
    std::string strValue;

    const StructType* calledStructType;
    std::vector<const Type*> parameters;
};

namespace Instructions {
    //Creates a new instruction with the given op code
    Instruction make(OpCodes opCode);

    //Creates a new instruction with an int as value
    Instruction makeWithInt(OpCodes opCode, int value);

    //Creates a new instruction with a float as value
    Instruction makeWithFloat(OpCodes opCode, float value);

    //Creates a new instruction with a char as value
    Instruction makeWithChar(OpCodes opCode, char value);

    //Creates a new instruction with a string as the value
    Instruction makeWithStr(OpCodes opCode, std::string value);

    //Creates a new call instruction
    Instruction makeCall(std::string funcName, std::vector<const Type*> parameters);

    //Creates a new call instance instruction
    Instruction makeCallInstance(const StructType* structType, std::string funcName, std::vector<const Type*> parameters);

    //Creates a new create object instruction
    Instruction makeNewObject(const StructType* structType, std::vector<const Type*> parameters);
}