#pragma once
#include <unordered_map>
//#include "typechecker.h"
#include <string>

enum Types : unsigned char;

//Represents an array handle
class ArrayHandle {
private:
	unsigned char* handle;
public:
	const int Size;
	int* Elements;

	ArrayHandle(int size, int* elements);
	ArrayHandle();
	
	//Deletes the underlying handle
	void deleteHandle();

	//Returns the handle
	const unsigned char* getHandle();
};

//Represents a struct handle
class StructHandle {
private:
	unsigned char* handle;
	const std::unordered_map<std::string, Types> fields;
public:
	StructHandle(std::unordered_map<std::string, Types> fields);

	//Returns the type for the given field
	Types getType(std::string field) const;

	//Deletes the underlying handle
	void deleteHandle();

	//Returns the handle
	const unsigned char* getHandle();
};