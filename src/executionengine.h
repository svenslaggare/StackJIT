#pragma once
#include "binder.h"

typedef int (*EntryPointFunction)();

class VMState;

//Represents the execution engine
class ExecutionEngine {
private:
	 VMState& vmState
public:
	//Creates a new execution engine
	ExecutionEngine(VMState& vmState);

	//Returns the entry point
	EntryPointFunction entryPoint() const; 

	//Loads the given program
	void loadProgram(Program& program);
};