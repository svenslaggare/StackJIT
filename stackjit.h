#pragma once
#include <string>
#include <map>

//The number of locals
const int NUM_LOCALS = 8;

//Indicates if debugging is enabled
const bool ENABLE_DEBUG = true;

//Represents the state for the VM
struct VMState {
    int Locals[NUM_LOCALS] = {0};
    std::map<std::string, long> FunctionTable;
};