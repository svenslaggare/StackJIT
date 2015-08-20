#pragma once
#include <string>
#include <stdexcept>
#include "objects.h"

class ClassHandle;
class ClassMetadata;
class Type;

//Represents a raw class reference
using RawClassRef = unsigned char*;

//Represents a raw array reference
using RawArrayRef = unsigned char*;

//Represents a field reference
template<typename T>
class FieldRef {
private:
	T* mFieldPtr;

	//Creates a new reference to the given field
	FieldRef(unsigned char* fieldPtr);
	friend class ClassRef;
public:
	//Returns a pointer to the field
	T* value();
};

//Represents a class reference
class ClassRef {
private:
	ClassHandle* mHandle;
	const ClassMetadata& mMetadata;
public:
	//Creates a new reference to the given structure
	ClassRef(ClassHandle* handle, const ClassMetadata& metadata);

	//Returns a reference to a field of the given type
	template<typename T>
	FieldRef<T> getField(std::string name, const Type* type);
};

//Represents an array reference
template<typename T>
class ArrayRef {
private:
	T* mElementsPtr;
	int mLength;
public:
	//Creates a new reference to the given array
	ArrayRef(const RawArrayRef arrayRef);

	//Returns a pointer to the elements
	T* elementsPtr() const;

	//Returns the value of the given element
	T getElement(int index) const;

	//Returns the length of the array
	int length() const;
};

#include "objectref.hpp"