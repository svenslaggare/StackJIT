#if defined(_WIN64) || defined(__MINGW32__)
#include "../compiler/allocator.h"
#include <Windows.h>

void* Allocator::allocate(std::size_t size) {
	return VirtualAlloc(
	    nullptr,
	    size,
	    MEM_COMMIT | MEM_RESERVE,
	    PAGE_EXECUTE_READWRITE);
}

void Allocator::deallocate(void* mem, std::size_t size) {
	VirtualProtect(mem, size, PAGE_EXECUTE_READ, nullptr);
}

bool Allocator::makeExecutable(void* mem, std::size_t size) {
	return mprotect(mem, size, PROT_EXEC | PROT_READ) == 0;
}
#endif