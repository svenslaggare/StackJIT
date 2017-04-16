#pragma once
#include <string>
#include <vector>
#include "instructionset.h"

namespace stackjit {
	class Type;
	class ClassType;

	//Represents an instruction
	class Instruction {
	private:
	    const OpCodes mOpCode;
	    std::vector<const Type*> mOperandTypes;
	public:
	    //Primitive values
	    float floatValue;
	    int intValue;
	    char charValue;
	    std::string stringValue;

	    //Used by call instructions
	    std::vector<const Type*> parameters;

	    //Used by object instructions
	    const ClassType* classType;

	    //Creates a new instruction
	    Instruction();
	    Instruction(OpCodes opCode);

	    //Returns the OP code
	    OpCodes opCode() const;

		//Indicates if the instruction calls a member function (virtual & non-virtual)
	    bool isCallInstance() const;

	    //Returns the operand types
	    const std::vector<const Type*>& operandTypes() const;

	    //Sets the operand types
	    void setOperandTypes(const std::vector<const Type*>& operandTypes);
	};
}
