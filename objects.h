#pragma once
#include <unordered_map>
#include <string>

class Type;

//Represents an array handle
class ArrayHandle {
private:
	unsigned char* handle;
public:
	const int size;
	int* const elements;

	ArrayHandle(int size, int* elements);
	ArrayHandle();
	
	//Deletes the underlying handle
	void deleteHandle();

	//Returns the handle
	const unsigned char* getHandle() const;
};

//Represents a struct handle
class StructHandle {
private:
	unsigned char* handle;
	const std::unordered_map<std::string, Type*> fields;
public:
	StructHandle(std::unordered_map<std::string, Type*> fields);

	//Returns the type for the given field
	Type* getType(std::string fieldName) const;

	//Deletes the underlying handle
	void deleteHandle();

	//Returns the handle
	const unsigned char* getHandle() const;
};