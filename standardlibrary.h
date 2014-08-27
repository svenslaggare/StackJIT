#pragma once
#include <map>
#include <string>

int std_abs(int x);
int std_print(int x);
int std_println(int x);

//Adds the standard library to the given call table
void addStandardLibrary(std::map<std::string, long>& callTable);