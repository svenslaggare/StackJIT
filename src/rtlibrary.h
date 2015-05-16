#pragma once
#include <string>

struct Function;
class Type;
class ObjectHandle;

//The runtime library
namespace Runtime {
	//Pushes the given func to the top of the call stack
	void pushFunc(Function* func, int instIndex);

	//Pops the top function from the call stack
	void popFunc();

	//Prints the given stack frame
	void printStackFrame(long* basePtr, Function* func);

	//Internal functions
	namespace Internal {
		//Prints the alive objects
		void printAliveObjects(long* basePtr, Function* func, int instIndex, std::string indentation = "");

		//Marks all the objects
		void markObjects(long* basePtr, Function* func, int instIndex);
	};

	//Tries to collect garbage
	void garbageCollect(long* basePtr, Function* func, int instIndex);

	//Creates a new array of the given type and length
	long newArray(Type* elementType, int length);

	//Creates a new struct of the given type
	long newObject(Type* type);

	//Creates a new string of the given length
	long newString(const char* string, int length);

	//Stops the execution
	void runtimeError(std::string errorMessage);

	//Signals that an invalid array creation has been made
	void invalidArrayCreation();

	//Signals that an invalid array access has been made
	void arrayOutOfBoundsError();

	//Signals that a null reference has been made
	void nullReferenceError();
}