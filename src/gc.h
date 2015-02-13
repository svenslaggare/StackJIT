#pragma once
#include <unordered_map>
#include <vector>

class ObjectHandle;
class Type;
class StructType;
class VMState;

//Represents the garbage collector
class GarbageCollector {
private:
	VMState& vmState;

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

	//Sweeps the object deleting unreachable objects.
	void sweepObjects();
public:
	//Creates a new GC
	GarbageCollector(VMState& vmState);
	
	~GarbageCollector();

	//Prevent the GC from being copied
	GarbageCollector(const GarbageCollector&) = delete;
	GarbageCollector& operator=(const GarbageCollector&) = delete;

	//Allocates a new array of the given type and length.
	unsigned char* newArray(const Type* elementType, int length);

	//Allocates a new struct of the given type.
	unsigned char* newStruct(const StructType* structType);

	//Marks the value of the given type
	void markValue(long value, const Type* type);

	//Begins the garbage collection. Return true if started.
	bool beginGC();

	//Ends the garbage collection.
	void endGC();
};