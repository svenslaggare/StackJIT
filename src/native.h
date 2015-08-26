#pragma once
#include "objectref.h"

class VMState;
class Type;
class ClassType;
class ArrayType;

//Represents a string reference
class StringRef {
private:
	char* mChars;
	int mLength;

	static std::size_t sCharsFieldOffset;
	static const ArrayType* sCharArrayType;
	static const ClassType* sStringType;
public:
	//Creates a new reference for the given raw reference
	StringRef(RawClassRef stringRef);

	//Returns the char at the given index
	inline char charAt(int index);

	//Returns tte length of the string
	inline int length() const;

	//Returns the char array type
	static const ArrayType* charArrayType();

	//Returns the string type
	static const ClassType* stringType();

	//Sets the value of the chars field
	static void setCharsField(RawClassRef stringRef, char* value);

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
	void println(RawArrayRef rawArrayRef);

	int abs(int x);

	bool stringEquals(RawClassRef str1, RawClassRef str2);

	//Adds the native library to the given VM state
	void add(VMState& vmState);
}