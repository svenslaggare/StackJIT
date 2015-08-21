#include "verifier.h"
#include "vmstate.h"
#include "function.h"
#include "instructions.h"
#include "type.h"
#include "classmetadata.h"

#include <iostream>
#include <vector>

namespace {
	std::string typeToString(const Type* type) {
		if (type == nullptr) {
			return "Untyped";
		}

		return type->name();
	}

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

	void typeError(std::size_t instIndex, std::string errorMessage) {
		throw std::runtime_error(std::to_string(instIndex) + ": " + errorMessage);
	}

	void assertOperandCount(std::size_t index, const InstructionTypes& stack, std::size_t count) {
		if (stack.size() < count) {
			typeError(index, "Expected " + std::to_string(count) + " operand(s) on the stack.");
		}
	}

	//Indicates if the given types are equal
	bool sameType(const Type* type1, const Type* type2) {
		return
			*type1 == *type2
			|| (TypeSystem::isReferenceType(type1) && TypeSystem::isNull(type2))
			|| (TypeSystem::isReferenceType(type2) && TypeSystem::isNull(type1));
	}

	std::string checkType(const Type* expectedType, const Type* actualType) {
		if (expectedType == nullptr || *expectedType == *actualType || TypeSystem::isNull(actualType)) {
			return "";
		} else {
			return
				"Expected type '" + typeToString(expectedType)
				+ "' but got type '"
				+ typeToString(actualType) + "'.";
		}
	}

	void assertNotVoidType(std::size_t index, const Type* type) {
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

	//Verifies a function definition
	void verifyFunctionDefinition(Function& function) {
		if (function.returnType() == nullptr) {
			throw std::runtime_error("A function cannot have return type 'Untyped'.");
		}

		if (function.isConstructor() && !TypeSystem::isPrimitiveType(function.returnType(), PrimitiveTypes::Void)) {
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
	}

	//Checks the local types
	void preCheckLocalsTypes(VMState& vmState, Function& function) {
		const auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

		for (std::size_t i = 0; i < function.numLocals(); i++) {
			auto localType = function.getLocal(i);

			if (localType != nullptr) {
				if (localType == voidType) {
					typeError(0, "Locals of 'Void' type are not allowed.");
				};
			}
		}
	}

	//Verifies the branches
	void verifyBranches(Function& function, std::vector<BranchCheck>& branches) {
		for (auto branch : branches) {
			auto postSourceTypes = branch.branchTypes;
			auto preTargetTypes = function.instructions[branch.target].operandTypes();

			if (postSourceTypes.size() == preTargetTypes.size()) {
				for (std::size_t i = 0; i < postSourceTypes.size(); i++) {
					auto postType = popType(postSourceTypes);
					auto preType = popType(preTargetTypes);
					auto error = checkType(postType, preType);

					if (error != "") {
						typeError(branch.source, error);
					}
				}
			} else {
				typeError(branch.source, "Expected the number of types before and after branch to be the same.");
			}
		}
	}

	//Checks the local types
	void postCheckLocalsTypes(Function& function) {
		for (std::size_t i = 0; i < function.numLocals(); i++) {
			if (function.getLocal(i) == nullptr) {
				typeError(0, "Local " + std::to_string(i) + " is not typed.");
			}
		}
	}
}

Verifier::Verifier(VMState& vmState)
	: mVMState(vmState) {

	//Get common types
	mIntType = mVMState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));
	mFloatType = mVMState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Float));
	mBoolType = mVMState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Bool));
	mCharType = mVMState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
	mVoidType = mVMState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));
	mNullType = mVMState.typeProvider().makeType("Ref.Null");
	mStringType = mVMState.typeProvider().makeType(TypeSystem::stringTypeName);
}

