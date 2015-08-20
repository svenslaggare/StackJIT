#pragma once
#include "objects.h"
#include "objectref.h"
#include "stackjit.h"
#include <unordered_map>
#include <vector>

class ObjectHandle;
class Type;
class ClassType;
class VMState;

//Represents the garbage collector
class GarbageCollector {
private:
	VMState& vmState;

	std::size_t mNumAllocated = 0;
	const std::size_t mAllocatedBeforeCollection = 0;
	std::unordered_map<const unsigned char*, ObjectHandle*> mObjects;	
	std::vector<ObjectHandle*> mObjectsToRemove;

	//Adds the given handle to the list of objects
    void newObject(ObjectHandle* handle);

    //Deletes the given object
    void deleteObject(ObjectHandle* handle);

    //Prints the given object
    void printObject(ObjectHandle* handle);

	//Marks the given object.
	void markObject(ObjectHandle* handle);

	//Deletes unreachable objects.
	void sweepObjects();

	//Returns a handle for the given raw object pointer
	ObjectHandle* getHandle(unsigned char* objectPtr);
public:
	//Creates a new GC
	GarbageCollector(VMState& vmState);
	
	~GarbageCollector();

	//Prevent the GC from being copied
	GarbageCollector(const GarbageCollector&) = delete;
	GarbageCollector& operator=(const GarbageCollector&) = delete;

	//Allocates a new array of the given type and length.
	unsigned char* newArray(const Type* elementType, int length);

	//Allocates a new class of the given type.
	unsigned char* newClass(const ClassType* classType);

	//Marks the value of the given type
	void markValue(RegisterValue value, const Type* type);

	//Begins the garbage collection. Return true if started.
	bool beginGC();

	//Ends the garbage collection.
	void endGC();

	//Returns a reference to the given class
	ClassRef getClassRef(RawClassRef classRef);
};