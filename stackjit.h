#pragma once
#include <string>
#include <map>
#include <vector>

struct Function;

//Indicates if debugging is enabled
const bool ENABLE_DEBUG = true;

//Represents a function definition
struct FunctionDefinition {
	char NumArgs;
	long EntryPoint;
	int FunctionSize;

	FunctionDefinition(char numArgs, long entryPoint, int funcSize)
		: NumArgs(numArgs), EntryPoint(entryPoint), FunctionSize(funcSize)
	{

	}

	FunctionDefinition() {}
};

//Represents the state for the VM
struct VMState {
    std::map<std::string, FunctionDefinition> FunctionTable;
    std::vector<unsigned char*> Objects;
};

//Prints the given stack frame
void rt_printStackFrame(long*, Function*);

//Creates a new array of the given size
long rt_newArray(int);

//Stops the execution
void rt_runtimeError(std::string);

//Signals that an inavlid array access has been made
void rt_arrayOutOfBoundsError();