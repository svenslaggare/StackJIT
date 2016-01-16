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

void ManagedHeap::visitObjects(std::function<void (ObjectRef)> fn) {
	auto current = mData;
	while (current < mNextAllocation) {
		if (((*(std::int32_t*)current) & -1) != -1) {
			ObjectRef objRef(current + StackJIT::OBJECT_HEADER_SIZE);
			fn(objRef);
			current += objRef.fullObjectSize();
		} else {
			//Dead object
			current += *(std::int32_t*)(current + sizeof(std::int32_t));
		}
	}
}
