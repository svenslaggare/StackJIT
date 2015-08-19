#pragma once

//Defines types and assumptions used through out the VM

//Holds a pointer value
using PtrValue = std::size_t;

//Holds a register value
using RegisterValue = std::int64_t;

namespace StackJIT {
	//The size of the length of an array
	const int ARRAY_LENGTH_SIZE = 4;
}
