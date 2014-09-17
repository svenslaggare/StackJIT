#include "typechecker.h"

#include <iostream>
#include <vector>

#include "stackjit.h"
#include "codegenerator.h"
#include "program.h"
#include "instructions.h"
#include "type.h"

Type* TypeChecker::popType(std::stack<Type*>& stack) {
    auto value = stack.top();
    stack.pop();
    return value;
}

std::string TypeChecker::typeToString(Type* type) {
    if (type == nullptr) {
        return "Untyped";
    }

    return type->name();
}

void typeError(int instIndex, std::string errorMessage) {
    throw std::runtime_error(std::to_string(instIndex) + ": " + errorMessage);
}

void assertOperandCount(int index, const std::stack<Type*>& stack, int count) {
    if (stack.size() < count) {
        typeError(index, "Expected " + std::to_string(count) + " operand(s) on the stack.");
    }
}

std::string checkType(Type* expectedType, Type* actualType) {
    if (expectedType == nullptr || *expectedType == *actualType) {
        return "";
    } else {
        return "Expected type '" + TypeChecker::typeToString(expectedType) + "' but got type '" + TypeChecker::typeToString(actualType) + "'.";
    }
}

struct BranchCheck {
    int Source;
    int Target;
    std::stack<Type*> BranchTypes;

    BranchCheck(int source, int target, std::stack<Type*> branchTypes)
        : Source(source), Target(target), BranchTypes(branchTypes)
    {

    }
};

void TypeChecker::typeCheckFunction(FunctionCompilationData& function, VMState& vmState, bool showDebug) {
    std::stack<Type*> operandStack;

    auto numInsts = function.Function.Instructions.size();
    auto& func = function.Function;

    std::vector<InstructionTypes> instructionsOperandTypes;
    instructionsOperandTypes.reserve(numInsts);

    std::vector<Type*> locals(function.Function.NumLocals);
    std::vector<BranchCheck> branches;

    int index = 1;

    if (showDebug) {
    	std::cout << "----Type checking: " <<  func.Name << "----" << std::endl;
    }

    //Check the function definition
    if (func.ReturnType == nullptr) {
        throw std::runtime_error("The function cannot return type 'Untyped'.");
    }

    int i = 0;
    for (auto arg : func.Arguments) {
        if (arg == nullptr || TypeSystem::isPrimitiveType(arg, PrimitiveTypes::Void)) {
            throw std::runtime_error("The argument: " + std::to_string(i) + " in function '" + func.Name + "' cannot be of type '" + typeToString(arg) + "'.");
        }

        i++;
    }

    for (auto inst : func.Instructions) {
    	instructionsOperandTypes.push_back(operandStack);

        switch (inst.OpCode) {
        case OpCodes::PUSH_INT:
            operandStack.push(vmState.getType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer)));
            break;
        case OpCodes::POP:
            assertOperandCount(index, operandStack, 1);
            popType(operandStack);
            break;
        case OpCodes::ADD:
        case OpCodes::SUB:
        case OpCodes::MUL:
        case OpCodes::DIV:
            {
                assertOperandCount(index, operandStack, 2);
            
                auto op1 = popType(operandStack);
                auto op2 = popType(operandStack);
    
                if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
                    operandStack.push(vmState.getType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer)));
                } else {
                    typeError(index, "Expected 2 int operands on the stack.");
                }
            }
            break;
        case OpCodes::LOAD_LOCAL:
            {
                auto localIndex = inst.Value;
                auto localType = locals[localIndex];

                if (localType != nullptr) {
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
                if (!TypeSystem::isPrimitiveType(calledFunc.ReturnType, PrimitiveTypes::Void)) {
                    operandStack.push(calledFunc.ReturnType);
                }
            }
            break;
        case OpCodes::RET:
            {
                int returnCount = 1;

                if (TypeSystem::isPrimitiveType(func.ReturnType, PrimitiveTypes::Void)) {
                    returnCount = 0;
                }

                if (operandStack.size() == returnCount) {
                    if (returnCount > 0) {
                        auto returnType = popType(operandStack);

                        if (*returnType != *func.ReturnType) {
                            throw std::runtime_error("Expected '" + TypeChecker::typeToString(func.ReturnType) + "' as return type.");
                        }
                    }
                } else {
                    typeError(
                        index,
                        "Expected " + std::to_string(returnCount) + " operand on the stack but got " + std::to_string(operandStack.size()) + " when returning.");
                }
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
    
                if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
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

                auto error = checkType(vmState.getType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer)), popType(operandStack));

                if (error != "") {
                    typeError(index, error);
                }

                operandStack.push(vmState.getType("Ref.Array[" + inst.StrValue + "]"));
            }
            break;
        case OpCodes::STORE_ELEMENT:
            {
                assertOperandCount(index, operandStack, 3);

                auto valueType = popType(operandStack);
                auto indexType = popType(operandStack);
                auto arrayRefType = popType(operandStack);

                if (!TypeSystem::isArray(arrayRefType)) {
                    typeError(index, "Expected first operand to be ArrayRef.");
                }

                if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
                    typeError(index, "Expected second operand to be Int.");
                }

                auto elemType = vmState.getType(inst.StrValue);

                if (*valueType != *elemType) {
                    typeError(index, "Expected third operand to be " + elemType->name() + ".");
                }
            }
            break;
        case OpCodes::LOAD_ELEMENT:
            {
                assertOperandCount(index, operandStack, 2);

                auto indexType = popType(operandStack);
                auto arrayRefType = popType(operandStack);

                if (!TypeSystem::isArray(arrayRefType)) {
                    typeError(index, "Expected first operand to be ArrayRef.");
                }

                if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
                    typeError(index, "Expected second operand to be Int.");
                }

                operandStack.push(vmState.getType(inst.StrValue));
            }
            break;
        case OpCodes::LOAD_ARRAY_LENGTH:
            {
                assertOperandCount(index, operandStack, 1);
                auto arrayRefType = popType(operandStack);

                if (!TypeSystem::isArray(arrayRefType)) {
                    typeError(index, "Expected operand to be ArrayRef.");
                }

                operandStack.push(vmState.getType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer)));
            }
            break;
        }

        if (index == numInsts) {
            if (inst.OpCode != OpCodes::RET) {
                typeError(index, "Function must end with 'RET' instruction.");
            }
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

    if (showDebug) {
    	std::cout << "----End type checking----" << std::endl;
    }

    //Save the operand types
    function.InstructionOperandTypes = instructionsOperandTypes;
}