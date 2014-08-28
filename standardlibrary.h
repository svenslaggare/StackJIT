#pragma once
#include <map>
#include <string>

struct VMState;

int std_abs(int x);
int std_print(int x);
int std_println(int x);

//Adds the standard library to the given VM state
void addStandardLibrary(VMState& vmState);