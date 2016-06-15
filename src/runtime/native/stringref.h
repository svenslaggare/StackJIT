#pragma once
#include "../../type/objectref.h"

namespace stackjit {
	class Type;
	class ClassType;
	class ArrayType;
	class VMState;

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
		inline char charAt(int index) {
			return mChars[index];
		}

		//Returns tte length of the string
		inline int length() const {
			return mLength;
		}

		//Returns the char array type
		static const ArrayType* charArrayType();

		//Returns the string type
		static const ClassType* stringType();

		//Sets the value of the chars field
		static void setCharsField(RawClassRef stringRef, char* value);

		//Initialize the class
		static void initialize(VMState& vmState);
	};
}
