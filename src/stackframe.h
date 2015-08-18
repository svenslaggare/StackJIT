#pragma once
#include <functional>
#include <deque>
#include "stackjit.h"

class Function;
class Type;

//Represents a stack frame entry (argument, local, operand)
struct StackFrameEntry {
	RegisterValue value;
	const Type* type;

	StackFrameEntry(RegisterValue value, const Type* type);
};

//Represents a stack frame
class StackFrame {
private:
	RegisterValue* mBasePtr;
	const Function* mFunction;
	const std::deque<const Type*>& mOperandTypes;
public:
	//Creates a new stack frame
	StackFrame(RegisterValue* basePtr, const Function* function, const int instIndex);

	//Returns the given function argument
	StackFrameEntry getArgument(int index);

	//Returns the given local
	StackFrameEntry getLocal(int index);

	//Returns the given operand
	StackFrameEntry getStackOperand(int index);

	//Returns the size of the operand stack at the current instruction
	std::size_t operandStackSize() const;
};