#pragma once
#include <cstdint>

//Defines types and assumptions used through out the VM
namespace stackjit {
	//Holds a pointer value
	using PtrValue = std::size_t;

	//Holds a register value
	using RegisterValue = std::int64_t;

	//Byte pointer
	using BytePtr = unsigned char*;

	//Represents a byte
	using Byte = unsigned char;

	//The size of the length of an array
	const int ARRAY_LENGTH_SIZE = 4;

	//The size of the object header
	const int OBJECT_HEADER_SIZE = 9;
}
