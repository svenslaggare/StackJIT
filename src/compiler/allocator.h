#pragma once

#ifdef __unix__
#include <cstring>
#else
#include <cstddef>
#endif

namespace stackjit {
	//Represents a memory allocator
	namespace Allocator {
		//Allocates memory block of the given size
		void* allocate(std::size_t size);

		//Deallocate the given memory block
		void deallocate(void* memory, std::size_t size);

		//Makes the given memory executable
		bool makeExecutable(void* memory, std::size_t size);
	}
}
