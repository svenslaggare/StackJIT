#pragma once
#include <map>
#include <string>

class VMState;

namespace StandardLibrary {
	int abs(int x);

	//Prints the given integer
	void print(int x);

	//Prints the given integer followed by a line break
	void println(int x);

	//Prints the given float followed by a line break
	void println(float x);

	//Prints the given char
	void printchar(int x);

	//Adds the standard library to the given VM state
	void add(VMState& vmState);
}