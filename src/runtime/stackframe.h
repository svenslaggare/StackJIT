#pragma once
#include <functional>
#include <vector>
#include "../stackjit.h"

namespace stackjit {
	class ManagedFunction;
	class Type;
	class VMState;

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
		StackFrameEntry getArgument(std::size_t index);

		//Returns the given local
		StackFrameEntry getLocal(std::size_t index);

		//Returns the given operand
		StackFrameEntry getStackOperand(std::size_t index);

		//Returns the size of the operand stack at the current instruction
		std::size_t operandStackSize() const;
	};

	//Represents a stack walker
	class StackWalker {
	public:
		using VisitReferenceFn = std::function<void (StackFrameEntry)>;
		using VisitFrameFn = std::function<void (RegisterValue* basePtr, ManagedFunction* func, int instIndex)>;
	private:
		VMState& mVMState;

		//Finds the base ptr for the function at the given index
		RegisterValue* findBasePtr(RegisterValue* currentBasePtr, int currentIndex, int targetIndex);

		//Visits the given frame entry if reference
		void visitReference(StackFrameEntry frameEntry, VisitReferenceFn fn);

		//Visits all the references in the given stack frame
		void visitReferencesInFrame(RegisterValue* basePtr, ManagedFunction* func, int instIndex, VisitReferenceFn fn);
	public:
		//Creates a new stack walker
		StackWalker(VMState& vmState);

		//Visits all the references in all stack frames, starting at the given frame
		void visitReferences(RegisterValue* basePtr,
							 ManagedFunction* func,
							 int instIndex,
							 VisitReferenceFn fn,
							 VisitFrameFn frameFn = {});
	};
}
