#pragma once
#include <map>
#include <string>

int vm_abs(int x);
int vm_print(int x);
int vm_println(int x);

//Adds the standard library to the given call table
void addStandardLibrary(std::map<std::string, long>& callTable);