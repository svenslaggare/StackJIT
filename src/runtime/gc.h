#pragma once
#include "../type/objectref.h"
#include "../stackjit.h"
#include "managedheap.h"
#include "stackframe.h"
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
		RegisterValue* basePtr;
		ManagedFunction* function;
		int instructionIndex;

		GCRuntimeInformation(RegisterValue* basePtr, ManagedFunction* function, int instructionIndex);
	};

	//Represents a generation for the garbage collector
	class CollectorGeneration {
	private:
		ManagedHeap mHeap;

		std::size_t mNumAllocated = 0;
		std::size_t mAllocatedBeforeCollection = 0;
		int mSurvivedCollectionsBeforePromote = 0;

		BytePtr mCardTable;
	public:
		static const std::size_t CARD_SIZE = 1024; //The size of a card in the table

		//Creates a new generation
		CollectorGeneration(std::size_t size, std::size_t allocatedBeforeCollection, int survivedCollectionsBeforePromote = -1);
		~CollectorGeneration();

		//Prevent the generation from being copied
		CollectorGeneration(const CollectorGeneration&) = delete;
		CollectorGeneration& operator=(const CollectorGeneration&) = delete;

		//Returns the heap
		ManagedHeap& heap();
		const ManagedHeap& heap() const;

		//Returns the card table
		BytePtr cardTable() const;

		//Indicates if the generation requires a collection
		bool needsToCollect() const;

		//Indicates if the given object needs to be promoted to an older generation
		bool needsToPromote(int survivalCount) const;

		//Allocates an object of the given size
		BytePtr allocate(std::size_t size);

		//Marks that the generation has been collected
		void collected();
	};

	//Represents the garbage collector
	class GarbageCollector {
	public:
		using VisitReferenceFn = std::function<void (StackFrameEntry)>;
		using VisitFrameFn = std::function<void (RegisterValue* basePtr, ManagedFunction* func, int instIndex)>;
	private:
		VMState& vmState;

		CollectorGeneration mYoungGeneration;
		CollectorGeneration mOldGeneration;
		std::chrono::time_point<std::chrono::high_resolution_clock> mGCStart;

		//Allocate an object of given type and size in the given heap
		RawObjectRef allocateObject(CollectorGeneration& generation, const Type* type, std::size_t size);

		//Deletes the given object
		void deleteObject(ObjectRef objRef);

		//Prints the given object
		void printObject(ObjectRef objRef);

		//Visits the given frame entry if reference
		void visitFrameReference(StackFrameEntry frameEntry, VisitReferenceFn fn);

		//Visits all the references in the given stack frame
		void visitFrameReferences(RegisterValue* basePtr, ManagedFunction* func, int instIndex, VisitReferenceFn fn);

		//Visits all the references in all stack frames, starting at the given frame
		void visitAllFrameReferences(RegisterValue* basePtr,
									 ManagedFunction* func,
									 int instIndex,
									 VisitReferenceFn fn,
									 VisitFrameFn frameFn = {});

		//Marks the given object
		void markObject(ObjectRef objRef);

		//Marks the value of the given type
		void markValue(RegisterValue value, const Type* type);

		//Marks the objects in all stack frames, starting at the given frame
		void markAllObjects(RegisterValue* basePtr, ManagedFunction* func, int instIndex);

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
		void updateStackReferences(GCRuntimeInformation& runtimeInformation, ForwardingTable& forwardingAddress);

		//Updates the references
		void updateReferences(CollectorGeneration& generation, GCRuntimeInformation& runtimeInformation, ForwardingTable& forwardingAddress);

		//Moves the objects
		int moveObjects(CollectorGeneration& generation, ForwardingTable& forwardingAddress);

		//Promotes the object to the given generation
		void promoteObjects(CollectorGeneration& generation, PromotedObjects& promotedObjects, ForwardingTable& forwardingAddress);

		//Compacts the objects
		void compactObjects(CollectorGeneration& generation, CollectorGeneration* nextGeneration, GCRuntimeInformation& runtimeInformations);

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
		void collect(GCRuntimeInformation& runtimeInformation, int generationNumber, bool forceGC = false);

		//Returns a reference to the given class
		inline ClassRef getClassRef(RawClassRef classRef) {
			ObjectRef objRef(classRef);
			auto classType = static_cast<const ClassType*>(objRef.type());
			return ClassRef(objRef, *classType->metadata());
		}
	};
}
