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
    const ClassType* classClassType;

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