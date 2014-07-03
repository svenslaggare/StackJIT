#pragma once
#include <map>
#include <string>

int vm_abs(int x);
int vm_print(int x);
int vm_println(int x);
int vm_rand();

void addStandardLibrary(std::map<std::string, long>&);