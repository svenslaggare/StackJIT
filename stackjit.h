#pragma once
#include <string>
#include <map>

const int NUM_LOCALS = 8;

struct VMState {
    int Locals[NUM_LOCALS] = {0};
    std::map<std::string, long> CallTable;
};