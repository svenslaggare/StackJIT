#pragma once
#include <string>
#include <vector>
#include <deque>
#include "instructionset.h"

class Type;
class ClassType;

//Represents an instruction
class Instruction {
private:
    const OpCodes mOpCode;
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
    const ClassType* classType;

    //Creates a new instruction
    Instruction();
    Instruction(OpCodes opCode);

    //Returns the OP code
    OpCodes opCode() const;

    //Returns the operand types
    const std::deque<const Type*>& operandTypes() const;

    //Sets the operand types
    void setOperandTypes(std::deque<const Type*> operandTypes);
};