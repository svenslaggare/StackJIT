#pragma once
#include <stack>
#include <string>
#include "../core/instruction.h"

namespace stackjit {
	class ManagedFunction;
	class VMState;
	class Type;

	using InstructionTypes = std::stack<const Type*>;

	//Represents a branch check
	struct BranchCheck {
		const std::size_t source;
		const std::size_t target;
		const InstructionTypes branchTypes;

		BranchCheck(std::size_t source, std::size_t target, InstructionTypes branchTypes)
			: source(source), target(target), branchTypes(branchTypes) {

		}
	};

	//Verifies the semantics of functions
	class Verifier {
	private:
		VMState& mVMState;

		static const std::string sIntTypeName;
		static const std::string sFloatTypeName;
		static const std::string sBoolTypeName;
		static const std::string sCharTypeName;
		static const std::string sVoidTypeName;

		//Getters for common types
		const Type* mIntType = nullptr;
		const Type* mFloatType = nullptr;
		const Type* mBoolType = nullptr;
		const Type* mCharType = nullptr;
		const Type* mVoidType = nullptr;
		const Type* mNullType = nullptr;
		const Type* mStringType = nullptr;
		const Type* getOrSetType(const std::string& name, const Type*& typeField);

		const Type* intType();
		const Type* floatType();
		const Type* boolType();
		const Type* charType();
		const Type* voidType();
		const Type* nullType();
		const Type* stringType();

		//Verifies the given instruction
		void verifyInstruction(ManagedFunction& function,
							   std::string functionSignature,
							   Instruction& instruction,
							   std::size_t index,
							   InstructionTypes& operandStack,
							   std::vector<BranchCheck>& branches);
	public:
		//Creates a new verifier using the given VM state
		Verifier(VMState& vmState);

		//Verifies the given function
		void verifyFunction(ManagedFunction& function);
	};
}
