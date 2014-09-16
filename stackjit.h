#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

struct Function;
enum Types : unsigned char;
class ArrayHandle;
class Type;

//Indicates if debugging is enabled
const bool ENABLE_DEBUG = true;

//Prints type checking if debug is enabled
const bool PRINT_TYPE_CHECKING = false;

//Prints the info about the stack frame if debug is enabled
const bool PRINT_STACK_FRAME = false;

//Indicates if the generated code is outputed as a file
const bool OUTPUT_GENERATED_CODE = false;

//Represents a function definition
struct FunctionDefinition {
	std::vector<Type*> Arguments;
	Type* ReturnType;

	long EntryPoint;
	int FunctionSize;

	bool IsManaged; //Indicates if the function is implemented in managed code

	//Creates a new managed function definition
	FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint, int funcSize)
		: Arguments(arguments), ReturnType(returnType), EntryPoint(entryPoint), FunctionSize(funcSize), IsManaged(true)
	{

	}

	//Creates a new external function definition
	FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint)
		: Arguments(arguments), ReturnType(returnType), EntryPoint(entryPoint), IsManaged(false)
	{

	}

	FunctionDefinition() {}

	//Sets the function body (for managed functions)
	void SetFunctionBody(long entryPoint, int functionSize) {
		if (IsManaged) {
			EntryPoint = entryPoint;
			FunctionSize = functionSize;
		}
	}
};

//Represents the state of the VM
class VMState {
private:
	std::unordered_map<std::string, Type*> types;
public:
	~VMState();

    std::map<std::string, FunctionDefinition> FunctionTable;
    std::vector<ArrayHandle> Objects;

    //Returns the given type
    Type* getType(std::string name);
};

//Prints the given stack frame
void rt_printStackFrame(long*, Function*);

//Creates a new array of the given size
long rt_newArray(int);

//Stops the execution
void rt_runtimeError(std::string);

//Signals that an inavlid array access has been made
void rt_arrayOutOfBoundsError();