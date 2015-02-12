#include "linux.h"
#include <sys/mman.h>
#include <assert.h>

void* LinuxCompiler::allocateMemory(std::size_t size) {
	void *mem = mmap(
        nullptr,
        size,
        PROT_WRITE | PROT_READ,
        MAP_ANON | MAP_PRIVATE,
        -1,
        0);

    assert(mem != MAP_FAILED);
    return mem;
}

void LinuxCompiler::makeExecutableMemory(void* memory, std::size_t size) {
	int success = mprotect(memory, size, PROT_EXEC | PROT_READ);
	assert(success == 0);
}