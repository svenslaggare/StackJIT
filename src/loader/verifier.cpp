#include "verifier.h"
#include "../vmstate.h"
#include "../core/function.h"
#include "../core/instruction.h"
#include "../type/type.h"
#include "../type/classmetadata.h"
#include "../core/functionsignature.h"
#include <iostream>
#include <vector>

namespace stackjit {
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

		void typeError(std::string functionSignature, std::size_t instIndex, std::string errorMessage) {
			throw std::runtime_error(functionSignature + " @ " + std::to_string(instIndex) + ": " + errorMessage);
		}

		void assertOperandCount(std::string functionSignature, std::size_t index, const InstructionTypes& stack, std::size_t count) {
			if (stack.size() < count) {
				typeError(functionSignature, index, "Expected " + std::to_string(count) + " operand(s) on the stack.");
			}
		}

		//Indicates if the given class is a subtype of the given class
		bool isSubtypeOf(const Type* baseClass, const Type* subClass) {
			if (baseClass->isClass() && subClass->isClass()) {
				auto baseClassType = static_cast<const ClassType*>(baseClass);
				auto subClassType = static_cast<const ClassType*>(subClass);
				return TypeSystem::isSubtypeOf(baseClassType, subClassType);
			}

			return false;
		}

		//Indicates if the given types are equal
		bool sameType(const Type* type1, const Type* type2) {
			return *type1 == *type2;
		}

		std::string checkType(const Type* expectedType, const Type* actualType) {
			if (sameType(expectedType, actualType) || isSubtypeOf(expectedType, actualType)) {
				return "";
			} else {
				return
					"Expected type '" + typeToString(expectedType)
					+ "' but got type '"
					+ typeToString(actualType) + "'.";
			}
		}

		void assertNotVoidType(std::string functionSignature, std::size_t index, const Type* type) {
			if (type != nullptr && type->name() == "Void") {
				typeError(functionSignature, index, "Void type not allowed.");
			}
		}

		std::vector<const Type*> toVector(InstructionTypes typesStack) {
			std::vector<const Type*> types;

			while (!typesStack.empty()) {
				types.push_back(typesStack.top());
				typesStack.pop();
			}

			return types;
		}

		std::deque<const Type*> toList(const std::vector<const Type*>& types) {
			std::deque<const Type*> typesList;

			for (auto& type : types) {
				typesList.push_back(type);
			}

			return typesList;
		}

		//Finds an inherited member function
		std::string findInheritedMemberFunction(const VMState& vmState,
												std::string& initialSignature,
												const ClassType* classType,
												std::string name,
												const std::vector<const Type*> parameters) {
			std::string signature = FunctionSignature::memberFunction(
				classType,
				name,
				parameters).str();

			if (initialSignature.empty()) {
				initialSignature = signature;
			}

			if (vmState.binder().isDefined(signature)) {
				return signature;
			}

			if (classType->metadata()->parentClass() != nullptr) {
				return findInheritedMemberFunction(
					vmState,
					initialSignature,
					classType->metadata()->parentClass(),
					name,
					parameters);
			} else {
				return initialSignature;
			}
		}

		std::string findInheritedMemberFunction(const VMState& vmState,
												const ClassType* classType,
												std::string name,
												const std::vector<const Type*> parameters) {
			std::string initial;
			return findInheritedMemberFunction(
				vmState,
				initial,
				classType,
				name,
				parameters);
		}

		//Indicates if the given function can call the given member function
		bool canCallMemberFunction(const FunctionDefinition& callingFunc, const FunctionDefinition& funcToCall) {
			if (funcToCall.accessModifier() == AccessModifier::Public) {
				return true;
			} else {
				if (callingFunc.classType() != nullptr) {
					return callingFunc.classType() == funcToCall.classType();
				} else {
					return false;
				}
			}
		}

