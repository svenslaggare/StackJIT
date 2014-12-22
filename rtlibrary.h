#pragma once
#include <string>

struct Function;
class Type;
class ObjectHandle;

//The runtime library
namespace Runtime {
	//Prints the given stack frame
	void printStackFrame(long* basePtr, Function* func);

	//Pushes the given func to the top of the call stack
	void pushFunc(Function* func, int instIndex);

	//Pops the top function from the call stack
	void popFunc();

	//Prints the alive objects
	void printAliveObjects(long* basePtr, Function* func, int instIndex, std::string indentation = "");

	//Marks the given object
	void markObject(ObjectHandle* handle);

	//Marks the given value
	void markValue(long value, Type* type);

	//Marks all the objects
	void markObjects(long* basePtr, Function* func, int instIndex);

	//Sweeps (deletes) none reachable objects
	void sweepObjects();

	//Tries to collect garbage
	void garbageCollect(long* basePtr, Function* func, int instIndex);

	//Creates a new array of the given size
	long newArray(Type* type, int size);

	//Creates a new struct
	long newObject(Type* type);

	//Stops the execution
	void runtimeError(std::string errorMessage);

	//Signals that an inavlid array access has been made
	void arrayOutOfBoundsError();

	//Signals that a null reference has been made
	void nullReferenceError();
}