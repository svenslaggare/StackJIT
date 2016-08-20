#include "stackframe.h"
#include "../core/function.h"

namespace stackjit {
	//Stack frame entry
	StackFrameEntry::StackFrameEntry(RegisterValue* value, const Type* type)
		: mValue(value), mType(type) {

	}

	RegisterValue StackFrameEntry::value() const {
		return *mValue;
	}

	RegisterValue* StackFrameEntry::valuePtr() const {
		return mValue;
	}

	const Type* StackFrameEntry::type() const {
		return mType;
	}

	//Stack frame
	StackFrame::StackFrame(RegisterValue* basePtr, const ManagedFunction* function, const int instIndex)
		: mBasePtr(basePtr),
		  mFunction(function),
		  mOperandTypes(function->instructions()[instIndex].operandTypes()) {
	}

	StackFrameEntry StackFrame::getArgument(std::size_t index) {
		RegisterValue* argsStart = mBasePtr - 1;
		return StackFrameEntry(argsStart - index, mFunction->def().parameters()[index]);
	}

	StackFrameEntry StackFrame::getLocal(std::size_t index) {
		RegisterValue* localsStart = mBasePtr - 1 - mFunction->def().numParams();
		return StackFrameEntry(localsStart - index, mFunction->getLocal(index));
	}

	StackFrameEntry StackFrame::getStackOperand(std::size_t index) {
		RegisterValue* stackStart = mBasePtr - 1 - mFunction->def().numParams() - mFunction->numLocals();
		return StackFrameEntry(stackStart - index, mOperandTypes[mOperandTypes.size() - 1 - index]);
	}

	std::size_t StackFrame::operandStackSize() const {
		return mOperandTypes.size();
	}
}
