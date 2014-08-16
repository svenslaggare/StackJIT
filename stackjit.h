#pragma once
#include <string>
#include <map>

//Indicates if debugging is enabled
const bool ENABLE_DEBUG = true;

//Represents the state for the VM
struct VMState {
    std::map<std::string, long> FunctionTable;
};

//Prints the given stack frame
void rt_printStackFrame(long*, int, int);