#pragma once
#include "../type/objectref.h"
#include <vector>

namespace stackjit {
	//Represents a managed heap.
	class ManagedHeap {
	private:
		BytePtr const mData;
		const std::size_t mSize;
		BytePtr mNextAllocation;
	public:
		//Creates a heap of the given size
		ManagedHeap(std::size_t size);
		~ManagedHeap();

		//Returns a pointer to the data in the heap.
		BytePtr data() const;

		//Returns the size of the heap
		std::size_t size() const;

		//Returns the start of the heap
		BytePtr start() const;

		//Returns the end of the heap (address of last element)
		BytePtr end() const;

		//Indicates if the given pointer is inside the heap
		bool inside(BytePtr ptr) const;

		//Allocates a memory block of the given size. Returns nullptr if not allocated
		BytePtr allocate(std::size_t size);

		//Sets where the next allocation should occur.
		void setNextAllocation(BytePtr nextAllocation);

		//Visits all the alive objects in the heap.
		void visitObjects(std::function<void (ObjectRef)> fn);
	};
}
