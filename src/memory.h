#pragma once
#include <cstring>

//Represents a memory manager
class MemoryManager {
public:
	//Allocates memory of the given size. The memory allocated by this function is handled automatic.
	virtual void* allocateMemory(std::size_t size) = 0;

	//Makes all the allocated memory executable
	virtual void makeMemoryExecutable() = 0;
};