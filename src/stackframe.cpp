#include "stackframe.h"
#include "function.h"

StackFrameEntry::StackFrameEntry(RegisterValue value, const Type* type)
	: value(value), type(type) {

}

//Stack frame
StackFrame::StackFrame(RegisterValue* basePtr, const Function* function, const int instIndex)
	: mBasePtr(basePtr),
	  mFunction(function),
	  mOperandTypes(function->instructions[instIndex].operandTypes()) {
}

StackFrameEntry StackFrame::getArgument(int index) {
	RegisterValue* argsStart = mBasePtr - 1;
	return StackFrameEntry(argsStart[-index], mFunction->parameters()[index]);
}

StackFrameEntry StackFrame::getLocal(int index) {
	RegisterValue* localsStart = mBasePtr - 1 - mFunction->numParams();
	return StackFrameEntry(localsStart[-index], mFunction->getLocal(index));
}

StackFrameEntry StackFrame::getStackOperand(int index) {
	RegisterValue* stackStart = mBasePtr - 1 - mFunction->numParams() - mFunction->numLocals();
	return StackFrameEntry(stackStart[-index], mOperandTypes[mOperandTypes.size() - 1 - index]);
}

std::size_t StackFrame::operandStackSize() const {
	return mOperandTypes.size();
}