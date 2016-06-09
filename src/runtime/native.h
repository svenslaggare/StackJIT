#pragma once
#include "../type/objectref.h"

class VMState;

//The part of the runtime library exposed to programs
namespace NativeLibrary {
	void print(int x);
	void print(float x);
	void print(bool x);
	void print(char x);

	void println(int x);
	void println(float x);
	void println(bool x);
	void println(char x);
	void println(RawArrayRef rawArrayRef);

	int abs(int x);

	bool stringEquals(RawClassRef str1, RawClassRef str2);

	//Adds the native library to the given VM state
	void add(VMState& vmState);
}