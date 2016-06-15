#include "callstack.h"
#include <stdexcept>

namespace stackjit {
	CallStackEntry::CallStackEntry(ManagedFunction* function, int callPoint)
		: function(function), callPoint(callPoint) {

	}

	CallStackEntry::CallStackEntry()
		: function(nullptr), callPoint(0) {

	}

	CallStack::CallStack(std::size_t size)
		: mSize(size), mStart(new CallStackEntry[size]), mTop(mStart) {

	}

	CallStack::~CallStack() {
		delete[] mStart;
	}

	void CallStack::push(ManagedFunction* function, int callPoint) {
		if (mTop + 1 < mStart + mSize) {
			mTop++;
			*mTop = CallStackEntry(function, callPoint);
		} else {
			throw std::runtime_error("Stack overflow.");
		}
	}

	CallStackEntry CallStack::pop() {
		if (mTop == mStart) {
			throw std::runtime_error("Stack underflow.");
		}

		auto top = *mTop;
		mTop--;
		return top;
	}

	std::size_t CallStack::size() const {
		return mSize;
	}

	CallStackEntry* CallStack::start() {
		return mStart;
	}

	CallStackEntry* const CallStack::start() const {
		return mStart;
	}

	CallStackEntry* CallStack::top() {
		return mTop;
	}

	CallStackEntry* const * const CallStack::topPtr() const {
		return &mTop;
	}
}
