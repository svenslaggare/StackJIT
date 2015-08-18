#pragma once

//Defines types and assumptions used through out the VM

//Holds a pointer value
using PtrValue = std::size_t;

#if defined(_WIN64) || defined(__MINGW32__)
//Holds a register value
using RegisterValue = long long;

//Represents a 64 bits signed integer
using Int64 = long long;
#else
//Holds a register value
using RegisterValue = long;

//Represents a 64 bits signed integer
using Int64 = long;
#endif

namespace StackJIT {
	//The size of the length of an array
	const int ARRAY_LENGTH_SIZE = 4;
}