		//Indicates if the given function can read/write the given field
		bool canReadOrWriteField(const FunctionDefinition& func,
								 const ClassMetadata& classMetadata,
								 const ClassType* classType,
								 std::string fieldName) {
			auto& field = classMetadata.fields().at(fieldName);

			if (field.accessModifier() == AccessModifier::Public) {
				return true;
			} else {
				if (func.classType() != nullptr) {
					return func.classType() == classType;
				} else {
					return false;
				}
			}
		}

		//Verifies a function definition
		void verifyFunctionDefinition(ManagedFunction& function) {
			if (function.def().returnType() == nullptr) {
				throw std::runtime_error("A function cannot have return type 'Untyped'.");
			}

			if (function.def().isConstructor() &&
				!TypeSystem::isPrimitiveType(function.def().returnType(), PrimitiveTypes::Void)) {
				throw std::runtime_error("Constructors must have return type 'Void'.");
			}

			int i = 0;
			for (auto arg : function.def().parameters()) {
				if (arg == nullptr || TypeSystem::isPrimitiveType(arg, PrimitiveTypes::Void)) {
					throw std::runtime_error(
						"Parameter: " + std::to_string(i) + " in function '" + function.def().name()
						+ "' cannot be of type '" + typeToString(arg) + "'.");
				}

				i++;
			}
		}

		//Checks the local types
		void preCheckLocalsTypes(VMState& vmState, ManagedFunction& function, std::string functionSignature) {
			const auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

			for (std::size_t i = 0; i < function.numLocals(); i++) {
				auto localType = function.getLocal(i);

				if (localType != nullptr) {
					if (localType == voidType) {
						typeError(functionSignature, 0, "Locals of 'Void' type are not allowed.");
					}
				}
			}
		}

		//Verifies the branches
		void verifyBranches(ManagedFunction& function, std::string functionSignature, std::vector<BranchCheck>& branches) {
			for (auto& branch : branches) {
				auto postSourceTypes = branch.branchTypes;
				auto preTargetTypes = toList(function.instructions()[branch.target].operandTypes());

				if (postSourceTypes.size() == preTargetTypes.size()) {
					for (std::size_t i = 0; i < postSourceTypes.size(); i++) {
						auto postType = popType(postSourceTypes);
						auto preType = popType(preTargetTypes);
						auto error = checkType(postType, preType);

						if (error != "") {
							typeError(functionSignature, branch.source, error);
						}
					}
				} else {
					typeError(
						functionSignature,
						branch.source,
						"Expected the number of types before and after branch to be the same.");
				}
			}
		}

