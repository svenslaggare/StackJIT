#pragma once
#include <string>
#include <map>
#include <vector>

struct Function;
enum Types : unsigned char;

//Indicates if debugging is enabled
const bool ENABLE_DEBUG = true;

//Prints type checking if debug is enabled
const bool PRINT_TYPE_CHECKING = false;

//Indicates if the generated code is outputed as a file
const bool OUTPUT_GENERATED_CODE = false;

//Represents a function definition
struct FunctionDefinition {
	std::vector<Types> Arguments;
	Types ReturnType;

	long EntryPoint;
	int FunctionSize;

	FunctionDefinition(std::vector<Types> arguments, Types returnType, long entryPoint, int funcSize)
		: Arguments(arguments), ReturnType(returnType), EntryPoint(entryPoint), FunctionSize(funcSize)
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