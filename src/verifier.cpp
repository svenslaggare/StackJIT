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
				"Expected type '" + typeToString(expectedType)
				+ "' but got type '"
				+ typeToString(actualType) + "'.";
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
					typeError(1, "Locals of 'Void' type are not allowed.");
				};
			}
		}
	}

	//Verifies the given instruction
	void verifyInstruction(VMState& vmState, Function& function, Instruction inst, std::size_t index,
						   InstructionTypes& operandStack, std::vector<BranchCheck>& branches) {
		const auto numInstructions = function.instructions.size();

		//Get common types
		const auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));
		const auto floatType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Float));
		const auto boolType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Bool));
		const auto charType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
		const auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));
		const auto nullType = vmState.typeProvider().makeType("Ref.Null");
		const auto stringType = vmState.typeProvider().makeType("Ref.Array[Char]");

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
						signature = vmState.binder().functionSignature(
							inst.strValue,
							inst.parameters);
					} else {
						signature = vmState.binder().memberFunctionSignature(
							inst.classType,
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

					int calledFuncNumArgs = (int) calledFunc.parameters().size();
					assertOperandCount(index, operandStack, calledFuncNumArgs);

					//Check the arguments
					for (int i = calledFuncNumArgs - 1; i >= 0; i--) {
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
				if (!(inst.intValue >= 0 && inst.intValue < (int) numInstructions)) {
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
						inst.classType,
						inst.strValue,
						inst.parameters);

					if (!vmState.binder().isDefined(signature)) {
						typeError(index, "The constructor '" + signature + "' is not defined.");
					}

					auto calledFunc = vmState.binder().getFunction(signature);

					int calledFuncNumArgs = calledFunc.parameters().size();
					assertOperandCount(index, operandStack, calledFuncNumArgs - 1);

					//Check the arguments
					for (int i = calledFuncNumArgs - 1; i >= 1; i--) {
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
					bool isNull = classRefType == nullType;

					if (!TypeSystem::isClass(classRefType) && !isNull) {
						typeError(index, "Expected first operand to be a class reference.");
					}

					std::pair<std::string, std::string> structAndField;

					if (TypeSystem::getClassAndField(inst.strValue, structAndField)) {
						auto className = structAndField.first;
						auto fieldName = structAndField.second;

						if (!vmState.classProvider().isDefined(className)) {
							typeError(index, "'" + className + "' is not a class type.");
						}

						auto structMetadata = vmState.classProvider()[className];
						auto classType = vmState.typeProvider().makeType("Ref.Class." + className);

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
					bool isNull = classRefType == nullType;

					if (!TypeSystem::isClass(classRefType) && !isNull) {
						typeError(index, "Expected first operand to be a class reference.");
					}

					std::pair<std::string, std::string> structAndField;

					if (TypeSystem::getClassAndField(inst.strValue, structAndField)) {
						auto className = structAndField.first;
						auto fieldName = structAndField.second;

						if (!vmState.classProvider().isDefined(className)) {
							typeError(index, "'" + className + "' is not a class type.");
						}

						auto classMetadata = vmState.classProvider()[className];
						auto fieldType = classMetadata.fields().at(fieldName).type();

						if (fieldType == nullptr) {
							typeError(index, "There exists no field '" + fieldName + "' in the '" + className + "' class.");
						}

						auto classType = vmState.typeProvider().makeType("Ref.Class." + className);

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
				operandStack.push(stringType);
				break;
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
				typeError(1, "Local " + std::to_string(i) + " is not typed.");
			}
		}
	}
}

void Verifier::verifyFunction(Function& function, VMState& vmState) {
	InstructionTypes operandStack;

	const auto numInstructions = function.instructions.size();

	if (numInstructions == 0) {
		typeError(1, "Empty functions are not allowed.");
	}

	//Check that local types are valid
	preCheckLocalsTypes(vmState, function);

	//Check the function definition
	verifyFunctionDefinition(function);

	std::size_t index = 1;
	std::vector<BranchCheck> branches;

	//Check instructions
	for (auto& inst : function.instructions) {
		inst.setOperandTypes(asList(operandStack));

		//Calculate the maximum size of the stack
		auto stackSize = inst.operandTypes().size();
		if (stackSize > function.operandStackSize()) {
			function.setOperandStackSize(stackSize);
		}

		verifyInstruction(vmState, function, inst, index, operandStack, branches);

		if (index == numInstructions) {
			if (inst.opCode() != OpCodes::RET) {
				typeError(index, "Functions must end with a 'RET' instruction.");
			}
		}

		index++;
	}

	//Check that the branches are valid
	verifyBranches(function, branches);

	//Check that all locals has been typed
	postCheckLocalsTypes(function);
}