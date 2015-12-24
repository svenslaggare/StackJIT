#ifdef __unix__
#include "../compiler/allocator.h"
#include <sys/mman.h>

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

void Allocator::deallocate(void* mem, std::size_t size) {
	munmap(mem, size);
}

bool Allocator::makeExecutable(void* mem, std::size_t size) {
	return mprotect(mem, size, PROT_EXEC | PROT_READ) == 0;
}
#endif