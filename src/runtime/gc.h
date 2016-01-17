#pragma once
#include "../type/objectref.h"
#include "../stackjit.h"
#include "managedheap.h"
#include "stackframe.h"
#include <unordered_map>
#include <vector>
#include <chrono>

class Type;
class ClassType;
class ArrayType;
class VMState;
class ManagedFunction;

//Holds information needed to perform the collection provided by the runtime
struct GCRuntimeInformation {
	RegisterValue* basePtr;
	ManagedFunction* function;
	int instIndex;

	GCRuntimeInformation(RegisterValue* basePtr, ManagedFunction* function, int instIndex);
};

//Represents the garbage collector
class GarbageCollector {
public:
	using VisitReferenceFn = std::function<void (StackFrameEntry)>;
	using VisitFrameFn = std::function<void (RegisterValue* basePtr, ManagedFunction* func, int instIndex)>;
private:
	VMState& vmState;

	ManagedHeap mHeap;

	std::size_t mNumAllocated = 0;
	std::size_t mAllocatedBeforeCollection = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> mGCStart;

	//Allocate an object of given type and size in the given heap
	unsigned char* allocateObject(ManagedHeap& heap, const Type* type, std::size_t size);

	//Deletes the given object
	void deleteObject(ManagedHeap& heap, ObjectRef objRef);

	//Prints the given object
	void printObject(ObjectRef objRef);

	//Visits the given frame entry if reference
	void visitFrameReference(StackFrameEntry frameEntry, VisitReferenceFn fn);

	//Visits all the references in the given stack frame
	void visitFrameReferences(RegisterValue* basePtr, ManagedFunction* func, int instIndex, VisitReferenceFn fn);

	//Visits all the references in all stack frames, starting at the given frame
	void visitAllFrameReferences(RegisterValue* basePtr, ManagedFunction* func, int instIndex,
								 VisitReferenceFn fn, VisitFrameFn frameFn = {});

	//Marks the given object
	void markObject(ObjectRef objRef);

	//Marks the value of the given type
	void markValue(RegisterValue value, const Type* type);

	//Marks the objects in all stack frames, starting at the given frame
	void markAllObjects(RegisterValue* basePtr, ManagedFunction* func, int instIndex);

	//Deletes unreachable objects.
	void sweepObjects();

	using ForwardingTable = std::unordered_map<unsigned char*, unsigned char*>;

	//Computes the new locations of the objects
	unsigned char* computeLocations(ForwardingTable& forwardingAddress);

	//Updates the references
	void updateReferences(GCRuntimeInformation& runtimeInformation, ForwardingTable& forwardingAddress);

	//Moves the objects
	int moveObjects(ForwardingTable& forwardingAddress);

	//Compacts the objects
	void compactObjects(GCRuntimeInformation& runtimeInformation);

	//Begins the garbage collection. Return true if started.
	bool beginGC(bool forceGC = false);
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

	//Begins a collection using the given runtime information
	void collect(GCRuntimeInformation& runtimeInformation);

	//Returns a reference to the given class
	ClassRef getClassRef(RawClassRef classRef);
};