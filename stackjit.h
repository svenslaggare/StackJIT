#pragma once
#include <string>
#include <map>

struct Function;

//Indicates if debugging is enabled
const bool ENABLE_DEBUG = true;

//Represents a function definition
struct FunctionDefinition {
	char NumArgs;
	long EntryPoint;

	FunctionDefinition(char numArgs, long entryPoint)
		: NumArgs(numArgs), EntryPoint(entryPoint)
	{

	}

	FunctionDefinition() {}
};

//Represents the state for the VM
struct VMState {
    std::map<std::string, FunctionDefinition> FunctionTable;
};

//Prints the given stack frame
void rt_printStackFrame(long*, Function*);