#pragma once
#include "managedheap.h"

namespace stackjit {
	//Represents a generation for the garbage collector
	class CollectorGeneration {
	private:
		ManagedHeap mHeap;

		std::size_t mNumAllocated = 0;
		std::size_t mAllocatedBeforeCollection = 0;
		int mSurvivedCollectionsBeforePromote = 0;

		std::size_t mCardSize;
		std::size_t mNumCards;
		BytePtr mCardTable;
	public:
		//Creates a new generation
		CollectorGeneration(std::size_t size,
							std::size_t allocatedBeforeCollection,
							int survivedCollectionsBeforePromote = -1,
							std::size_t cardSize = 0);
		~CollectorGeneration();

		//Prevent the generation from being copied
		CollectorGeneration(const CollectorGeneration&) = delete;
		CollectorGeneration& operator=(const CollectorGeneration&) = delete;

		//Returns the heap
		ManagedHeap& heap();
		const ManagedHeap& heap() const;

		//Returns the number of cards
		std::size_t numCards() const;

		//Returns the size of a card
		std::size_t cardSize() const;

		//Returns the card table
		BytePtr cardTable() const;

		//Returns the card number for the given memory.
		// Note: assumes that the pointer is inside the heap.
		std::size_t getCardNumber(BytePtr ptr) const;

		//Indicates if the generation requires a collection
		bool needsToCollect() const;

		//Indicates if the given object needs to be promoted to an older generation
		bool needsToPromote(int survivalCount) const;

		//Allocates an object of the given size
		BytePtr allocate(std::size_t size);

		//Marks that the generation has been collected
		void collected();
	};
}