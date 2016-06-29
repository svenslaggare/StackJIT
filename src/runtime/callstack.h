#pragma once
#include <cstdlib>

namespace stackjit {
	class ManagedFunction;

	//Represents a call stack entry
	struct CallStackEntry {
		ManagedFunction* function;
		int callPoint;

		CallStackEntry(ManagedFunction* function, int callPoint);
		CallStackEntry();
	};

	//Manages the call stack
	class CallStack {
	private:
		std::size_t mSize;
		CallStackEntry* mStart;
		CallStackEntry* mTop;
	public:
		//Creates a new call stack of the given size
		CallStack(std::size_t size);
		~CallStack();

		//Pushes the given function to the stack
		void push(ManagedFunction* function, int callPoint);

		//Pops the top entry
		CallStackEntry pop();

		//Returns the size of the stack
		std::size_t size() const;

		//Returns the start of the stack
		CallStackEntry* start();
		CallStackEntry* const start() const;

		//Returns top of the stack
		CallStackEntry* top();

		//Pointer to the top variable
		CallStackEntry* const * const topPtr() const;
	};
}
