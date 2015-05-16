#pragma once
#include <string>
#include <stdexcept>
#include "objects.h"

class StructHandle;
class StructMetadata;
class Type;

//Represents a raw struct reference
using RawStructRef = unsigned char*;

//Represents a raw array reference
using RawArrayRef = unsigned char*;

//Represents a field reference
template<typename T>
class FieldRef {
private:
	T* mFieldPtr;

	//Creates a new reference to the given field
	FieldRef(unsigned char* fieldPtr);
	friend class StructRef;
public:
	//Returns a pointer to the field
	T* value();
};

//Represents a struct reference
class StructRef {
private:
	StructHandle* mHandle;
	const StructMetadata& mMetadata;
public:
	//Creates a new reference to the given structure
	StructRef(StructHandle* handle, const StructMetadata& metadata);

	//Returns a reference to a field of the given type
	template<typename T>
	FieldRef<T> getField(std::string name, const Type* type);
};

//Represents an element reference
template<typename T>
class ElementRef {
private:
	T* mElementPtr;
	int mIndex;

	//Creates a new reference to the given element
	ElementRef(unsigned char* elementPtr, int index);

	template<typename U>
	friend class ArrayRef;
public:
	//Returns a pointer to the element
	T* value();

	//Returns the index for the element
	int index() const;
};

//Represents an array reference
template<typename T>
class ArrayRef {
private:
	ArrayHandle* mHandle;
	int mLength;
public:
	//Creates a new reference to the given array
	ArrayRef(ArrayHandle* handle);

	//Returns a reference to the field at the given index
	ElementRef<T> getElement(int index);

	//Returns the length of the array
	int length() const;
};

#include "objectref.hpp"