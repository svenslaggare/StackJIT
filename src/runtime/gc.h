#pragma once
#include "../type/objectref.h"
#include "../stackjit.h"
#include "managedheap.h"
#include <unordered_map>
#include <vector>
#include <chrono>

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

	std::size_t mNumAllocated = 0;
	std::size_t mAllocatedBeforeCollection = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> mGCStart;

	//Allocate an object of given type and size in the given heap
	unsigned char* allocateObject(ManagedHeap& heap, const Type* type, std::size_t size);

	//Prints the given object
	void printObject(ObjectRef objRef);

	//Marks the given object.
	void markObject(ObjectRef objRef);

	//Deletes unreachable objects.
	void sweepObjects();
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

	//Marks the value of the given type
	void markValue(RegisterValue value, const Type* type);

	//Begins the garbage collection. Return true if started.
	bool beginGC(bool forceGC = false);

	//Ends the garbage collection.
	void endGC();

	//Returns a reference to the given class
	ClassRef getClassRef(RawClassRef classRef);
};