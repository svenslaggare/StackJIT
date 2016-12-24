#pragma once
#include "../type/objectref.h"
#include "../stackjit.h"
#include "stackframe.h"
#include "gcgeneration.h"
#include <unordered_map>
#include <vector>
#include <chrono>

namespace stackjit {
	class Type;
	class ClassType;
	class ArrayType;
	class VMState;
	class ManagedFunction;

	//Holds information needed to perform the collection provided by the runtime
	struct GCRuntimeInformation {
		RegisterValue* const basePtr;
		ManagedFunction* const function;
		const int instructionIndex;

		GCRuntimeInformation(RegisterValue* basePtr, ManagedFunction* function, int instructionIndex);
	};

	//Represents the garbage collector
	class GarbageCollector {
	private:
		VMState& mVMState;

		CollectorGeneration mYoungGeneration;
		CollectorGeneration mOldGeneration;
		std::chrono::time_point<std::chrono::high_resolution_clock> mGCStart;

		//Indicates if the given generation is the young
		bool isYoung(const CollectorGeneration& generation) const;

		//Indicates if the given generation is the old
		bool isOld(const CollectorGeneration& generation) const;

		//Prints the given object
		void printObject(ObjectRef objRef);

		//Allocate an object of given type and size in the given heap
		RawObjectRef allocateObject(CollectorGeneration& generation, const Type* type, std::size_t size);

		//Deletes the given object
		void deleteObject(ObjectRef objRef);

		//Marks the given object
		void markObject(CollectorGeneration& generation, ObjectRef objRef);

		//Marks the value of the given type
		void markValue(CollectorGeneration& generation, RegisterValue value, const Type* type);

		//Marks the objects in all stack frames, starting at the given frame
		void markAllObjects(CollectorGeneration& generation, RegisterValue* basePtr, ManagedFunction* func, int instIndex);

		//Deletes unreachable objects.
		void sweepObjects(CollectorGeneration& generation);

		using ForwardingTable = std::unordered_map<BytePtr, BytePtr>;
		using PromotedObjects = std::vector<BytePtr>;

		//Computes the new locations of the objects
		BytePtr computeNewLocations(CollectorGeneration& generation, ForwardingTable& forwardingAddress, PromotedObjects& promotedObjects);

		//Updates the given object reference
		void updateReference(ForwardingTable& forwardingAddress, PtrValue* objRef);

		//Updates the references stored in the given heap
		void updateHeapReferences(CollectorGeneration& generation, ForwardingTable& forwardingAddress);

		//Updates the references stored in the stack
		void updateStackReferences(const GCRuntimeInformation& runtimeInformation, ForwardingTable& forwardingAddress);

		//Moves the objects
		int moveObjects(CollectorGeneration& generation, ForwardingTable& forwardingAddress);

		//Promotes the object to the given generation
		void promoteObjects(CollectorGeneration& generation, PromotedObjects& promotedObjects, ForwardingTable& forwardingAddress);

		//Compacts the objects
		void compactObjects(CollectorGeneration& generation, CollectorGeneration* nextGeneration, const GCRuntimeInformation& runtimeInformations);

		//Begins the garbage collection. Return true if started.
		bool beginGC(int generationNumber, bool forceGC);
	public:
		//Creates a new GC
		GarbageCollector(VMState& vmState);

		//Prevent the GC from being copied
		GarbageCollector(const GarbageCollector&) = delete;
		GarbageCollector& operator=(const GarbageCollector&) = delete;

		//Returns the young generation
		CollectorGeneration& youngGeneration();
		const CollectorGeneration& youngGeneration() const;

		//Returns the old generation
		CollectorGeneration& oldGeneration();
		const CollectorGeneration& oldGeneration() const;

		//Returns the given generation
		CollectorGeneration& getGeneration(int generationNumber);
		const CollectorGeneration& getGeneration(int generationNumber) const;

		//Allocates a new array of the given type and length.
		RawArrayRef newArray(const ArrayType* arrayType, int length);

		//Allocates a new class of the given type.
		RawClassRef newClass(const ClassType* classType);

		//Begins a collection using the given runtime information
		void collect(const GCRuntimeInformation& runtimeInformation, int generationNumber, bool forceGC = false);

		//Returns a reference to the given class
		inline ClassRef getClassRef(RawClassRef classRef) {
			ObjectRef objRef(classRef);
			auto classType = static_cast<const ClassType*>(objRef.type());
			return ClassRef(objRef, *classType->metadata());
		}
	};
}
