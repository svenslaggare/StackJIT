#pragma once
class VMState;

//The part of the runtime library exposed to programs
namespace NativeLibrary {
	void print(int x);
	void print(float x);

	void println(int x);
	void println(float x);
	void println(bool x);
	void println(char x);

	void printchar(char x);

	int abs(int x);

	//Adds the native library to the given VM state
	void add(VMState& vmState);
}