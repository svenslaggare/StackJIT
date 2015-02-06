#pragma once
#include "binder.h"
#include "jit.h"

typedef int (*EntryPointFunction)();

class VMState;
class Program;

//Represents the execution engine
class ExecutionEngine {
private:
	 VMState& mVMState;
	 JITCompiler mJIT;
public:
	//Creates a new execution engine
	ExecutionEngine(VMState& vmState);

	//Prevent it from being copied
	ExecutionEngine(const ExecutionEngine&) = delete;
	ExecutionEngine& operator=(const ExecutionEngine&) = delete;

	//Returns the entry point
	EntryPointFunction entryPoint() const; 

	//Loads the given program
	void loadProgram(Program& program);
};