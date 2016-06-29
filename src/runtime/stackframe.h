#pragma once
#include <functional>
#include <vector>
#include "../stackjit.h"

namespace stackjit {
	class ManagedFunction;
	class Type;

	//Represents a stack frame entry (argument, local, operand)
	class StackFrameEntry {
	private:
		RegisterValue* mValue;
		const Type* mType;

	public:
		//Creates a new stack frame entry
		StackFrameEntry(RegisterValue* value, const Type* type);

		//Returns the value of the entry
		RegisterValue value() const;

		//Returns a pointer to the value
		RegisterValue* valuePtr() const;

		//Returns the type of the entry
		const Type* type() const;
	};

	//Represents a stack frame
	class StackFrame {
	private:
		RegisterValue* mBasePtr;
		const ManagedFunction* mFunction;
		const std::vector<const Type*>& mOperandTypes;
	public:
		//Creates a new stack frame
		StackFrame(RegisterValue* basePtr, const ManagedFunction* function, const int instIndex);

		//Returns the given function argument
		StackFrameEntry getArgument(std::int64_t index);

		//Returns the given local
		StackFrameEntry getLocal(std::int64_t index);

		//Returns the given operand
		StackFrameEntry getStackOperand(std::int64_t index);

		//Returns the size of the operand stack at the current instruction
		std::size_t operandStackSize() const;
	};
}
