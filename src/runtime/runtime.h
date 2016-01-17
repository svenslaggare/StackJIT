#pragma once
#include <string>
#include "../stackjit.h"
#include "../type/type.h"
#include "../vmstate.h"

class ManagedFunction;
class FunctionDefinition;
class Type;
class ClassType;
class ArrayType;

//Defines the runtime
namespace Runtime {
	//The global VM state
	extern VMState vmState;

	//Prints the given stack frame
	void printStackFrame(RegisterValue* basePtr, ManagedFunction* func);

	//Functions not intended to be called from outside the runtime.
	namespace Internal {
		//Prints the alive objects
		void printAliveObjects(RegisterValue* basePtr, ManagedFunction* func, int instIndex, std::string indentation = "");

		//Finds the base ptr for the function at the given index
		RegisterValue* findBasePtr(RegisterValue* currentBasePtr, int currentIndex, int targetIndex);
	};

	//Compiles the given function
	void compileFunction(ManagedFunction* callee, int callOffset, int checkStart, int checkEnd, FunctionDefinition* funcToCall);

	//Tries to collect garbage
	void garbageCollect(RegisterValue* basePtr, ManagedFunction* func, int instIndex);

	//Creates a new array of the given type and length
	unsigned char* newArray(const ArrayType* arrayType, int length);

	//Creates a new class of the given type
	unsigned char* newObject(const ClassType* classType);

	//Creates a new string of the given length
	unsigned char* newString(const char* string, int length);

	//Stops the execution
	void runtimeError(std::string errorMessage);

	//Signals that an invalid array creation has been made
	void invalidArrayCreation();

	//Signals that an invalid array access has been made
	void arrayOutOfBoundsError();

	//Signals that a null reference has been made
	void nullReferenceError();

	//Signals that the call stack has run out of memory
	void stackOverflow();
}