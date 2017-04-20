#include "stackframe.h"
#include "../core/function.h"
#include "runtime.h"

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
		RegisterValue* localsStart = mBasePtr - 1 - mFunction->def().numParameters();
		return StackFrameEntry(localsStart - index, mFunction->getLocal(index));
	}

	StackFrameEntry StackFrame::getStackOperand(std::size_t index) {
		RegisterValue* stackStart = mBasePtr - 1 - mFunction->def().numParameters() - mFunction->numLocals();
		return StackFrameEntry(stackStart - index, mOperandTypes[mOperandTypes.size() - 1 - index]);
	}

	std::size_t StackFrame::operandStackSize() const {
		return mOperandTypes.size();
	}

	//Stack walker
	StackWalker::StackWalker(VMState& vmState)
		: mVMState(vmState) {

	}

	RegisterValue* StackWalker::findBasePtr(RegisterValue* currentBasePtr, int currentIndex, int targetIndex) {
		if (currentBasePtr == nullptr) {
			return nullptr;
		}

		if (currentIndex == targetIndex) {
			return (RegisterValue*)*currentBasePtr;
		}

		return findBasePtr((RegisterValue*)*currentBasePtr, currentIndex + 1, targetIndex);
	}

	void StackWalker::visitReference(StackFrameEntry frameEntry, VisitReferenceFn fn) {
		if (frameEntry.type()->isReference()) {
			auto objPtr = (BytePtr)frameEntry.value();

			//Don't visit nulls
			if (objPtr == nullptr) {
				return;
			}

			fn(frameEntry);
		}
	}

	void StackWalker::visitReferencesInFrame(RegisterValue* basePtr,
											 ManagedFunction* func,
											 int instIndex,
											 VisitReferenceFn fn) {
		StackFrame stackFrame(basePtr, func, instIndex);
		auto numArgs = func->def().numParameters();
		auto numLocals = func->numLocals();
		auto stackSize = stackFrame.operandStackSize();

		for (std::size_t i = 0; i < numArgs; i++) {
			auto arg = stackFrame.getArgument(i);
			visitReference(arg, fn);
		}

		for (std::size_t i = 0; i < numLocals; i++) {
			auto local = stackFrame.getLocal(i);
			visitReference(local, fn);
		}

		for (std::size_t i = 0; i < stackSize; i++) {
			auto operand = stackFrame.getStackOperand(i);
			visitReference(operand, fn);
		}
	}

	void StackWalker::visitReferences(RegisterValue* basePtr,
									  ManagedFunction* func,
									  int instIndex,
									  VisitReferenceFn fn,
									  VisitFrameFn frameFn) {
		if (frameFn) {
			frameFn(basePtr, func, instIndex);
		}

		//Visit the calling stack frame
		visitReferencesInFrame(basePtr, func, instIndex, fn);

		//Then all other stack frames
		auto topEntryPtr = mVMState.engine().callStack().top();
		int topFuncIndex = 0;
		while (topEntryPtr > mVMState.engine().callStack().start()) {
			auto callEntry = *topEntryPtr;
			auto topFunc = callEntry.function;
			auto callPoint = callEntry.callPoint;
			auto callBasePtr = findBasePtr(basePtr, 0, topFuncIndex);

			if (frameFn) {
				frameFn(callBasePtr, topFunc, callPoint);
			}

			visitReferencesInFrame(callBasePtr, topFunc, callPoint, fn);

			topEntryPtr--;
			topFuncIndex++;
		}
	}
}
