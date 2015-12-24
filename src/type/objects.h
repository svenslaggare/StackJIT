#pragma once
#include <unordered_map>
#include <string>

class Type;

//Represents an object handle
class ObjectHandle {
private:
	unsigned char* mHandle;
	std::size_t mSize;
	const Type* mType;
	bool mIsMarked = false;
public:	
	//Creates a new object handle
	ObjectHandle(unsigned char* handle, std::size_t size, const Type* type);
	virtual ~ObjectHandle();

	//Returns the size of the handled object
	std::size_t size() const;

	//Returns the type of the handled object
	const Type* type() const;

	//Returns the handle.
	const unsigned char* handle() const;

	//Indicates if the object is marked
	bool isMarked() const;

	//Marks the current object
	void mark();

	//Unmarks the current object
	void unmark();
};

//Represents an array handle
class ArrayHandle : public ObjectHandle {
private:
	int mLength;
public:
	//Creates a new array handle
	ArrayHandle(unsigned char* handle, std::size_t size, const Type* type, int length);
	ArrayHandle();

	//Returns the length of the handled array
	int length() const;
};

//Represents a class handle
class ClassHandle : public ObjectHandle  {
public:
	//Creates a new class handle
	ClassHandle(unsigned char* handle, std::size_t objSize, const Type* type);
	ClassHandle();
};