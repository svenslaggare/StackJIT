#include "typechecker.h"
#include "vmstate.h"
#include "function.h"
#include "instructions.h"
#include "type.h"
#include "structmetadata.h"

#include <iostream>
#include <vector>

std::string TypeChecker::typeToString(const Type* type) {
    if (type == nullptr) {
        return "Untyped";
    }

    return type->name();
}

namespace {
    const Type* popType(InstructionTypes& stack) {
        auto value = stack.top();
        stack.pop();
        return value;
    }

    const Type* popType(std::deque<const Type*>& list) {
        auto value = list.front();
        list.pop_front();
        return value;
    }

    void typeError(int instIndex, std::string errorMessage) {
        throw std::runtime_error(std::to_string(instIndex) + ": " + errorMessage);
    }

    void assertOperandCount(int index, const InstructionTypes& stack, std::size_t count) {
        if (stack.size() < count) {
            typeError(index, "Expected " + std::to_string(count) + " operand(s) on the stack.");
        }
    }

    std::string checkType(const Type* expectedType, const Type* actualType) {
        if (expectedType == nullptr || *expectedType == *actualType || actualType->name() == "Ref.Null") {
            return "";
        } else {
            return
				"Expected type '" + TypeChecker::typeToString(expectedType)
				+ "' but got type '"
				+ TypeChecker::typeToString(actualType) + "'.";
        }
    }

    void assertNotVoidType(int index, const Type* type) {
        if (type != nullptr && type->name() == "Void") {
            typeError(index, "Void type not allowed.");
        }
    }

    std::deque<const Type*> asList(InstructionTypes types) {
        std::deque<const Type*> typesList;

        while (!types.empty()) {
            typesList.push_back(types.top());
            types.pop();
        }

        return typesList;
    }

    struct BranchCheck {
        const std::size_t source;
        const std::size_t target;
        const InstructionTypes branchTypes;

        BranchCheck(std::size_t source, std::size_t target, InstructionTypes branchTypes)
            : source(source), target(target), branchTypes(branchTypes) {

        }
    };
}