void Verifier::verifyInstruction(Function& function, Instruction inst, std::size_t index,
					   			 InstructionTypes& operandStack, std::vector<BranchCheck>& branches) {
	const auto numInstructions = function.instructions.size();

	switch (inst.opCode()) {
		case OpCodes::NOP:
			break;
		case OpCodes::LOAD_INT:
			operandStack.push(mIntType);
			break;
		case OpCodes::LOAD_FLOAT:
			operandStack.push(mFloatType);
			break;
		case OpCodes::LOAD_CHAR:
			operandStack.push(mCharType);
			break;
		case OpCodes::POP:
			assertOperandCount(index, operandStack, 1);
			popType(operandStack);
			break;
		case OpCodes::DUPLICATE:
		{
			assertOperandCount(index, operandStack, 1);
			auto topType = operandStack.top();
			operandStack.push(topType);
		}
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
					operandStack.push(mIntType);
				} else {
					typeError(index, "Expected 2 operands of type Int on the stack.");
				}
			} else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Float)) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
					operandStack.push(mFloatType);
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
			operandStack.push(mBoolType);
		}
			break;
		case OpCodes::AND:
		case OpCodes::OR:
		{
			assertOperandCount(index, operandStack, 2);

			auto op1 = popType(operandStack);
			auto op2 = popType(operandStack);

			if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Bool) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
				operandStack.push(mBoolType);
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
				operandStack.push(mFloatType);
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
				operandStack.push(mIntType);
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
				if (*op1 == *mIntType) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
						operandStack.push(mBoolType);
					} else {
						typeError(index, "Expected 2 operands of type Int on the stack.");
					}
				} else if (*op1 == *mBoolType) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
						operandStack.push(mBoolType);
					} else {
						typeError(index, "Expected 2 operands of type Bool on the stack.");
					}
				} else if (*op1 == *mFloatType) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
						operandStack.push(mBoolType);
					} else {
						typeError(index, "Expected 2 operands of type Float on the stack.");
					}
				} else if (*op1 == *mCharType) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
						operandStack.push(mBoolType);
					} else {
						typeError(index, "Expected 2 operands of type Char on the stack.");
					}
				} else if (sameType(op1, op2)) {
					operandStack.push(mBoolType);
				} else {
					typeError(index, "Expected 2 operands of comparable type on the stack.");
				}
			} else {
				if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
					operandStack.push(mBoolType);
				} else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Float) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
					operandStack.push(mBoolType);
				} else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Char) && TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
					operandStack.push(mBoolType);
				} else {
					typeError(index, "Expected 2 operands of type Int, Char or Float on the stack.");
				}
			}
		}
			break;
		case OpCodes::NOT:
		{
			assertOperandCount(index, operandStack, 1);

			auto op = popType(operandStack);

			if (TypeSystem::isPrimitiveType(op, PrimitiveTypes::Bool)) {
				operandStack.push(mBoolType);
			} else {
				typeError(index, "Expected 1 operand of type Bool on the stack.");
			}
		}
			break;
		case OpCodes::LOAD_LOCAL:
		{
			auto localType = function.getLocal(inst.intValue);

			if (localType != nullptr) {
				operandStack.push(localType);
			} else {
				typeError(index, "Cannot load untyped local (" + std::to_string(inst.intValue) + ").");
			}
		}
			break;
		case OpCodes::STORE_LOCAL:
		{
			assertOperandCount(index, operandStack, 1);

			auto localIndex = inst.intValue;
			auto valueType = popType(operandStack);
			auto localType = function.getLocal(localIndex);

			auto error = checkType(localType, valueType);

			if (error == "") {
				if (localType == nullptr) {
					function.setLocal(localIndex, valueType);
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
				signature = mVMState.binder().functionSignature(
					inst.strValue,
					inst.parameters);
			} else {
				signature = mVMState.binder().memberFunctionSignature(
					inst.classType,
					inst.strValue,
					inst.parameters);
			}

			if (!mVMState.binder().isDefined(signature)) {
				typeError(index, "The function '" + signature + "' is not defined.");
			}

			auto calledFunc = mVMState.binder().getFunction(signature);

			if (!isInstance && calledFunc.isMemberFunction()) {
				typeError(index, "Member functions must be called with the 'CALLINST' instruction.");
			}

			auto calledFuncNumArgs = calledFunc.parameters().size();
			assertOperandCount(index, operandStack, calledFuncNumArgs);

			//Check the arguments
			for (int i = (int)calledFuncNumArgs - 1; i >= 0; i--) {
				auto argType = popType(operandStack);
				auto error = checkType(calledFunc.parameters()[i], argType);

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
						throw std::runtime_error("Expected '" + typeToString(function.returnType()) + "' as return type.");
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
		{
			assertOperandCount(index, operandStack, 2);

			//Check if valid target
			if (!(inst.intValue >= 0 && inst.intValue < (int) numInstructions)) {
				typeError(index, "Invalid jump target (" + std::to_string(inst.intValue) + ").");
			}

			auto op1 = popType(operandStack);
			auto op2 = popType(operandStack);

			if (*op1 == *mIntType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Int on the stack.");
				}
			} else if (*op1 == *mBoolType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Bool on the stack.");
				}
			} else if (*op1 == *mFloatType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Float on the stack.");
				}
			} else if (*op1 == *mCharType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Char on the stack.");
				}
			} else if (sameType(op1, op2)) {
				branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
			} else {
				typeError(index, "Expected 2 operands of comparable type on the stack.");
			}
		}
			break;
		case OpCodes::BRANCH_GREATER_THAN:
		case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
		case OpCodes::BRANCH_LESS_THAN:
		case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
		{
			assertOperandCount(index, operandStack, 2);

			//Check if valid target
			if (!(inst.intValue >= 0 && inst.intValue < (int) numInstructions)) {
				typeError(index, "Invalid jump target (" + std::to_string(inst.intValue) + ").");
			}

			auto op1 = popType(operandStack);
			auto op2 = popType(operandStack);

			if (*op1 == *mIntType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Int on the stack.");
				}
			} else if (*op1 == *mBoolType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Bool on the stack.");
				}
			} else if (*op1 == *mFloatType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Float on the stack.");
				}
			} else if (*op1 == *mCharType) {
				if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
					branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
				} else {
					typeError(index, "Expected 2 operands of type Char on the stack.");
				}
			} else {
				typeError(index, "Expected 2 operands of comparable type on the stack.");
			}
		}
			break;
		case OpCodes::BRANCH:
			//Check if valid target
			if (!(inst.intValue >= 0 && inst.intValue < (int) numInstructions)) {
				typeError(index, "Invalid jump target (" + std::to_string(inst.intValue) + ").");
			}

			branches.push_back({ index, (std::size_t)inst.intValue, operandStack });
			break;
		case OpCodes::LOAD_NULL:
		{
			operandStack.push(mNullType);
		}
			break;
		case OpCodes::NEW_ARRAY:
		{
			assertOperandCount(index, operandStack, 1);

			auto error = checkType(mIntType, popType(operandStack));

			if (error != "") {
				typeError(index, error);
			}

			auto elemType = mVMState.typeProvider().makeType(inst.strValue);

			if (elemType == nullptr) {
				typeError(index, "'" + inst.strValue + "' is not a valid type.");
			}

			if (*elemType == *mVoidType) {
				typeError(index, "Arrays of type 'Void' is not allowed.");
			}

			operandStack.push(mVMState.typeProvider().makeType("Ref.Array[" + inst.strValue + "]"));
		}
			break;
		case OpCodes::STORE_ELEMENT:
		{
			assertOperandCount(index, operandStack, 3);

			auto valueType = popType(operandStack);
			auto indexType = popType(operandStack);
			auto arrayRefType = popType(operandStack);

			bool isNull = arrayRefType == mNullType;

			if (!TypeSystem::isArray(arrayRefType) && !isNull) {
				typeError(index, "Expected first operand to be an array reference, but got type: " + arrayRefType->name() + ".");
			}

			if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
				typeError(index, "Expected second operand to be of type Int but got type: " + indexType->name() + ".");
			}

			auto elemType = mVMState.typeProvider().makeType(inst.strValue);

			if (elemType == nullptr) {
				typeError(index, "There exists no type '" + inst.strValue + "'.");
			}

			assertNotVoidType(index, elemType);

			if (!isNull) {
				auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();

				auto error = checkType(arrayElemType, elemType);

				if (error != "") {
					typeError(index, error);
				}
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

			bool isNull = arrayRefType == mNullType;

			if (!TypeSystem::isArray(arrayRefType) && !isNull) {
				typeError(index, "Expected first operand to be an array reference, but got type: " + arrayRefType->name() + ".");
			}

			if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
				typeError(index, "Expected second operand to be of type Int but got type: " + indexType->name() + ".");
			}

			auto elemType = mVMState.typeProvider().makeType(inst.strValue);

			if (elemType == nullptr) {
				typeError(index, "There exists no type '" + inst.strValue + "'.");
			}

			assertNotVoidType(index, elemType);

			if (!isNull) {
				auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();

				auto error = checkType(arrayElemType, elemType);

				if (error != "") {
					typeError(index, error);
				}
			}

			operandStack.push(elemType);
		}
			break;
		case OpCodes::LOAD_ARRAY_LENGTH:
		{
			assertOperandCount(index, operandStack, 1);
			auto arrayRefType = popType(operandStack);

			if (!TypeSystem::isArray(arrayRefType) && arrayRefType != mNullType) {
				typeError(index, "Expected operand to be an array reference.");
			}

			operandStack.push(mIntType);
		}
			break;
		case OpCodes::NEW_OBJECT:
		{
			std::string signature = mVMState.binder().memberFunctionSignature(
				inst.classType,
				inst.strValue,
				inst.parameters);

			if (!mVMState.binder().isDefined(signature)) {
				typeError(index, "The constructor '" + signature + "' is not defined.");
			}

			auto calledFunc = mVMState.binder().getFunction(signature);

			auto calledFuncNumArgs = calledFunc.parameters().size();
			assertOperandCount(index, operandStack, calledFuncNumArgs - 1);

			//Check the arguments
			for (int i = (int)calledFuncNumArgs - 1; i >= 1; i--) {
				auto argType = popType(operandStack);
				auto error = checkType(calledFunc.parameters()[i], argType);

				if (error != "") {
					typeError(index, error);
				}
			}

			operandStack.push(inst.classType);
		}
			break;
		case OpCodes::LOAD_FIELD:
		{
			assertOperandCount(index, operandStack, 1);

			auto classRefType = popType(operandStack);
			bool isNull = classRefType == mNullType;

			if (!TypeSystem::isClass(classRefType) && !isNull) {
				typeError(index, "Expected first operand to be a class reference, but got type: " + classRefType->name() + ".");
			}

			std::pair<std::string, std::string> structAndField;

			if (TypeSystem::getClassAndField(inst.strValue, structAndField)) {
				auto className = structAndField.first;
				auto fieldName = structAndField.second;

				if (!mVMState.classProvider().isDefined(className)) {
					typeError(index, "'" + className + "' is not a class type.");
				}

				auto structMetadata = mVMState.classProvider().getMetadata(className);
				auto classType = mVMState.typeProvider().makeType("Ref.Class." + className);

				if (!isNull) {
					auto error = checkType(classType, classRefType);

					if (error != "") {
						typeError(index, error);
					}
				}

				auto fieldType = structMetadata.fields().at(fieldName).type();

				if (fieldType == nullptr) {
					typeError(index, "There exists no field '" + fieldName + "' in the '" + className + "' class.");
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
			auto classRefType = popType(operandStack);
			bool isNull = classRefType == mNullType;

			if (!TypeSystem::isClass(classRefType) && !isNull) {
				typeError(index, "Expected first operand to be a class reference, but got type: " + classRefType->name() + ".");
			}

			std::pair<std::string, std::string> structAndField;

			if (TypeSystem::getClassAndField(inst.strValue, structAndField)) {
				auto className = structAndField.first;
				auto fieldName = structAndField.second;

				if (!mVMState.classProvider().isDefined(className)) {
					typeError(index, "'" + className + "' is not a class type.");
				}

				auto classMetadata = mVMState.classProvider().getMetadata(className);
				auto fieldType = classMetadata.fields().at(fieldName).type();

				if (fieldType == nullptr) {
					typeError(index, "There exists no field '" + fieldName + "' in the '" + className + "' class.");
				}

				auto classType = mVMState.typeProvider().makeType("Ref.Class." + className);

				if (!isNull) {
					auto error = checkType(classType, classRefType);

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
			if (mStringType == nullptr) {
				typeError(index, "The 'LDSTR' instruction requires the runtime library to be loaded.");
			}

			operandStack.push(mStringType);
			break;
	}
}

void Verifier::verifyFunction(Function& function) {
	InstructionTypes operandStack;

	const auto numInstructions = function.instructions.size();

	if (numInstructions == 0) {
		typeError(0, "Empty functions are not allowed.");
	}

	//Check that local types are valid
	preCheckLocalsTypes(mVMState, function);

	//Check the function definition
	verifyFunctionDefinition(function);

	std::size_t index = 0;
	std::vector<BranchCheck> branches;

	//Check instructions
	for (auto& inst : function.instructions) {
		inst.setOperandTypes(asList(operandStack));

		//Calculate the maximum size of the stack
		auto stackSize = inst.operandTypes().size();
		if (stackSize > function.operandStackSize()) {
			function.setOperandStackSize(stackSize);
		}

		verifyInstruction(function, inst, index, operandStack, branches);

		if (index == numInstructions - 1) {
			if (inst.opCode() != OpCodes::RET) {
				typeError(index, "Functions must end with the 'RET' instruction.");
			}
		}

		index++;
	}

	//Check that the branches are valid
	verifyBranches(function, branches);

	//Check that all locals has been typed
	postCheckLocalsTypes(function);
}