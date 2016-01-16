#pragma once
#include <vector>

//Represents a managed heap.
class ManagedHeap {
private:
	unsigned char* const mHeap;
	const std::size_t mSize;

	unsigned char* mNextAllocation;
public:
	//Creates a heap of the given size
	ManagedHeap(std::size_t size);

	~ManagedHeap();

	//Allocates a memory block of the given size. Returns nullptr if not allocated
	unsigned char* allocate(std::size_t size);
};