void TypeChecker::typeCheckFunction(Function& function, VMState& vmState, bool showDebug) {
    InstructionTypes operandStack;

    const auto numInsts = function.instructions.size();

    if (numInsts == 0) {
        typeError(1, "Empty functions are not allowed.");
    }

    //Get common types
    const auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));
    const auto floatType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Float));
    const auto boolType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Bool));
    const auto charType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
    const auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));
    const auto nullType = vmState.typeProvider().makeType("Ref.Null");
    const auto stringType = vmState.typeProvider().makeType("Ref.Array[Char]");
    
    //Set the type of the locals
    std::vector<const Type*> locals(function.numLocals());

    for (std::size_t i = 0; i < locals.size(); i++) {
        auto localType = function.getLocal(i);

        if (localType != nullptr) {
            if (localType == voidType) {
                typeError(1, "Locals of 'Void' type are not allowed.");
            }

            locals[i] = localType;
        }
    }

    if (showDebug) {
        std::cout << "----Type checking: " <<  function.name() << "----" << std::endl;
    }

    //Check the function definition
    if (function.returnType() == nullptr) {
        throw std::runtime_error("A function cannot have return type 'Untyped'.");
    }

    if (function.isConstructor() && function.returnType() != voidType) {
        throw std::runtime_error("Constructors must have return type 'Void'.");
    }

    int i = 0;
    for (auto arg : function.parameters()) {
        if (arg == nullptr || TypeSystem::isPrimitiveType(arg, PrimitiveTypes::Void)) {
            throw std::runtime_error(
                "Parameter: " + std::to_string(i) + " in function '" + function.name()
				+ "' cannot be of type '" + typeToString(arg) + "'.");
        }

        i++;
    }

    std::size_t index = 1;
    std::vector<BranchCheck> branches;

    for (auto& inst : function.instructions) {
        inst.setOperandTypes(asList(operandStack));

        //Calculate the maximum size of the stack
        auto stackSize = inst.operandTypes().size();
        if (stackSize > function.operandStackSize()) {
            function.setOperandStackSize(stackSize);
        }

        switch (inst.opCode()) {
        case OpCodes::NOP:
            break;
        case OpCodes::LOAD_INT:
            operandStack.push(intType);
            break;
        case OpCodes::LOAD_FLOAT:
            operandStack.push(floatType);
            break;
        case OpCodes::LOAD_CHAR:
            operandStack.push(charType);
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
    
                if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer)) {
                    if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
                        operandStack.push(intType);
                    } else {
                        typeError(index, "Expected 2 operands of type Int on the stack.");
                    }
                } else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Float)) {
                    if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
                        operandStack.push(floatType);
                    } else {
                        typeError(index, "Expected 2 operands of type Float on the stack.");
                    }
                } else {
                    typeError(index, "Expected 2 operands of type Int or Float on the stack.");
                }
            }
            break;
        case OpCodes::LOAD_TRUE:
        case OpCodes::LOAD_FALSE:
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
        case OpCodes::CONVERT_INT_TO_FLOAT:
            {
                assertOperandCount(index, operandStack, 1);
            
                auto op = popType(operandStack);

                if (TypeSystem::isPrimitiveType(op, PrimitiveTypes::Integer)) {
                    operandStack.push(floatType);
                } else {
                    typeError(index, "Expected 1 operand of type Int on the stack.");
                }
            }
            break;
        case OpCodes::CONVERT_FLOAT_TO_INT:
            {
                assertOperandCount(index, operandStack, 1);
            
                auto op = popType(operandStack);

                if (TypeSystem::isPrimitiveType(op, PrimitiveTypes::Float)) {
                    operandStack.push(intType);
                } else {
                    typeError(index, "Expected 1 operand of type Float on the stack.");
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
    
                if (inst.opCode() == OpCodes::COMPARE_EQUAL || inst.opCode() == OpCodes::COMPARE_NOT_EQUAL) {
                    if (*op1 == *intType) {               
                        if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
                            operandStack.push(boolType);
                        } else {
                            typeError(index, "Expected 2 operands of type Int on the stack.");
                        }
                    } else if (*op1 == *boolType) {
                        if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
                            operandStack.push(boolType);
                        } else {
                            typeError(index, "Expected 2 operands of type Bool on the stack.");
                        }
                    } else if (*op1 == *floatType) {
                        if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
                            operandStack.push(boolType);
                        } else {
                            typeError(index, "Expected 2 operands of type Float on the stack.");
                        }
                    } else {
                        typeError(index, "Expected 2 operands of comparable type on the stack.");  
                    }
                } else {
                    if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
                        operandStack.push(boolType);
                    } else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Float) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
                        operandStack.push(boolType);
                    } else {
                        typeError(index, "Expected 2 operands of type Int or Float on the stack.");
                    }
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
                auto localIndex = inst.intValue;
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
            
                auto localsIndex = inst.intValue;
                auto valueType = popType(operandStack);
                auto localType = locals[localsIndex];
                
                auto error = checkType(localType, valueType);

                if (error == "") {
                    if (locals[localsIndex] == nullptr) {
                        locals[localsIndex] = valueType;
                        function.setLocal(localsIndex, valueType);
                    }
                } else {
                    typeError(index, error);
                }
            }
            break;
        case OpCodes::CALL:
        case OpCodes::CALL_INSTANCE:
            {
                bool isInstance = inst.opCode() == OpCodes::CALL_INSTANCE;

                std::string signature = "";

                if (!isInstance) {
                    signature = vmState.binder().functionSignature(
                        inst.strValue,
                        inst.parameters);
                } else {
                    signature = vmState.binder().memberFunctionSignature(
                        inst.calledStructType,
                        inst.strValue,
                        inst.parameters);
                }

                if (!vmState.binder().isDefined(signature)) {
                    typeError(index, "The function '" + signature + "' is not defined.");
                }

                auto calledFunc = vmState.binder().getFunction(signature);

                if (!isInstance && calledFunc.isMemberFunction()) {
                    typeError(index, "Member functions must be called with the 'CALLINST' instruction.");
                }

                int calledFuncNumArgs = (int)calledFunc.arguments().size();
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
                std::size_t returnCount = 1;

                if (TypeSystem::isPrimitiveType(function.returnType(), PrimitiveTypes::Void)) {
                    returnCount = 0;
                }

                if (operandStack.size() == returnCount) {
                    if (returnCount > 0) {
                        auto returnType = popType(operandStack);

                        if (*returnType != *function.returnType()) {
                            throw std::runtime_error("Expected '" + TypeChecker::typeToString(function.returnType()) + "' as return type.");
                        }
                    }
                } else {
                    typeError(
                        index,
                        "Expected " + std::to_string(returnCount) + " operand on the stack but got "
                        + std::to_string(operandStack.size()) + " when returning.");
                }
            }
            break;
        case OpCodes::LOAD_ARG:
            operandStack.push(function.parameters()[inst.intValue]);
            break;
        case OpCodes::BRANCH_EQUAL:
        case OpCodes::BRANCH_NOT_EQUAL:
        case OpCodes::BRANCH_GREATER_THAN:
        case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
        case OpCodes::BRANCH_LESS_THAN:
        case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
            {
                assertOperandCount(index, operandStack, 2);
                
                //Check if valid target
                if (!(inst.intValue >= 0 && inst.intValue < (int)numInsts)) {
                    typeError(index, "Invalid jump target (" + std::to_string(inst.intValue) + ").");
                }

                auto op1 = popType(operandStack);
                auto op2 = popType(operandStack);
    
                if (*op1 == *intType) {               
                    if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
                        branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
                    } else {
                        typeError(index, "Expected 2 operands of type Int on the stack.");
                    }
                } else if (*op1 == *boolType) {
                    if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
                        branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
                    } else {
                        typeError(index, "Expected 2 operands of type Bool on the stack.");
                    }
                } else if (*op1 == *floatType) {
                    if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
                        branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
                    } else {
                        typeError(index, "Expected 2 operands of type Float on the stack.");
                    }
                } else {
                    typeError(index, "Expected 2 operands of comparable type on the stack.");  
                }
            }
            break;
        case OpCodes::BRANCH:
            //Check if valid target
            if (!(inst.intValue >= 0 && inst.intValue < (int)numInsts)) {
                typeError(index, "Invalid jump target (" + std::to_string(inst.intValue) + ").");
            }

            branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
            break;
        case OpCodes::LOAD_NULL:
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

                auto elemType = vmState.typeProvider().makeType(inst.strValue);

                if (elemType == nullptr) {
                    typeError(index, "'" + inst.strValue + "' is not a valid type.");
                }

                if (*elemType == *voidType) {
                    typeError(index, "Arrays of type 'Void' is not allowed.");
                }

                operandStack.push(vmState.typeProvider().makeType("Ref.Array[" + inst.strValue + "]"));
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
                    typeError(index, "Expected first operand to be an array reference.");
                }

                if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
                    typeError(index, "Expected second operand to be of type Int.");
                }

                auto elemType = vmState.typeProvider().makeType(inst.strValue);
                assertNotVoidType(index, elemType);

                if (!isNull) {
                    auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();

                    auto error = checkType(arrayElemType, elemType);

                    if (error != "") {
                        typeError(index, error);
                    }
                }

                if (elemType == nullptr) {
                    typeError(index, "There exists no type '" + inst.strValue + "'.");
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
                    typeError(index, "Expected first operand to be an array reference.");
                }

                if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
                    typeError(index, "Expected second operand to be of type Int.");
                }

                auto elemType = vmState.typeProvider().makeType(inst.strValue);
                assertNotVoidType(index, elemType);

                if (!isNull) {
                    auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();

                    auto error = checkType(arrayElemType, elemType);

                    if (error != "") {
                        typeError(index, error);
                    }
                }

                if (elemType == nullptr) {
                    typeError(index, "There exists no type '" + inst.strValue + "'.");
                }

                operandStack.push(elemType);
            }
            break;
        case OpCodes::LOAD_ARRAY_LENGTH:
            {
                assertOperandCount(index, operandStack, 1);
                auto arrayRefType = popType(operandStack);

                if (!TypeSystem::isArray(arrayRefType) && arrayRefType != nullType) {
                    typeError(index, "Expected operand to be an array reference.");
                }

                operandStack.push(intType);
            }
            break;
        case OpCodes::NEW_OBJECT:
            {
                std::string signature = vmState.binder().memberFunctionSignature(
                    inst.calledStructType,
                    inst.strValue,
                    inst.parameters);

                if (!vmState.binder().isDefined(signature)) {
                    typeError(index, "The constructor '" + signature + "' is not defined.");
                }

                auto calledFunc = vmState.binder().getFunction(signature);

                int calledFuncNumArgs = calledFunc.arguments().size();
                assertOperandCount(index, operandStack, calledFuncNumArgs - 1);

                //Check the arguments
                for (int i = calledFuncNumArgs - 1; i >= 1; i--) {
                    auto argType = popType(operandStack);
                    auto error = checkType(calledFunc.arguments()[i], argType);

                    if (error != "") {
                        typeError(index, error);
                    }
                }

                operandStack.push(inst.calledStructType);
            }
            break;
        case OpCodes::LOAD_FIELD:
            {
                assertOperandCount(index, operandStack, 1);

                auto structRefType = popType(operandStack);
                bool isNull = structRefType == nullType;

                if (!TypeSystem::isStruct(structRefType) && !isNull) {
                    typeError(index, "Expected first operand to be a struct reference.");
                }

                std::pair<std::string, std::string> structAndField;

                if (TypeSystem::getStructAndField(inst.strValue, structAndField)) {
                    auto structName = structAndField.first;
                    auto fieldName = structAndField.second;

                    if (!vmState.structProvider().isDefined(structName)) {
                        typeError(index, "'" + structName + "' is not a struct type.");
                    }

                    auto structMetadata = vmState.structProvider()[structName];

                    auto structType = vmState.typeProvider().makeType("Ref.Struct." + structName);

                    if (!isNull) {
                        auto error = checkType(structType, structRefType);

                        if (error != "") {
                            typeError(index, error);
                        }
                    }

                    auto fieldType = structMetadata.fields().at(fieldName).type();

                    if (fieldType == nullptr) {
                        typeError(index, "There exists no field '" + fieldName + "' in the '" + structName + "' struct.");
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
                    typeError(index, "Expected first operand to be a struct reference.");
                }

                std::pair<std::string, std::string> structAndField;

                if (TypeSystem::getStructAndField(inst.strValue, structAndField)) {
                    auto structName = structAndField.first;
                    auto fieldName = structAndField.second;

                    if (!vmState.structProvider().isDefined(structName)) {
                        typeError(index, "'" + structName + "' is not a struct type.");
                    }

                    auto structMetadata = vmState.structProvider()[structName];
                    auto fieldType = structMetadata.fields().at(fieldName).type();

                    if (fieldType == nullptr) {
                        typeError(index, "There exists no field '" + fieldName + "' in the '" + structName + "' struct.");
                    }

                    auto structType = vmState.typeProvider().makeType("Ref.Struct." + structName);

                    if (!isNull) {
                        auto error = checkType(structType, structRefType);

                        if (error != "") {
                            typeError(index, error);
                        }
                    }

                    if (*valueType != *fieldType) {
                        typeError(index, "Expected the second operand to be of type " + fieldType->name() + ".");
                    }
                } else {
                    typeError(index, "Invalid field reference.");
                }
            }
            break;
        case OpCodes::LOAD_STRING:
            operandStack.push(stringType);
            break;
        }

        if (index == numInsts) {
            if (inst.opCode() != OpCodes::RET) {
                typeError(index, "Functions must end with a 'RET' instruction.");
            }
        }

        index++;
    }

    //Check that the branches are valid
    for (auto branch : branches) {
        auto postSourceTypes = branch.branchTypes;
        auto preTargetTypes = function.instructions[branch.target].operandTypes();

        if (postSourceTypes.size() == preTargetTypes.size()) {
            for (std::size_t i = 0; i < postSourceTypes.size(); i++) {
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
        for (std::size_t i = 0; i < numInsts; i++) {
            auto types = function.instructions[i].operandTypes();

            std::cout << i << ": ";

            while (!types.empty()) {
                std::cout << typeToString(types.front()) << " ";
                types.pop_front();
            }

            std::cout << std::endl;
        }
    }

    if (showDebug) {
        std::cout << "----End type checking----" << std::endl;
    }

    for (std::size_t i = 0; i < function.numLocals(); i++) {
        if (function.getLocal(i) == nullptr) {
            typeError(1, "Local " + std::to_string(i) + " is not typed.");
        }
    }
}