#pragma once
#include "binder.h"
#include "jit.h"
#include <deque>

typedef int (*EntryPointFunction)();

class VMState;
class Assembly;
class Function;

using CallStackEntry = std::pair<Function*, int>;

//Represents the execution engine
class ExecutionEngine {
private:
	VMState& mVMState;
	JITCompiler mJIT;
	std::deque<CallStackEntry> mCallStack;
public:
	//Creates a new execution engine
	ExecutionEngine(VMState& vmState);

	//Prevent it from being copied
	ExecutionEngine(const ExecutionEngine&) = delete;
	ExecutionEngine& operator=(const ExecutionEngine&) = delete;

	//Returns the entry point
	EntryPointFunction entryPoint() const; 

	//Loads the given assembly
	void loadAssembly(Assembly& assembly);

	//Begins the execution of the program
	void beginExecution();

	//Returns the call stack
    const std::deque<CallStackEntry>& callStack() const;

    //Pops the top function
    CallStackEntry popFunc();

    //Pushes the given function to the top of the stack
    void pushFunc(Function* func, int instIndex);
};