		//Checks the local types
		void postCheckLocalsTypes(ManagedFunction& function, std::string functionSignature) {
			for (std::size_t i = 0; i < function.numLocals(); i++) {
				if (function.getLocal(i) == nullptr) {
					typeError(functionSignature, 0, "Local " + std::to_string(i) + " is not typed.");
				}
			}
		}
	}

	Verifier::Verifier(VMState& vmState)
		: mVMState(vmState) {

	}

	const std::string Verifier::sIntTypeName = TypeSystem::toString(PrimitiveTypes::Integer);
	const std::string Verifier::sFloatTypeName = TypeSystem::toString(PrimitiveTypes::Float);
	const std::string Verifier::sBoolTypeName = TypeSystem::toString(PrimitiveTypes::Bool);
	const std::string Verifier::sCharTypeName = TypeSystem::toString(PrimitiveTypes::Char);
	const std::string Verifier::sVoidTypeName = TypeSystem::toString(PrimitiveTypes::Void);

	const Type* Verifier::getOrSetType(const std::string& name, const Type*& typeField) {
		if (typeField == nullptr) {
			typeField = mVMState.typeProvider().makeType(name);
			return typeField;
		} else {
			return typeField;
		}
	}

	const Type* Verifier::intType() {
		return getOrSetType(sIntTypeName, mIntType);
	}

	const Type* Verifier::floatType() {
		return getOrSetType(sFloatTypeName, mFloatType);
	}

	const Type* Verifier::boolType() {
		return getOrSetType(sBoolTypeName, mBoolType);
	}

	const Type* Verifier::charType() {
		return getOrSetType(sCharTypeName, mCharType);
	}

	const Type* Verifier::voidType() {
		return getOrSetType(sVoidTypeName, mVoidType);
	}

	const Type* Verifier::nullType() {
		return getOrSetType(TypeSystem::nullTypeName, mNullType);
	}

	const Type* Verifier::stringType() {
		return getOrSetType(TypeSystem::stringTypeName, mStringType);
	}

	void Verifier::verifyInstruction(ManagedFunction& function,
									 std::string functionSignature,
									 Instruction& instruction,
									 std::size_t index,
									 InstructionTypes& operandStack,
									 std::vector<BranchCheck>& branches) {
		const auto numInstructions = function.instructions().size();

		switch (instruction.opCode()) {
			case OpCodes::NOP:
				break;
			case OpCodes::LOAD_INT:
				operandStack.push(intType());
				break;
			case OpCodes::LOAD_FLOAT:
				operandStack.push(floatType());
				break;
			case OpCodes::LOAD_CHAR:
				operandStack.push(charType());
				break;
			case OpCodes::POP:
				assertOperandCount(functionSignature, index, operandStack, 1);
				popType(operandStack);
				break;
			case OpCodes::DUPLICATE: {
				assertOperandCount(functionSignature, index, operandStack, 1);
				auto topType = operandStack.top();
				operandStack.push(topType);
				break;
			}
			case OpCodes::ADD:
			case OpCodes::SUB:
			case OpCodes::MUL:
			case OpCodes::DIV: {
				assertOperandCount(functionSignature, index, operandStack, 2);

				auto op1 = popType(operandStack);
				auto op2 = popType(operandStack);

				if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer)) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
						operandStack.push(intType());
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sIntTypeName + " on the stack.");
					}
				} else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Float)) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
						operandStack.push(floatType());
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sFloatTypeName + " on the stack.");
					}
				} else {
					typeError(functionSignature, index, "Expected 2 operands of type " + sIntTypeName + " or " + sFloatTypeName + " on the stack.");
				}
				break;
			}
			case OpCodes::LOAD_TRUE:
			case OpCodes::LOAD_FALSE: {
				operandStack.push(boolType());
				break;
			}
			case OpCodes::AND:
			case OpCodes::OR: {
				assertOperandCount(functionSignature, index, operandStack, 2);

				auto op1 = popType(operandStack);
				auto op2 = popType(operandStack);

				if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Bool) &&
					TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
					operandStack.push(boolType());
				} else {
					typeError(functionSignature, index, "Expected 2 operands of type " + sBoolTypeName + " on the stack.");
				}
				break;
			}
			case OpCodes::CONVERT_INT_TO_FLOAT: {
				assertOperandCount(functionSignature, index, operandStack, 1);

				auto op = popType(operandStack);
				if (TypeSystem::isPrimitiveType(op, PrimitiveTypes::Integer)) {
					operandStack.push(floatType());
				} else {
					typeError(functionSignature, index, "Expected 1 operand of type " + sIntTypeName + " on the stack.");
				}

				break;
			}
			case OpCodes::CONVERT_FLOAT_TO_INT: {
				assertOperandCount(functionSignature, index, operandStack, 1);

				auto op = popType(operandStack);
				if (TypeSystem::isPrimitiveType(op, PrimitiveTypes::Float)) {
					operandStack.push(intType());
				} else {
					typeError(functionSignature, index, "Expected 1 operand of type " + sFloatTypeName + " on the stack.");
				}
				break;
			}
			case OpCodes::COMPARE_EQUAL:
			case OpCodes::COMPARE_NOT_EQUAL:
			case OpCodes::COMPARE_GREATER_THAN:
			case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
			case OpCodes::COMPARE_LESS_THAN:
			case OpCodes::COMPARE_LESS_THAN_OR_EQUAL: {
				assertOperandCount(functionSignature, index, operandStack, 2);

				auto op1 = popType(operandStack);
				auto op2 = popType(operandStack);

				if (instruction.opCode() == OpCodes::COMPARE_EQUAL || instruction.opCode() == OpCodes::COMPARE_NOT_EQUAL) {
					if (*op1 == *intType()) {
						if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
							operandStack.push(boolType());
						} else {
							typeError(functionSignature, index, "Expected 2 operands of type " + sIntTypeName + " on the stack.");
						}
					} else if (*op1 == *boolType()) {
						if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
							operandStack.push(boolType());
						} else {
							typeError(functionSignature, index, "Expected 2 operands of type " + sBoolTypeName + " on the stack.");
						}
					} else if (*op1 == *floatType()) {
						if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
							operandStack.push(boolType());
						} else {
							typeError(functionSignature, index, "Expected 2 operands of type " + sFloatTypeName + " on the stack.");
						}
					} else if (*op1 == *charType()) {
						if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
							operandStack.push(boolType());
						} else {
							typeError(functionSignature, index, "Expected 2 operands of type " + sCharTypeName + " on the stack.");
						}
					} else if (sameType(op1, op2)) {
						operandStack.push(boolType());
					} else {
						typeError(functionSignature, index, "Expected 2 operands of comparable type on the stack.");
					}
				} else {
					if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Integer) &&
						TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
						operandStack.push(boolType());
					} else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Float) &&
							   TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
						operandStack.push(boolType());
					} else if (TypeSystem::isPrimitiveType(op1, PrimitiveTypes::Char) &&
							   TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
						operandStack.push(boolType());
					} else {
						typeError(
							functionSignature,
							index,
							"Expected 2 operands of type " + sIntTypeName + ", " + sFloatTypeName + " or " + sCharTypeName + " on the stack.");
					}
				}

				break;
			}
			case OpCodes::NOT: {
				assertOperandCount(functionSignature, index, operandStack, 1);

				auto op = popType(operandStack);

				if (TypeSystem::isPrimitiveType(op, PrimitiveTypes::Bool)) {
					operandStack.push(boolType());
				} else {
					typeError(functionSignature, index, "Expected 1 operand of type " + sBoolTypeName + " on the stack.");
				}

				break;
			}
			case OpCodes::LOAD_LOCAL: {
				auto localType = function.getLocal((std::size_t)instruction.intValue);

				if (localType != nullptr) {
					operandStack.push(localType);
				} else {
					typeError(functionSignature, index, "Cannot load untyped local (" + std::to_string(instruction.intValue) + ").");
				}

				break;
			}
			case OpCodes::STORE_LOCAL: {
				assertOperandCount(functionSignature, index, operandStack, 1);

				auto localIndex = (std::size_t)instruction.intValue;
				auto valueType = popType(operandStack);
				auto localType = function.getLocal(localIndex);
				bool setType = false;

				//We allow implicit typed locals.
				if (localType == nullptr) {
					localType = valueType;
					setType = true;
				}

				auto error = checkType(localType, valueType);

				if (error == "") {
					if (setType) {
						function.setLocal(localIndex, valueType);
					}
				} else {
					typeError(functionSignature, index, error);
				}

				break;
			}
			case OpCodes::CALL:
			case OpCodes::CALL_INSTANCE:
			case OpCodes::CALL_VIRTUAL: {
				bool isInstance = instruction.isCallInstance();
				bool isVirtual = instruction.opCode() == OpCodes::CALL_VIRTUAL;

				std::string signature = "";

				if (!isInstance) {
					signature = FunctionSignature::function(
						instruction.stringValue,
						instruction.parameters).str();
				} else {
					signature = findInheritedMemberFunction(
						mVMState,
						instruction.classType,
						instruction.stringValue,
						instruction.parameters);
				}

				if (!mVMState.binder().isDefined(signature)) {
					typeError(functionSignature, index, "The function '" + signature + "' is not defined.");
				}

				auto& funcToCall = mVMState.binder().getFunction(signature);

				//Rebind the call, since we might call an inherited function
				if (isInstance) {
					instruction.classType = funcToCall.classType();
				}

				if (!isInstance && funcToCall.isMemberFunction()) {
					typeError(functionSignature, index, "Member functions must be called with the 'CALLINST' instruction.");
				}

				if (isInstance && funcToCall.isMemberFunction()) {
					if (!isVirtual && funcToCall.isVirtual()) {
						typeError(functionSignature, index, "Virtual member functions must be called with the 'CALLVIRT' instruction.");
					} else if (isVirtual && !funcToCall.isVirtual()) {
						typeError(functionSignature, index, "Non virtual member functions must be called with the 'CALLINST' instruction.");
					}
				}

				if (funcToCall.isConstructor()) {
					bool isInvalid = false;
					if (!isInstance) {
						isInvalid = true;
					} else if (!(function.def().isConstructor()
							   && TypeSystem::isSubtypeOf(funcToCall.classType(), function.def().classType()))) {
						isInvalid = true;
					}

					if (isInvalid) {
						typeError(functionSignature, index, "Cannot call constructor '" + signature + "'.");
					}
				}

				//Check if the member function can be called
				if (isInstance) {
					if (!canCallMemberFunction(function.def(), funcToCall)) {
						typeError(functionSignature, index, "Cannot call private function '" + signature + "'.");
					}
				}

				auto calledFuncNumArgs = funcToCall.parameters().size();
				assertOperandCount(functionSignature, index, operandStack, calledFuncNumArgs);

				//Check the arguments
				for (int i = (int)calledFuncNumArgs - 1; i >= 0; i--) {
					auto argType = popType(operandStack);
					auto error = checkType(funcToCall.parameters()[i], argType);

					if (error != "") {
						typeError(functionSignature, index, error);
					}
				}

				//Return type
				if (!TypeSystem::isPrimitiveType(funcToCall.returnType(), PrimitiveTypes::Void)) {
					operandStack.push(funcToCall.returnType());
				}

				break;
			}
			case OpCodes::RET: {
				std::size_t returnCount = 1;

				if (TypeSystem::isPrimitiveType(function.def().returnType(), PrimitiveTypes::Void)) {
					returnCount = 0;
				}

				if (operandStack.size() == returnCount) {
					if (returnCount > 0) {
						auto returnType = popType(operandStack);

						if (!sameType(returnType, function.def().returnType())) {
							throw std::runtime_error(
								"Expected '" + typeToString(function.def().returnType()) + "' as the return type.");
						}
					}
				} else {
					typeError(
						functionSignature,
						index,
						"Expected " + std::to_string(returnCount) + " operand on the stack but got "
						+ std::to_string(operandStack.size()) + " when returning.");
				}

				break;
			}
			case OpCodes::LOAD_ARG: {
				int argNum = instruction.intValue;

				if (argNum >= 0 && argNum < (int)function.def().parameters().size()) {
					operandStack.push(function.def().parameters()[argNum]);
				} else {
					throw std::runtime_error("The argument index is out of range.");
				}
				break;
			}
			case OpCodes::BRANCH_EQUAL:
			case OpCodes::BRANCH_NOT_EQUAL: {
				assertOperandCount(functionSignature, index, operandStack, 2);

				//Check if valid target
				if (!(instruction.intValue >= 0 && instruction.intValue < (int)numInstructions)) {
					typeError(functionSignature, index, "Invalid jump target (" + std::to_string(instruction.intValue) + ").");
				}

				auto op1 = popType(operandStack);
				auto op2 = popType(operandStack);

				if (*op1 == *intType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sIntTypeName + " on the stack.");
					}
				} else if (*op1 == *boolType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sBoolTypeName + " on the stack.");
					}
				} else if (*op1 == *floatType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sFloatTypeName + " on the stack.");
					}
				} else if (*op1 == *charType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sCharTypeName + " on the stack.");
					}
				} else if (sameType(op1, op2)) {
					branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
				} else {
					typeError(functionSignature, index, "Expected 2 operands of comparable type on the stack.");
				}

				break;
			}
			case OpCodes::BRANCH_GREATER_THAN:
			case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
			case OpCodes::BRANCH_LESS_THAN:
			case OpCodes::BRANCH_LESS_THAN_OR_EQUAL: {
				assertOperandCount(functionSignature, index, operandStack, 2);

				//Check if valid target
				if (!(instruction.intValue >= 0 && instruction.intValue < (int)numInstructions)) {
					typeError(functionSignature, index, "Invalid jump target (" + std::to_string(instruction.intValue) + ").");
				}

				auto op1 = popType(operandStack);
				auto op2 = popType(operandStack);

				if (*op1 == *intType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Integer)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sIntTypeName + " on the stack.");
					}
				} else if (*op1 == *boolType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Bool)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sBoolTypeName + " on the stack.");
					}
				} else if (*op1 == *floatType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Float)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sFloatTypeName + " on the stack.");
					}
				} else if (*op1 == *charType()) {
					if (TypeSystem::isPrimitiveType(op2, PrimitiveTypes::Char)) {
						branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
					} else {
						typeError(functionSignature, index, "Expected 2 operands of type " + sCharTypeName + " on the stack.");
					}
				} else {
					typeError(functionSignature, index, "Expected 2 operands of comparable type on the stack.");
				}

				break;
			}
			case OpCodes::BRANCH:
				//Check if valid target
				if (!(instruction.intValue >= 0 && instruction.intValue < (int)numInstructions)) {
					typeError(functionSignature, index, "Invalid jump target (" + std::to_string(instruction.intValue) + ").");
				}

				branches.push_back({index, (std::size_t)instruction.intValue, operandStack});
				break;
			case OpCodes::LOAD_NULL: {
				operandStack.push(nullType());
				break;
			}
			case OpCodes::NEW_ARRAY: {
				assertOperandCount(functionSignature, index, operandStack, 1);

				auto error = checkType(intType(), popType(operandStack));

				if (error != "") {
					typeError(functionSignature, index, error);
				}

				auto elemType = mVMState.typeProvider().makeType(instruction.stringValue);

				if (elemType == nullptr) {
					typeError(functionSignature, index, "'" + instruction.stringValue + "' is not a valid type.");
				}

				if (*elemType == *voidType()) {
					typeError(functionSignature, index, "Arrays of type '" + sVoidTypeName + "' is not allowed.");
				}

				operandStack.push(mVMState.typeProvider().makeType("Ref.Array[" + instruction.stringValue + "]"));
				break;
			}
			case OpCodes::STORE_ELEMENT: {
				assertOperandCount(functionSignature, index, operandStack, 3);

				auto valueType = popType(operandStack);
				auto indexType = popType(operandStack);
				auto arrayRefType = popType(operandStack);

				bool isNull = arrayRefType == nullType();

				if (!arrayRefType->isArray() && !isNull) {
					typeError(
						functionSignature,
						index,
						"Expected first operand to be an array reference, but got type: " + arrayRefType->name() + ".");
				}

				if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
					typeError(
						functionSignature,
						index,
						"Expected second operand to be of type " + sIntTypeName + " but got type: " + indexType->name() + ".");
				}

				auto elemType = mVMState.typeProvider().makeType(instruction.stringValue);

				if (elemType == nullptr) {
					typeError(functionSignature, index, "There exists no type called '" + instruction.stringValue + "'.");
				}

				assertNotVoidType(functionSignature, index, elemType);

				if (!isNull) {
					auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();
					auto error = checkType(arrayElemType, elemType);

					if (error != "") {
						typeError(functionSignature, index, error);
					}
				}

				if (!sameType(valueType, elemType)) {
					typeError(functionSignature, index, "Expected third operand to be of type " + elemType->name() + ".");
				}

				break;
			}
			case OpCodes::LOAD_ELEMENT: {
				assertOperandCount(functionSignature, index, operandStack, 2);

				auto indexType = popType(operandStack);
				auto arrayRefType = popType(operandStack);

				bool isNull = arrayRefType == nullType();

				if (!arrayRefType->isArray() && !isNull) {
					typeError(
						functionSignature,
						index,
						"Expected first operand to be an array reference, but got type: " + arrayRefType->name() + ".");
				}

				if (!TypeSystem::isPrimitiveType(indexType, PrimitiveTypes::Integer)) {
					typeError(
						functionSignature,
						index,
						"Expected second operand to be of type " + sIntTypeName + " but got type: " + indexType->name() + ".");
				}

				auto elemType = mVMState.typeProvider().makeType(instruction.stringValue);

				if (elemType == nullptr) {
					typeError(functionSignature, index, "There exists no type called '" + instruction.stringValue + "'.");
				}

				assertNotVoidType(functionSignature, index, elemType);

				if (!isNull) {
					auto arrayElemType = dynamic_cast<const ArrayType*>(arrayRefType)->elementType();

					auto error = checkType(arrayElemType, elemType);
					if (error != "") {
						typeError(functionSignature, index, error);
					}
				}

				operandStack.push(elemType);
				break;
			}
			case OpCodes::LOAD_ARRAY_LENGTH: {
				assertOperandCount(functionSignature, index, operandStack, 1);
				auto arrayRefType = popType(operandStack);

				if (!arrayRefType->isArray() && arrayRefType != nullType()) {
					typeError(functionSignature, index, "Expected operand to be an array reference.");
				}

				operandStack.push(intType());
				break;
			}
			case OpCodes::NEW_OBJECT: {
				auto signature = FunctionSignature::memberFunction(
					instruction.classType,
					instruction.stringValue,
					instruction.parameters).str();

				if (!mVMState.binder().isDefined(signature)) {
					typeError(functionSignature, index, "The constructor '" + signature + "' is not defined.");
				}

				auto calledFunc = mVMState.binder().getFunction(signature);

				auto calledFuncNumArgs = calledFunc.parameters().size();
				assertOperandCount(functionSignature, index, operandStack, calledFuncNumArgs - 1);

				//Check the arguments
				for (int i = (int)calledFuncNumArgs - 1; i >= 1; i--) {
					auto argType = popType(operandStack);
					auto error = checkType(calledFunc.parameters()[i], argType);

					if (error != "") {
						typeError(functionSignature, index, error);
					}
				}

				operandStack.push(instruction.classType);
				break;
			}
			case OpCodes::LOAD_FIELD: {
				assertOperandCount(functionSignature, index, operandStack, 1);

				auto classRefType = popType(operandStack);
				bool isNull = classRefType == nullType();

				if (!classRefType->isClass() && !isNull) {
					typeError(
						functionSignature,
						index,
						"Expected first operand to be a class reference, but got type: " + classRefType->name() + ".");
				}

				std::string className;
				std::string fieldName;

				if (TypeSystem::getClassAndFieldName(instruction.stringValue, className, fieldName)) {
					if (!mVMState.classProvider().isDefined(className)) {
						typeError(functionSignature, index, "'" + className + "' is not a class type.");
					}

					auto& classMetadata = mVMState.classProvider().getMetadata(className);
					auto classType = mVMState.typeProvider().makeType("Ref." + className);

					if (!isNull) {
						auto error = checkType(classType, classRefType);

						if (error != "") {
							typeError(functionSignature, index, error);
						}
					}

					if (!classMetadata.fieldExists(fieldName)) {
						typeError(
							functionSignature,
							index,
							"There exists no field '" + fieldName + "' in the class '" + className + "'.");
					}

					auto canReadOrWrite = canReadOrWriteField(
						function.def(),
						classMetadata,
						static_cast<const ClassType*>(classType),
						fieldName);

					if (!canReadOrWrite) {
						typeError(
							functionSignature,
							index,
							"Cannot read from private field '" + fieldName + "' of class '" + className + "'.");
					}

					operandStack.push(classMetadata.fields().at(fieldName).type());
				} else {
					typeError(functionSignature, index, "Invalid field reference.");
				}

				break;
			}
			case OpCodes::STORE_FIELD: {
				assertOperandCount(functionSignature, index, operandStack, 2);

				auto valueType = popType(operandStack);
				auto classRefType = popType(operandStack);
				bool isNull = classRefType == nullType();

				if (!classRefType->isClass() && !isNull) {
					typeError(
						functionSignature,
						index,
						"Expected first operand to be a class reference, but got type: " + classRefType->name() + ".");
				}

				std::string className;
				std::string fieldName;

				if (TypeSystem::getClassAndFieldName(instruction.stringValue, className, fieldName)) {
					if (!mVMState.classProvider().isDefined(className)) {
						typeError(functionSignature, index, "'" + className + "' is not a class type.");
					}

					auto& classMetadata = mVMState.classProvider().getMetadata(className);

					if (!classMetadata.fieldExists(fieldName)) {
						typeError(
							functionSignature,
							index,
							"There exists no field '" + fieldName + "' in the class '" + className + "'.");
					}

					auto classType = mVMState.typeProvider().makeType("Ref." + className);

					if (!isNull) {
						auto error = checkType(classType, classRefType);

						if (error != "") {
							typeError(functionSignature, index, error);
						}
					}

					auto canReadOrWrite = canReadOrWriteField(
						function.def(),
						classMetadata,
						static_cast<const ClassType*>(classType),
						fieldName);
					if (!canReadOrWrite) {
						typeError(
							functionSignature,
							index,
							"Cannot write to private field '" + fieldName + "' of class '" + className + "'.");
					}

					auto fieldType = classMetadata.fields().at(fieldName).type();
					if (!sameType(valueType, fieldType)) {
						typeError(
							functionSignature,
							index,
							"Expected the second operand to be of type " + fieldType->name() + ".");
					}
				} else {
					typeError(functionSignature, index, "Invalid field reference.");
				}
				break;
			}
			case OpCodes::LOAD_STRING:
				if (stringType() == nullptr) {
					typeError(
						functionSignature,
						index,
						"The 'LDSTR' instruction requires the runtime library to be loaded.");
				}

				operandStack.push(stringType());
				break;
		}
	}

	void Verifier::verifyFunction(ManagedFunction& function) {
		InstructionTypes operandStack;
		const auto numInstructions = function.instructions().size();
		std::string functionSignature = FunctionSignature::from(function.def()).str();

		if (numInstructions == 0) {
			typeError(functionSignature, 0, "Empty functions are not allowed.");
		}

		//Check that local types are valid
		preCheckLocalsTypes(mVMState, function, functionSignature);

		//Check the function definition
		verifyFunctionDefinition(function);

		std::size_t index = 0;
		std::vector<BranchCheck> branches;

		//Check instructions
		for (auto& inst : function.instructions()) {
			inst.setOperandTypes(toVector(operandStack));

			//Calculate the maximum size of the stack
			auto stackSize = inst.operandTypes().size();
			if (stackSize > function.operandStackSize()) {
				function.setOperandStackSize(stackSize);
			}

			verifyInstruction(function, functionSignature, inst, index, operandStack, branches);

			if (index == numInstructions - 1) {
				if (inst.opCode() != OpCodes::RET) {
					typeError(functionSignature, index, "Functions must end with the 'RET' instruction.");
				}
			}

			index++;
		}

		//Check that the branches are valid
		verifyBranches(function, functionSignature, branches);

		//Check that all locals has been typed
		postCheckLocalsTypes(function, functionSignature);
	}
}
