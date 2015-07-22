#pragma once

//Defines types and assumptions used through out the VM

//An address to an object (array, class)
using ObjectAddr = long;

//An address to an function
using FuncAddr = long;

namespace StackJIT {
	//The size of the length of an array
	const int ARRAY_LENGTH_SIZE = 4;
}