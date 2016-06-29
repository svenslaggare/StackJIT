#pragma once
#include <vector>

namespace stackjit {
	//Represents a code page
	class CodePage {
	private:
		void* mStart;
		const std::size_t mSize;
		std::size_t mUsed;
	public:
		//Creates a new code page
		CodePage(void* start, std::size_t size);
		~CodePage();

		//Prevent copies
		CodePage(const CodePage&) = delete;
		CodePage& operator=(const CodePage&) = delete;

		//Returns the start of the page
		void* start() const;

		//Returns the size of the page
		std::size_t size() const;

		//Returns the number of bytes used
		std::size_t used() const;

		//Allocates the given memory in the page. Return nullptr if no room
		void* allocateMemory(std::size_t size);

		//Makes the page executable
		void makeExecutable();
	};

	//Represents a memory manager
	class MemoryManager {
	private:
		const static std::size_t PAGE_SIZE = 4096;

		std::vector<CodePage*> mPages;

		//Creates a new page
		CodePage* newPage(std::size_t size);
	public:
		//Creates a new memory manager
		MemoryManager();
		~MemoryManager();

		//Prevent copies
		MemoryManager(const MemoryManager&) = delete;
		MemoryManager& operator=(const MemoryManager&) = delete;

		//Allocates memory of the given size. The memory allocated by this function is handled automatic.
		void* allocateMemory(std::size_t size);

		//Makes all the allocated memory executable
		void makeMemoryExecutable();
	};
}
