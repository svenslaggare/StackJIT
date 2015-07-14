#pragma once
#include <functional>
#include <deque>

class Function;
class Type;

//Represents a stack frame entry (argument, local, operand)
struct StackFrameEntry {
	long value;
	const Type* type;

	StackFrameEntry(long value, const Type* type);
};


//Represents a stack frame
class StackFrame {
private:
	long* mBasePtr;
	const Function* mFunction;
	const int mInstIndex;
	const std::deque<const Type*>& mOperandTypes;
public:
	//Creates a new stack frame
	StackFrame(long* basePtr, const Function* function, const int instIndex);

	//Returns the given function argument
	StackFrameEntry getArgument(int index);

	//Returns the given local
	StackFrameEntry getLocal(int index);

	//Returns the given operand
	StackFrameEntry getStackOperand(int index);

	//Returns the size of the operand stack at the current instruction
	std::size_t operandStackSize() const;
};