#include "stackframe.h"
#include "function.h"

StackFrameEntry::StackFrameEntry(RegisterValue value, const Type* type)
	: value(value), type(type) {

}

//Stack frame
StackFrame::StackFrame(RegisterValue* basePtr, const ManagedFunction* function, const int instIndex)
	: mBasePtr(basePtr),
	  mFunction(function),
	  mOperandTypes(function->instructions[instIndex].operandTypes()) {
}

StackFrameEntry StackFrame::getArgument(std::int64_t index) {
	RegisterValue* argsStart = mBasePtr - 1;
	return StackFrameEntry(argsStart[-index], mFunction->def().parameters()[index]);
}

StackFrameEntry StackFrame::getLocal(std::int64_t index) {
	RegisterValue* localsStart = mBasePtr - 1 - mFunction->def().numParams();
	return StackFrameEntry(localsStart[-index], mFunction->getLocal(index));
}

StackFrameEntry StackFrame::getStackOperand(std::int64_t index) {
	RegisterValue* stackStart = mBasePtr - 1 - mFunction->def().numParams() - mFunction->numLocals();
	return StackFrameEntry(stackStart[-index], mOperandTypes[mOperandTypes.size() - 1 - index]);
}

std::size_t StackFrame::operandStackSize() const {
	return mOperandTypes.size();
}