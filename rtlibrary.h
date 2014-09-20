#pragma once
#include <string>

struct Function;
class Type;

//Prints the given stack frame
void rt_printStackFrame(long*, Function*);

//Creates a new array of the given size
long rt_newArray(Type* type, int size);

//Stops the execution
void rt_runtimeError(std::string);

//Signals that an inavlid array access has been made
void rt_arrayOutOfBoundsError();