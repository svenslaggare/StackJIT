#pragma once
#include <unordered_map>
#include <string>

class Type;

//Represents an object handle
class ObjectHandle {
private:
	unsigned char* handle;
	std::size_t objSize;
	Type* type;
	bool mIsMarked = false;
public:	
	ObjectHandle(unsigned char* handle, std::size_t objSize, Type* type);

	//Deletes the underlying handle
	void deleteHandle();

	//Returns the size of the handled object
	std::size_t getSize() const;

	//Returns the type of the handled object
	const Type* const getType() const;

	//Returns the handle
	const unsigned char* getHandle() const;

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
	int length;
public:
	ArrayHandle(unsigned char* handle, std::size_t objSize, Type* type, int length);
	ArrayHandle();

	//Returns the length of the handled array
	int getLength() const;
};

//Represents a struct handle
class StructHandle : public ObjectHandle  {
public:
	StructHandle(unsigned char* handle, std::size_t objSize, Type* type);
	StructHandle();
};