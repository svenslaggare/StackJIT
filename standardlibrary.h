#pragma once
#include <map>
#include <string>

class VMState;

int std_abs(int x);
void std_print(int x);
void std_println(int x);

//Adds the standard library to the given VM state
void addStandardLibrary(VMState& vmState);