#include "managedheap.h"

namespace stackjit {
	ManagedHeap::ManagedHeap(std::size_t size)
		: mData(new unsigned char[size]), mSize(size), mNextAllocation(mData) {

	}

	ManagedHeap::~ManagedHeap() {
		delete[] mData;
	}

	BytePtr ManagedHeap::data() const {
		return mData;
	}

	std::size_t ManagedHeap::size() const {
		return mSize;
	}

	BytePtr ManagedHeap::start() const {
		return mData;
	}

	BytePtr ManagedHeap::end() const {
		return mData + mSize;
	}

	bool ManagedHeap::inside(BytePtr ptr) const {
		return ptr >= start() && ptr <= end();
	}

	BytePtr ManagedHeap::allocate(std::size_t size) {
		auto nextAllocation = mNextAllocation + size;

		if (nextAllocation < end()) {
			auto allocation = mNextAllocation;
			mNextAllocation = nextAllocation;
			return allocation;
		} else {
			return nullptr;
		}
	}

	void ManagedHeap::setNextAllocation(BytePtr nextAllocation) {
		if (nextAllocation >= mData && nextAllocation < end()) {
			mNextAllocation = nextAllocation;
		} else {
			throw std::runtime_error("The pointer is outside the heap.");
		}
	}

	void ManagedHeap::visitObjects(std::function<void (ObjectRef)> fn) {
		auto current = mData;
		while (current < mNextAllocation) {
			if (*(current + sizeof(std::size_t)) != 0xFF) {
				ObjectRef objRef(current + stackjit::OBJECT_HEADER_SIZE);
				fn(objRef);
				current += objRef.fullSize();
			} else {
				//Dead object
				current += *(std::size_t*)(current);
			}
		}
	}
}
