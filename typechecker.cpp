#include "typechecker.h"

#include <iostream>
#include <vector>

#include "stackjit.h"
#include "codegenerator.h"
#include "program.h"
#include "instructions.h"

Types TypeChecker::popType(std::stack<Types>& stack) {
    auto value = stack.top();
    stack.pop();
    return value;
}

std::string TypeChecker::typeToString(Types type) {
    switch (type) {
        case Types::Int:
            return "Int";
        case Types::ArrayRef:
            return "ArrayRef";
        case Types::Untyped:
            return "Untyped";
    }
}

Types TypeChecker::stringToType(std::string typeStr) {
    if (typeStr == "int" || typeStr == "Int") {
        return Types::Int;
    } else if (typeStr == "arrayref" || typeStr == "ArrayRef") {
        return Types::ArrayRef;
    } else {
        return Types::Untyped;
    }
}

void typeError(int instIndex, std::string errorMessage) {
    throw std::runtime_error(std::to_string(instIndex) + ": " + errorMessage);
}

void assertOperandCount(int index, const std::stack<Types>& stack, int count) {
    if (stack.size() < count) {
        typeError(index, "Expected " + std::to_string(count) + " operand(s) on the stack.");
    }
}

std::string checkType(Types expectedType, Types actualType) {
    if (expectedType == actualType || expectedType == Types::Untyped) {
        return "";
    } else {
        return "Expected type '" + TypeChecker::typeToString(expectedType) + "' but got type '" + TypeChecker::typeToString(actualType) + "'.";
    }
}

struct BranchCheck {
    int Source;
    int Target;
    std::stack<Types> BranchTypes;

    BranchCheck(int source, int target, std::stack<Types> branchTypes)
        : Source(source), Target(target), BranchTypes(branchTypes)
    {

    }
};

