#pragma once
#include "../type/objectref.h"
#include <vector>

//Represents a managed heap.
class ManagedHeap {
private:
	unsigned char* const mData;
	const std::size_t mSize;

	unsigned char* mNextAllocation;
public:
	//Creates a heap of the given size
	ManagedHeap(std::size_t size);
	~ManagedHeap();

	//Returns a pointer to the data in the heap.
	unsigned char* data() const;

	//Allocates a memory block of the given size. Returns nullptr if not allocated
	unsigned char* allocate(std::size_t size);

	//Visits all the objects in the
	void visitObjects(std::function<void (ObjectRef)> fn);
};