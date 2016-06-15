#if defined(_WIN64) || defined(__MINGW32__)
#include "../compiler/allocator.h"
#include <Windows.h>

namespace stackjit {
	void* Allocator::allocate(std::size_t size) {
		return VirtualAlloc(
		    nullptr,
		    size,
		    MEM_COMMIT | MEM_RESERVE,
		    PAGE_EXECUTE_READWRITE);
	}

	void Allocator::deallocate(void* mem, std::size_t size) {
		VirtualFree(mem, size, MEM_RELEASE);
	}

	bool Allocator::makeExecutable(void* mem, std::size_t size) {
		return VirtualProtect(mem, size, PAGE_EXECUTE_READ, nullptr) == 0;
	}
}
#endif
