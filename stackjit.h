#pragma once
#include <string>
#include <map>

const int NUM_LOCALS = 8;
const bool ENABLE_DEBUG = true;

//Represents the state for the VM
struct VMState {
    int Locals[NUM_LOCALS] = {0};
    std::map<std::string, long> FunctionTable;
};