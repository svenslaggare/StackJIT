#include "memory.h"
#include "allocator.h"
#include "../compiler/jit.h"
#include "../core/function.h"
#include <iostream>

namespace stackjit {
	CodePage::CodePage(void* start, std::size_t size)
		: mStart(start), mSize(size), mUsed(0) {

	}

	CodePage::~CodePage() {
		Allocator::deallocate(mStart, mSize);
	}

	void* CodePage::start() const {
		return mStart;
	}

	std::size_t CodePage::size() const {
		return mSize;
	}

	std::size_t CodePage::used() const {
		return mUsed;
	}

	void* CodePage::allocateMemory(std::size_t size) {
		if (mUsed + size < mSize) {
			void* newPtr = (char*)mStart + mUsed;
			mUsed += size;
			return newPtr;
		} else {
			return nullptr;
		}
	}

	void CodePage::makeExecutable() {
		if (!Allocator::makeExecutable(mStart, mSize)) {
			throw std::runtime_error("Unable to make memory executable.");
		}
	}

	MemoryManager::MemoryManager() {

	}

	MemoryManager::~MemoryManager() {
		for (auto codePage : mPages) {
			delete codePage;
		}
	}

	CodePage* MemoryManager::newPage(std::size_t size) {
		//Align to page size
		size = ((size + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE;

		void *mem = Allocator::allocate(size);
		if (mem == nullptr) {
			throw std::runtime_error("Unable to allocate memory.");
		}

		auto newPage = new CodePage(mem, size);
		mPages.push_back(newPage);
		return newPage;
	}

	void* MemoryManager::allocateMemory(std::size_t size) {
		CodePage* page = nullptr;

		//Find a page with enough size
		for (auto currentPage : mPages) {
			if (currentPage->used() + size < currentPage->size()) {
				page = currentPage;
				break;
			}
		}

		if (page == nullptr) {
			page = newPage(size);
		}

		return page->allocateMemory(size);
	}

	void MemoryManager::makeMemoryExecutable() {
		for (auto codePage : mPages) {
			codePage->makeExecutable();
		}
	}
}
