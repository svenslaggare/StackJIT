#pragma once
#include <cstring>

//Represents a compiler for a platform
class Compiler {
public:
	//Allocates memory of the given size
	virtual void* allocateMemory(std::size_t size) = 0;

	//Makes the given memory executable
	virtual void makeExecutableMemory(void* memory, std::size_t size) = 0;
};