#include "managedheap.h"

ManagedHeap::ManagedHeap(std::size_t size)
	: mData(new unsigned char[size]), mSize(size), mNextAllocation(mData) {

}

ManagedHeap::~ManagedHeap() {
	delete[] mData;
}

unsigned char* ManagedHeap::data() const {
	return mData;
}

unsigned char* ManagedHeap::allocate(std::size_t size) {
	auto nextAllocation = mNextAllocation + size;

	if (nextAllocation < mData + mSize) {
		auto allocation = mNextAllocation;
		mNextAllocation = nextAllocation;
		return allocation;
	} else {
		return nullptr;
	}
}

void ManagedHeap::setNextAllocation(unsigned char* nextAllocation) {
	if (nextAllocation >= mData && nextAllocation < mData + mSize) {
		mNextAllocation = nextAllocation;
	} else {
		throw std::runtime_error("The pointer is outside the heap.");
	}
}

void ManagedHeap::visitObjects(std::function<void (ObjectRef)> fn) {
	auto current = mData;
	while (current < mNextAllocation) {
		if (*(current + sizeof(std::size_t)) != 0xFF) {
			ObjectRef objRef(current + StackJIT::OBJECT_HEADER_SIZE);
			fn(objRef);
			current += objRef.fullSize();
		} else {
			//Dead object
			current += *(std::size_t*)(current);
		}
	}
}