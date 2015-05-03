#pragma once
#include <string>
#include <vector>
#include <deque>

//The list of op codes
enum class OpCodes : unsigned char {
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
class Instruction {
private:
    const OpCodes mOpCode;
    bool mHasEliminatedNullCheck = false;
    std::deque<const Type*> mOperandTypes;
public:
    //Primitive values
    float floatValue;
    int intValue;
    char charValue;
    std::string strValue;

    //Used by call instructions
    std::vector<const Type*> parameters;

    //Used by the objects instruction
    const StructType* calledStructType;

    //Creates a new instruction
    Instruction();
    Instruction(OpCodes opCode);

    //Returns the OP code
    OpCodes opCode() const;

    //Indicates if the null check has been eliminated
    bool hasEliminatedNullCheck() const;

    //Eliminates the null check
    void eliminateNullCheck();

    //Returns the operand types
    const std::deque<const Type*>& operandTypes() const;

    //Sets the operand types
    void setOperandTypes(std::deque<const Type*> operandTypes);
};