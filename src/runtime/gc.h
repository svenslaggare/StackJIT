#pragma once
#include "../type/objects.h"
#include "../type/objectref.h"
#include "../stackjit.h"
#include "managedheap.h"
#include <unordered_map>
#include <vector>
#include <chrono>

class ObjectHandle;
class Type;
class ClassType;
class ArrayType;
class VMState;

//Represents the garbage collector
class GarbageCollector {
private:
	VMState& vmState;

	ManagedHeap mYoungGeneration;
	ManagedHeap mOldGeneration;

	//Allocate an object of given type and size in the given heap
	unsigned char* allocateObject(ManagedHeap& heap, const Type* type, std::size_t size);
public:
	//Creates a new GC
	GarbageCollector(VMState& vmState);

	//Prevent the GC from being copied
	GarbageCollector(const GarbageCollector&) = delete;
	GarbageCollector& operator=(const GarbageCollector&) = delete;

	//Initializes the GC
	void initialize();

	//Allocates a new array of the given type and length.
	unsigned char* newArray(const ArrayType* arrayType, int length);

	//Allocates a new class of the given type.
	unsigned char* newClass(const ClassType* classType);

	//Returns a reference to the given class
	ClassRef getClassRef(RawClassRef classRef);
};