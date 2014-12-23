#include "typechecker.h"

#include <iostream>
#include <vector>

#include "vmstate.h"
#include "codegenerator.h"
#include "program.h"
#include "function.h"
#include "instructions.h"
#include "type.h"
#include "structmetadata.h"

const Type* TypeChecker::popType(InstructionTypes& stack) {
    auto value = stack.top();
    stack.pop();
    return value;
}

std::string TypeChecker::typeToString(const Type* type) {
    if (type == nullptr) {
        return "Untyped";
    }

    return type->name();
}

void typeError(int instIndex, std::string errorMessage) {
    throw std::runtime_error(std::to_string(instIndex) + ": " + errorMessage);
}

void assertOperandCount(int index, const InstructionTypes& stack, int count) {
    if (stack.size() < count) {
        typeError(index, "Expected " + std::to_string(count) + " operand(s) on the stack.");
    }
}

std::string checkType(const Type* expectedType, const Type* actualType) {
    if (expectedType == nullptr || *expectedType == *actualType || actualType->name() == "Ref.Null") {
        return "";
    } else {
        return "Expected type '" + TypeChecker::typeToString(expectedType) + "' but got type '" + TypeChecker::typeToString(actualType) + "'.";
    }
}

std::deque<const Type*> asVector(InstructionTypes types) {
    std::deque<const Type*> typesList;

    while (!types.empty()) {
        typesList.push_back(types.top());
        types.pop();
    }

    return typesList;
}

struct BranchCheck {
    const int source;
    const int target;
    const InstructionTypes branchTypes;

    BranchCheck(int source, int target, InstructionTypes branchTypes)
        : source(source), target(target), branchTypes(branchTypes) {

    }
};