void TypeChecker::typeCheckFunction(FunctionCompilationData& function, const VMState& vmState, bool showDebug) {
    std::stack<Types> operandStack;

    auto numInsts = function.Function.Instructions.size();
    auto& func = function.Function;

    std::vector<InstructionTypes> instructionsOperandTypes;
    instructionsOperandTypes.reserve(numInsts);

    std::vector<Types> locals(function.Function.NumLocals);
    std::vector<BranchCheck> branches;

    int index = 0;

    if (showDebug) {
    	std::cout << "----Type checking: " <<  func.Name << "----" << std::endl;
    }

    for (auto inst : func.Instructions) {
    	instructionsOperandTypes.push_back(operandStack);

        switch (inst.OpCode) {
        case OpCodes::PUSH_INT:
            operandStack.push(Types::Int);
            break;
        case OpCodes::ADD:
        case OpCodes::SUB:
        case OpCodes::MUL:
        case OpCodes::DIV:
            {
                assertOperandCount(index, operandStack, 2);
            
                auto op1 = popType(operandStack);
                auto op2 = popType(operandStack);
    
                if (op1 == Types::Int && op2 == Types::Int) {
                    operandStack.push(Types::Int);
                } else {
                    typeError(index, "Expected 2 int operands on the stack.");
                }
            }
            break;
        case OpCodes::LOAD_LOCAL:
            {
                auto localIndex = inst.Value;
                auto localType = locals[localIndex];

                if (localType != Types::Untyped) {
                    operandStack.push(localType);
                } else {
                    typeError(index, "Cannot load untyped local.");
                }
            }
            break;
        case OpCodes::STORE_LOCAL:
            {
                assertOperandCount(index, operandStack, 1);
            
                auto localsIndex = inst.Value;
                auto valueType = popType(operandStack);
                auto localType = locals[localsIndex];
                
                auto error = checkType(localType, valueType);

                if (error == "") {
                    locals[localsIndex] = valueType;
                } else {
                    typeError(index, error);
                }
            }
            break;
        case OpCodes::CALL:
            {
                auto calledFunc = vmState.FunctionTable.at(inst.StrValue);
                int calledFuncNumArgs = calledFunc.Arguments.size();
                assertOperandCount(index, operandStack, calledFuncNumArgs);

                //Check the arguments
                for (int i = calledFuncNumArgs - 1; i >= 0; i--) {
                    auto argType = popType(operandStack);
                    auto error = checkType(calledFunc.Arguments[i], argType);

                    if (error != "") {
                        typeError(index, error);
                    }
                }

                //Return type
                operandStack.push(calledFunc.ReturnType);
            }
            break;
        case OpCodes::LOAD_ARG:
            operandStack.push(func.Arguments[inst.Value]);
            break;
        case OpCodes::BEQ:
        case OpCodes::BNE:
        case OpCodes::BGT:
        case OpCodes::BGE:
        case OpCodes::BLT:
        case OpCodes::BLE:
            {
                assertOperandCount(index, operandStack, 2);
                
                //Check if valid target
                if (!(inst.Value >= 0 && inst.Value < numInsts)) {
                    typeError(index, "Invalid jump target (" + std::to_string(inst.Value) + ").");
                }

                auto op1 = popType(operandStack);
                auto op2 = popType(operandStack);
    
                if (op1 == Types::Int && op2 == Types::Int) {
                    branches.push_back({ index, inst.Value, operandStack });
                } else {
                    typeError(index, "Expected 2 int operands on the stack.");
                }
            }
            break;
        case OpCodes::BR:
            //Check if valid target
            if (!(inst.Value >= 0 && inst.Value < numInsts)) {
                typeError(index, "Invalid jump target (" + std::to_string(inst.Value) + ").");
            }

            branches.push_back({ index, inst.Value, operandStack });
            break;
        case OpCodes::NEW_ARRAY:
            {
                assertOperandCount(index, operandStack, 1);

                auto error = checkType(Types::Int, popType(operandStack));

                if (error != "") {
                    typeError(index, error);
                }

                operandStack.push(Types::ArrayRef);
            }
            break;
        case OpCodes::STORE_ELEMENT:
            {
                assertOperandCount(index, operandStack, 3);

                auto valueType = popType(operandStack);
                auto indexType = popType(operandStack);
                auto arrayRefType = popType(operandStack);

                if (arrayRefType != Types::ArrayRef) {
                    typeError(index, "Expected first operand to be ArrayRef.");
                }

                if (indexType != Types::Int) {
                    typeError(index, "Expected second operand to be Int.");
                }

                if (valueType != Types::Int) {
                    typeError(index, "Expected third operand to be Int.");
                }
            }
            break;
        case OpCodes::LOAD_ELEMENT:
            {
                assertOperandCount(index, operandStack, 2);

                auto indexType = popType(operandStack);
                auto arrayRefType = popType(operandStack);

                if (arrayRefType != Types::ArrayRef) {
                    typeError(index, "Expected first operand to be ArrayRef.");
                }

                if (indexType != Types::Int) {
                    typeError(index, "Expected second operand to be Int.");
                }

                operandStack.push(Types::Int);
            }
            break;
        default:
            break;
        }

        index++;
    }

    //Check that the branches are valid
    for (auto branch : branches) {
        auto postSourceTypes = branch.BranchTypes;
        auto preTargetTypes = instructionsOperandTypes[branch.Target];

        if (postSourceTypes.size() == preTargetTypes.size()) {
            for (int i = 0; i < postSourceTypes.size(); i++) {
                auto postType = popType(postSourceTypes);
                auto preType = popType(preTargetTypes);
                auto error = checkType(postType, preType);

                if (error != "") {
                    typeError(index, error);
                }
            }
        } else {
            typeError(branch.Source, "Expected the number of types before and after branch to be the same.");
        }
    }

    if (showDebug) {
	    for (int i = 0; i < numInsts; i++) {
	        auto types = instructionsOperandTypes[i];

	        std::cout << i << ": ";

	        while (!types.empty()) {
	            std::cout << typeToString(types.top()) << " ";
	            types.pop();
	        }

	        std::cout << std::endl;
	    }
    }

    if (operandStack.size() == 1) {
        auto returnType = operandStack.top();

        if (returnType != func.ReturnType) {
            throw std::runtime_error("Expected '" + TypeChecker::typeToString(func.ReturnType) + "' as return type.");
        }
    } else {
        throw std::runtime_error("Expected 1 operand on the stack but got " + std::to_string(operandStack.size()) + " when returning.");
    }

    if (showDebug) {
    	std::cout << "----End type checking----" << std::endl;
    }

    //Save the operand types
    function.InstructionOperandTypes = instructionsOperandTypes;
}