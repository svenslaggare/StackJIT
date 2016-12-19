#ifdef __unix__
#include "../compiler/allocator.h"
#include <sys/mman.h>

namespace stackjit {
	void* Allocator::allocate(std::size_t size) {
		void *mem = mmap(
			nullptr,
			size,
			PROT_WRITE | PROT_READ | PROT_EXEC,
			MAP_ANON | MAP_PRIVATE,
			-1,
			0);

		if (mem == MAP_FAILED) {
			return nullptr;
		} else {
			return mem;
		}
	}

	void Allocator::deallocate(void* memory, std::size_t size) {
		munmap(memory, size);
	}

	bool Allocator::makeExecutable(void* memory, std::size_t size) {
		return mprotect(memory, size, PROT_EXEC | PROT_READ) == 0;
	}
}
#endif