void TypeChecker::typeCheckFunction(FunctionCompilationData& funcData, VMState& vmState, bool showDebug) {
    InstructionTypes operandStack;

    auto& func = funcData.function;
    const auto numInsts = func.instructions.size();

    std::vector<InstructionTypes> instructionsOperandTypes;
    instructionsOperandTypes.reserve(numInsts);

    std::vector<InstructionTypes> postInstructionsOperandTypes;
    postInstructionsOperandTypes.reserve(numInsts);

    //Set the local type if set
    std::vector<const Type*> locals(func.numLocals());

    for (int i = 0; i < locals.size(); i++) {
        auto localType = func.getLocal(i);

        if (localType != nullptr) {
            locals[i] = localType;
        }
    }

    std::vector<BranchCheck> branches;

    const auto intType = vmState.findType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer));
    const auto boolType = vmState.findType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Bool));
    const auto voidType = vmState.findType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Void));
    const auto nullType = vmState.findType("Ref.Null");

    int index = 1;

    if (showDebug) {
    	std::cout << "----Type checking: " <<  func.name() << "----" << std::endl;
    }

    //Check the function definition
    if (func.returnType() == nullptr) {
        throw std::runtime_error("The function cannot return type 'Untyped'.");
    }

    int i = 0;
    for (auto arg : func.arguments()) {
        if (arg == nullptr || TypeSystem::isPrimitiveType(arg, PrimitiveTypes::Void)) {
            throw std::runtime_error("The argument: " + std::to_string(i) + " in function '" + func.name() + "' cannot be of type '" + typeToString(arg) + "'.");
        }

        i++;
    }

    for (auto inst : func.instructions) {
    	instructionsOperandTypes.push_back(operandStack);

        switch (inst.OpCode) {
        case OpCodes::NOP:
            break;
        case OpCodes::PUSH_INT:
            operandStack.push(intType);
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
                    operandStack.push(intType);
                } else {
                    typeError(index, "Expected 2 operands of type Int on the stack.");
                }
            }
            break;
        case OpCodes::PUSH_TRUE:
        case OpCodes::PUSH_FALSE:
            {
                operandStack.push(boolType);
            }
            break;
        case OpCodes::AND:
        case OpCodes::OR:
            {
                assertOperandCount(index, operandStack, 2);
            
                auto op1 = popType(operandStack);
                auto op2 = popType(operandStack);
    
                if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Bool) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
                    operandStack.push(boolType);
                } else {
                    typeError(index, "Expected 2 operands of type Bool on the stack.");
                }
            }
            break;
        case OpCodes::COMPARE_EQUAL:
        case OpCodes::COMPARE_NOT_EQUAL:
        case OpCodes::COMPARE_GREATER_THAN:
        case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
        case OpCodes::COMPARE_LESS_THAN:
        case OpCodes::COMPARE_LESS_THAN_OR_EQUAL:
            {
                assertOperandCount(index, operandStack, 2);
            
                auto op1 = popType(operandStack);
                auto op2 = popType(operandStack);
    
                if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
                    operandStack.push(boolType);
                } else {
                    typeError(index, "Expected 2 operands of type Int on the stack.");
                }
            }
            break;
        case OpCodes::NOT:
            {
                assertOperandCount(index, operandStack, 1);
            
                auto op = popType(operandStack);
    
                if (TypeSystem::isPrimitiveType(op, PrimitiveTypes::Bool)) {
                    operandStack.push(boolType);
                } else {
                    typeError(index, "Expected 1 operand of type Bool on the stack.");
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
                    if (locals[localsIndex] == nullptr) {
                        locals[localsIndex] = valueType;
                        func.setLocal(localsIndex, valueType);
                    }
                } else {
                    typeError(index, error);
                }
            }
            break;
        case OpCodes::CALL:
            {
                auto calledFunc = vmState.functionTable.at(inst.StrValue);
                int calledFuncNumArgs = calledFunc.arguments().size();
                assertOperandCount(index, operandStack, calledFuncNumArgs);

                //Check the arguments
                for (int i = calledFuncNumArgs - 1; i >= 0; i--) {
                    auto argType = popType(operandStack);
                    auto error = checkType(calledFunc.arguments()[i], argType);

                    if (error != "") {
                        typeError(index, error);
                    }
                }

                //Return type
                if (!TypeSystem::isPrimitiveType(calledFunc.returnType(), PrimitiveTypes::Void)) {
                    operandStack.push(calledFunc.returnType());
                }
            }
            break;
        case OpCodes::RET:
            {
                int returnCount = 1;

                if (TypeSystem::isPrimitiveType(func.returnType(), PrimitiveTypes::Void)) {
                    returnCount = 0;
                }

                if (operandStack.size() == returnCount) {
                    if (returnCount > 0) {
                        auto returnType = popType(operandStack);

                        if (*returnType != *func.returnType()) {
                            throw std::runtime_error("Expected '" + TypeChecker::typeToString(func.returnType()) + "' as return type.");
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
            operandStack.push(func.arguments()[inst.Value]);
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
    
                if (*op1 == *intType) {               
                    if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
                        branches.push_back({ index, inst.Value, operandStack });
                    } else {
                        typeError(index, "Expected 2 operands of type Int on the stack.");
                    }
                } else if (*op1 == *boolType) {
                    if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
                        branches.push_back({ index, inst.Value, operandStack });
                    } else {
                        typeError(index, "Expected 2 operands of type Int on the stack.");
                    }
                } else {
                    typeError(index, "Expected 2 operands of type Int or Bool on the stack.");  
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
        case OpCodes::PUSH_NULL:
            {
                operandStack.push(nullType);
            }
            break;
        case OpCodes::NEW_ARRAY:
            {
                assertOperandCount(index, operandStack, 1);

                auto error = checkType(intType, popType(operandStack));

                if (error != "") {
                    typeError(index, error);
                }

                auto elemType = vmState.findType(inst.StrValue);

                if (elemType == nullptr) {
                    typeError(index, "'" + inst.StrValue + "' is not a valid type.");
                }

                if (*elemType == *voidType) {
                    typeError(index, "Arrays of Voids are not allowed");
                }

                operandStack.push(vmState.findType("Ref.Array[" + inst.StrValue + "]"));
            }
            break;
        case OpCodes::STORE_ELEMENT:
            {
                assertOperandCount(index, operandStack, 3);

                auto valueType = popType(operandStack);
                auto indexType = popType(operandStack);
                auto arrayRefType = popType(operandStack);

                bool isNull = arrayRefType == nullType;

                if (!TypeSystem::isArray(arrayRefType) && !isNull) {
                    typeError(index, "Expected first operand to be of type ArrayRef.");
                }

                if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
                    typeError(index, "Expected second operand to be of type Int.");
                }

                auto elemType = vmState.findType(inst.StrValue);

                if (!isNull) {
                    auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();

                    auto error = checkType(arrayElemType, elemType);

                    if (error != "") {
                        typeError(index, error);
                    }
                }

                if (elemType == nullptr) {
                    typeError(index, "There exists no type '" + inst.StrValue + "'.");
                }
 
                if (*valueType != *elemType) {
                    typeError(index, "Expected third operand to be of type " + elemType->name() + ".");
                }
            }
            break;
        case OpCodes::LOAD_ELEMENT:
            {
                assertOperandCount(index, operandStack, 2);

                auto indexType = popType(operandStack);
                auto arrayRefType = popType(operandStack);

                bool isNull = arrayRefType == nullType;

                if (!TypeSystem::isArray(arrayRefType) && !isNull) {
                    typeError(index, "Expected first operand to be of type ArrayRef.");
                }

                if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
                    typeError(index, "Expected second operand to be of type Int.");
                }

                auto elemType = vmState.findType(inst.StrValue);

                if (!isNull) {
                    auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();

                    auto error = checkType(arrayElemType, elemType);

                    if (error != "") {
                        typeError(index, error);
                    }
                }

                if (elemType == nullptr) {
                    typeError(index, "There exists no type '" + inst.StrValue + "'.");
                }

                operandStack.push(elemType);
            }
            break;
        case OpCodes::LOAD_ARRAY_LENGTH:
            {
                assertOperandCount(index, operandStack, 1);
                auto arrayRefType = popType(operandStack);

                if (!TypeSystem::isArray(arrayRefType) && arrayRefType != nullType) {
                    typeError(index, "Expected operand to be of type ArrayRef.");
                }

                operandStack.push(intType);
            }
            break;
        case OpCodes::NEW_OBJECT:
            {
                auto structType = vmState.findType(inst.StrValue);

                if (!TypeSystem::isReferenceType(structType)) {
                    typeError(index, "'" + structType->name() + "' is not a struct type.");
                }

                std::string structName = dynamic_cast<const StructType*>(structType)->structName();

                if (vmState.getStructMetadata(structName) == nullptr) {
                    typeError(index, "'" + structName + "' is not a defined struct.");
                }

                operandStack.push(structType);
            }
            break;
        case OpCodes::LOAD_FIELD:
            {
                assertOperandCount(index, operandStack, 1);

                auto structRefType = popType(operandStack);
                bool isNull = structRefType == nullType;

                if (!TypeSystem::isStruct(structRefType) && !isNull) {
                    typeError(index, "Expected first operand to be of type StructRef.");
                }

                std::pair<std::string, std::string> structAndField;

                if (TypeSystem::getStructAndField(inst.StrValue, structAndField)) {
                    auto structName = structAndField.first;
                    auto fieldName = structAndField.second;

                    auto structMetadata = vmState.getStructMetadata(structName);

                    if (structMetadata == nullptr) {
                        typeError(index, "'" + structName + "' is not a struct type.");
                    }

                    auto structType = vmState.findType("Ref.Struct." + structName);

                    if (!isNull) {
                        auto error = checkType(structType, structRefType);

                        if (error != "") {
                            typeError(index, error);
                        }
                    }

                    auto fieldType = structMetadata->getField(fieldName);

                    if (fieldType == nullptr) {
                        typeError(index, "There exists no '" + fieldName + "' field in the '" + structName + "' struct.");
                    }

                    operandStack.push(fieldType);
                } else {
                    typeError(index, "Invalid field reference.");
                }
            }
            break;
        case OpCodes::STORE_FIELD:
             {
                assertOperandCount(index, operandStack, 2);

                auto valueType = popType(operandStack);
                auto structRefType = popType(operandStack);
                bool isNull = structRefType == nullType;

                if (!TypeSystem::isStruct(structRefType) && !isNull) {
                    typeError(index, "Expected first operand to be of type StructRef.");
                }

                std::pair<std::string, std::string> structAndField;

                if (TypeSystem::getStructAndField(inst.StrValue, structAndField)) {
                    auto structName = structAndField.first;
                    auto fieldName = structAndField.second;

                    auto structMetadata = vmState.getStructMetadata(structName);

                    if (structMetadata == nullptr) {
                        typeError(index, "'" + structName + "' is not a struct type.");
                    }

                    auto fieldType = structMetadata->getField(fieldName);

                    if (fieldType == nullptr) {
                        typeError(index, "There exists no '" + fieldName + "' field in the '" + structName + "' struct.");
                    }

                    auto structType = vmState.findType("Ref.Struct." + structName);

                    if (!isNull) {
                        auto error = checkType(structType, structRefType);

                        if (error != "") {
                            typeError(index, error);
                        }
                    }

                    if (*valueType != *fieldType) {
                        typeError(index, "Expected second operand to be " + fieldType->name() + ".");
                    }
                } else {
                    typeError(index, "Invalid field reference.");
                }
            }
            break;
        }

        if (index == numInsts) {
            if (inst.OpCode != OpCodes::RET) {
                typeError(index, "Functions must end with a 'RET' instruction.");
            }
        }

        postInstructionsOperandTypes.push_back(operandStack);
        index++;
    }

    //Check that the branches are valid
    for (auto branch : branches) {
        auto postSourceTypes = branch.branchTypes;
        auto preTargetTypes = instructionsOperandTypes[branch.target];

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
            typeError(branch.source, "Expected the number of types before and after branch to be the same.");
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

    for (int i = 0; i < func.numLocals(); i++) {
        if (func.getLocal(i) == nullptr) {
            typeError(1, "Local " + std::to_string(i) + " is not typed.");
        }
    }

    //Save the operand types
    for (auto instTypes : instructionsOperandTypes) {
        funcData.instructionOperandTypes.push_back(asVector(instTypes));

        if (instTypes.size() > funcData.operandStackSize) {
            funcData.operandStackSize = instTypes.size();
        }
    }

    for (auto instTypes : postInstructionsOperandTypes) {
        funcData.postInstructionOperandTypes.push_back(asVector(instTypes));
    }
}