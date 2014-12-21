#pragma once
#include <string>

struct Function;
class Type;

//Prints the given stack frame
void rt_printStackFrame(long*, Function*);

//Pushes the given func to the top of the call stack
void rt_pushFunc(Function*, int);

//Pops the top function from the call stack
void rt_popFunc();

//Tries to collect garbage
void rt_garbageCollect(long*, Function*, int);

//Creates a new array of the given size
long rt_newArray(Type* type, int size);

//Creates a new struct
long rt_newObject(Type* type);

//Stops the execution
void rt_runtimeError(std::string);

//Signals that an inavlid array access has been made
void rt_arrayOutOfBoundsError();

//Signals that a null reference has been made
void rt_nullReferenceError();