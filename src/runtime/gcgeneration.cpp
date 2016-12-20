#include "gcgeneration.h"

namespace stackjit {
	CollectorGeneration::CollectorGeneration(std::size_t size,
											 std::size_t allocatedBeforeCollection,
											 int survivedCollectionsBeforePromote,
											 std::size_t cardSize)
			: mHeap(size),
			  mAllocatedBeforeCollection(allocatedBeforeCollection),
			  mSurvivedCollectionsBeforePromote(survivedCollectionsBeforePromote),
			  mCardSize(cardSize),
			  mNumCards(mCardSize > 0 ? (size / mCardSize) : 0),
			  mCardTable(mCardSize > 0 ? (new unsigned char[mNumCards]{ 0 }) : nullptr) {

	}

	CollectorGeneration::~CollectorGeneration() {
		delete[] mCardTable;
	}

	ManagedHeap& CollectorGeneration::heap() {
		return mHeap;
	}

	const ManagedHeap& CollectorGeneration::heap() const {
		return mHeap;
	}

	std::size_t CollectorGeneration::numCards() const {
		return mNumCards;
	}

	BytePtr CollectorGeneration::cardTable() const {
		return mCardTable;
	}

	std::size_t CollectorGeneration::getCardNumber(BytePtr ptr) const {
		if (mCardSize == 0) {
			return 0;
		}

		return (std::size_t)(ptr - mHeap.start()) / mCardSize;
	}

	bool CollectorGeneration::needsToCollect() const {
		return mNumAllocated >= mAllocatedBeforeCollection;
	}

	bool CollectorGeneration::needsToPromote(int survivalCount) const {
		if (mSurvivedCollectionsBeforePromote == -1) {
			return false;
		}

		return survivalCount >= mSurvivedCollectionsBeforePromote;
	}

	BytePtr CollectorGeneration::allocate(std::size_t size) {
		auto objPtr = mHeap.allocate(size);
		if (objPtr != nullptr) {
			mNumAllocated++;
		} else {
			throw std::runtime_error("Could not allocate object.");
		}

		return objPtr;
	}

	void CollectorGeneration::collected() {
		mNumAllocated = 0;

		//Reset the card table
		for (std::size_t i = 0; i < mNumCards; i++) {
			mCardTable[i] = 0;
		}
	}
}