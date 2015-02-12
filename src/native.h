#pragma once
class VMState;

//Represents the native library
namespace NativeLibrary {
	//Prints the given integer
	void print(int x);

	//Prints the given integer followed by a line break
	void println(int x);

	//Prints the given float followed by a line break
	void println(float x);

	//Prints the given char
	void printchar(char x);

	//Computes the absolute value
	int abs(int x);

	//Adds the native library to the given VM state
	void add(VMState& vmState);
}