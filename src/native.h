#pragma once

#include "objectref.h"

class VMState;

//Represents a string reference
class StringRef {
private:
	char* mChars;
	int mLength;

	static std::size_t sCharsFieldOffset;
public:
	//Creates a new reference for the given raw reference
	StringRef(RawClassRef stringRef);

	//Sets the value of the chars field
	static void setCharsField(RawClassRef stringRef, char* value);

	//Returns the char at the given index
	char charAt(int index);

	//Returns tte length of the string
	int length() const;

	//Initialize the string reference
	static void initialize(VMState& vmState);
};


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
	void println(RawArrayRef arrayRef);

	int abs(int x);

	bool stringEquals(RawClassRef str1, RawClassRef str2);

	//Adds the native library to the given VM state
	void add(VMState& vmState);
}