#include "stackframe.h"
#include "function.h"

StackFrameEntry::StackFrameEntry(long value, const Type* type)
	: value(value), type(type) {

}

//Stack frame
StackFrame::StackFrame(long* basePtr, const Function* function, const int instIndex)
	: mBasePtr(basePtr),
	  mFunction(function),
	  mOperandTypes(function->instructions[instIndex].operandTypes()) {
}

StackFrameEntry StackFrame::getArgument(int index) {
	long* argsStart = mBasePtr - 1;
	return StackFrameEntry(argsStart[-index], mFunction->parameters()[index]);
}

StackFrameEntry StackFrame::getLocal(int index) {
	long* localsStart = mBasePtr - 1 - mFunction->numParams();
	return StackFrameEntry(localsStart[-index], mFunction->getLocal(index));
}

StackFrameEntry StackFrame::getStackOperand(int index) {
	long* stackStart = mBasePtr - 1 - mFunction->numParams() - mFunction->numLocals();
	return StackFrameEntry(stackStart[-index], mOperandTypes[mOperandTypes.size() - 1 - index]);
}

std::size_t StackFrame::operandStackSize() const {
	return mOperandTypes.size();
}