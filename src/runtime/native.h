#pragma once
#include "../type/objectref.h"

namespace stackjit {
	class VMState;

	//The part of the runtime library exposed to programs
	namespace NativeLibrary {
		//Prints the given value
		void print(int x);
		void print(float x);
		void print(bool x);
		void print(char x);

		//Prints the given value followed by a line break
		void println(int x);
		void println(float x);
		void println(bool x);
		void println(char x);
		void println(RawArrayRef rawArrayRef);

		//Returns the absolute value of the given value
		int abs(int x);

		//Checks if the two strings are equal
		bool stringEquals(RawClassRef str1, RawClassRef str2);

		//Adds the native library to the given VM state
		void add(VMState& vmState);
	}
}
