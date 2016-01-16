#include "managedheap.h"

ManagedHeap::ManagedHeap(std::size_t size)
	: mHeap(new unsigned char[size]), mSize(size), mNextAllocation(mHeap) {

}

ManagedHeap::~ManagedHeap() {
	delete[] mHeap;
}

unsigned char* ManagedHeap::allocate(std::size_t size) {
	auto nextAllocation = mNextAllocation + size;

	if (nextAllocation < mHeap + mSize) {
		auto allocation = mNextAllocation;
		mNextAllocation = nextAllocation;
		return allocation;
	} else {
		return nullptr;
	}
}
