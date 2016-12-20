#include "gc.h"
#include "../type/type.h"
#include "../vmstate.h"
#include "../compiler/amd64.h"
#include "../stackjit.h"
#include "../helpers.h"
#include "stackframe.h"
#include "runtime.h"
#include <iostream>
#include <sstream>
#include <string.h>

namespace stackjit {
	namespace {
		void printTimes(char c, int times) {
			for (int i = 0; i < times; i++) {
				std::cout << c;
			}
		}

		std::string ptrToString(BytePtr ptr) {
			std::stringstream stringstream;
			stringstream << std::hex << "0x" << (std::size_t)ptr << std::dec;
			return stringstream.str();
		}
	}

	GCRuntimeInformation::GCRuntimeInformation(RegisterValue* basePtr, ManagedFunction* function, int instructionIndex)
			: basePtr(basePtr), function(function), instructionIndex(instructionIndex) {

	}

	CollectorGeneration::CollectorGeneration(std::size_t size, std::size_t allocatedBeforeCollection, int survivedCollectionsBeforePromote)
			: mHeap(size),
			  mAllocatedBeforeCollection(allocatedBeforeCollection),
			  mSurvivedCollectionsBeforePromote(survivedCollectionsBeforePromote),
			  mCardTable(new unsigned char[size / CARD_SIZE] { 0 }) {

	}

	CollectorGeneration::~CollectorGeneration() {
		delete[] mCardTable;
	}

	ManagedHeap& CollectorGeneration::heap() {
		return mHeap;
	}

	const ManagedHeap& CollectorGeneration::heap() const {
		return mHeap;
	}

	BytePtr CollectorGeneration::cardTable() const {
		return mCardTable;
	}

	bool CollectorGeneration::needsToCollect() const {
		return mNumAllocated >= mAllocatedBeforeCollection;
	}

	bool CollectorGeneration::needsToPromote(int survivalCount) const {
		if (mSurvivedCollectionsBeforePromote == -1) {
			return false;
		}

		return survivalCount >= mSurvivedCollectionsBeforePromote;
	}

	BytePtr CollectorGeneration::allocate(std::size_t size) {
		auto objPtr = mHeap.allocate(size);
		if (objPtr != nullptr) {
			mNumAllocated++;
		} else {
			throw std::runtime_error("Could not allocate object.");
		}

		return objPtr;
	}

	void CollectorGeneration::collected() {
		mNumAllocated = 0;
	}

	GarbageCollector::GarbageCollector(VMState& vmState)
			: vmState(vmState),
			  mYoungGeneration(4 * 1024 * 1024, (std::size_t)vmState.config.allocationsBeforeGC, 5),
			  mOldGeneration(8 * 1024 * 1024, (std::size_t)vmState.config.allocationsBeforeGC) {

	}

	CollectorGeneration& GarbageCollector::youngGeneration() {
		return mYoungGeneration;
	}

	const CollectorGeneration& GarbageCollector::youngGeneration() const {
		return mYoungGeneration;
	}

	CollectorGeneration& GarbageCollector::oldGeneration() {
		return mOldGeneration;
	}

	const CollectorGeneration& GarbageCollector::oldGeneration() const {
		return mOldGeneration;
	}

	CollectorGeneration& GarbageCollector::getGeneration(int generationNumber) {
		switch (generationNumber) {
			case 0:
				return mYoungGeneration;
			case 1:
				return mOldGeneration;
			default:
				throw std::runtime_error("The given generation does not exist.");
				break;
		}
	}

	const CollectorGeneration& GarbageCollector::getGeneration(int generationNumber) const {
		switch (generationNumber) {
			case 0:
				return mYoungGeneration;
			case 1:
				return mOldGeneration;
			default:
				throw std::runtime_error("The given generation does not exist.");
				break;
		}
	}

	void GarbageCollector::printObject(ObjectRef objRef) {
		std::cout
			<< ptrToString(objRef.dataPtr())
			<< ": { type: " << objRef.type()->name()
			<< ", size: " << objRef.size() << " bytes"
			<< ", survival: " << objRef.survivalCount()
			<< " }"
			<< std::endl;
	}

	RawObjectRef GarbageCollector::allocateObject(CollectorGeneration& generation, const Type* type, std::size_t size) {
		auto fullSize = stackjit::OBJECT_HEADER_SIZE + size;
		auto objPtr = generation.allocate(fullSize);

		memset(objPtr, 0, fullSize);

		//Set the header
		Helpers::setValue<std::size_t>(objPtr, 0, (PtrValue)type);
		Helpers::setValue<unsigned char>(objPtr, sizeof(PtrValue), 0); //GC info

		//The returned ptr is to the data
		return objPtr + stackjit::OBJECT_HEADER_SIZE;
	}

	void GarbageCollector::deleteObject(ObjectRef objRef) {
		Helpers::setValue<std::size_t>(objRef.fullPtr(), 0, objRef.fullSize());  //The amount of data to skip from the start.
		Helpers::setValue<unsigned char>(objRef.fullPtr(), sizeof(std::size_t), 0xFF); //Indicator for dead object
	}

	RawArrayRef GarbageCollector::newArray(const ArrayType* arrayType, int length) {
	    auto elementType = arrayType->elementType();
	    auto elementSize = TypeSystem::sizeOfType(elementType);

	    std::size_t objectSize = stackjit::ARRAY_LENGTH_SIZE + (length * elementSize);
	    auto arrayPtr = allocateObject(mYoungGeneration, arrayType, objectSize);

	    //Set the length of the array
		Helpers::setValue(arrayPtr, 0, length);

	    if (vmState.config.enableDebug && vmState.config.printAllocation) {
	        std::cout
	            << "Allocated array ("
	            << "size: " << objectSize << " bytes, "
				<< "length: " << length << ", type: " << elementType->name()
	            << ") at " << ptrToString(arrayPtr)
	            << std::endl;
	    }

	    return arrayPtr;
	}

	RawClassRef GarbageCollector::newClass(const ClassType* classType) {
	    std::size_t objectSize = classType->metadata()->size();
	    auto classPtr = allocateObject(mYoungGeneration, classType, objectSize);

	    if (vmState.config.enableDebug && vmState.config.printAllocation) {
	        std::cout
	            << "Allocated object (size: " << objectSize << " bytes, type: " <<  classType->name()
	            << ") at " << ptrToString(classPtr)
	            << std::endl;
	    }

	    return classPtr;
	}

	void GarbageCollector::visitFrameReference(StackFrameEntry frameEntry, VisitReferenceFn fn) {
		if (frameEntry.type()->isReference()) {
			auto objPtr = (BytePtr)frameEntry.value();

			//Don't visit nulls
			if (objPtr == nullptr) {
				return;
			}

			fn(frameEntry);
		}
	}

	void GarbageCollector::visitFrameReferences(RegisterValue* basePtr, ManagedFunction* func, int instIndex, VisitReferenceFn fn) {
		StackFrame stackFrame(basePtr, func, instIndex);
		auto numArgs = func->def().numParams();
		auto numLocals = func->numLocals();
		auto stackSize = stackFrame.operandStackSize();

		for (std::size_t i = 0; i < numArgs; i++) {
			auto arg = stackFrame.getArgument(i);
			visitFrameReference(arg, fn);
		}

		for (std::size_t i = 0; i < numLocals; i++) {
			auto local = stackFrame.getLocal(i);
			visitFrameReference(local, fn);
		}

		for (std::size_t i = 0; i < stackSize; i++) {
			auto operand = stackFrame.getStackOperand(i);
			visitFrameReference(operand, fn);
		}
	}

	void GarbageCollector::visitAllFrameReferences(RegisterValue* basePtr,
												   ManagedFunction* func,
												   int instIndex,
												   VisitReferenceFn fn,
												   VisitFrameFn frameFn) {
		if (frameFn) {
			frameFn(basePtr, func, instIndex);
		}

		//Visit the calling stack frame
		visitFrameReferences(basePtr, func, instIndex, fn);

		//Then all other stack frames
		auto topEntryPtr = vmState.engine().callStack().top();
		int topFuncIndex = 0;
		while (topEntryPtr > vmState.engine().callStack().start()) {
			auto callEntry = *topEntryPtr;
			auto topFunc = callEntry.function;
			auto callPoint = callEntry.callPoint;
			auto callBasePtr = Runtime::Internal::findBasePtr(basePtr, 0, topFuncIndex);

			if (frameFn) {
				frameFn(callBasePtr, topFunc, callPoint);
			}

			visitFrameReferences(callBasePtr, topFunc, callPoint, fn);

			topEntryPtr--;
			topFuncIndex++;
		}
	}

	void GarbageCollector::markObject(ObjectRef objRef) {
		if (!objRef.isMarked()) {
			if (objRef.type()->isArray()) {
				objRef.mark();

				auto arrayType = static_cast<const ArrayType*>(objRef.type());

				//Mark ref elements
				if (arrayType->elementType()->isReference()) {
					ArrayRef<PtrValue> arrayRef(objRef.dataPtr());
					for (int i = 0; i < arrayRef.length(); i++) {
						markValue(arrayRef.getElement(i), arrayType->elementType());
					}
				}
			} else if (objRef.type()->isClass()) {
				objRef.mark();

				//Mark ref fields
				auto classType = static_cast<const ClassType*>(objRef.type());
				for (auto fieldEntry : classType->metadata()->fields()) {
					auto field = fieldEntry.second;

					if (field.type()->isReference()) {
						RegisterValue fieldValue = *(PtrValue*)(objRef.dataPtr() + field.offset());
						markValue(fieldValue, field.type());
					}
				}
			}
		}
	}

	void GarbageCollector::markValue(RegisterValue value, const Type* type) {
		if (type->isReference()) {
			auto objPtr = (BytePtr)value;

			//Don't mark nulls
			if (objPtr == nullptr) {
				return;
			}

			markObject(ObjectRef((RawObjectRef)value));
		}
	}

	void GarbageCollector::markAllObjects(RegisterValue* basePtr, ManagedFunction* func, int instIndex) {
		if (vmState.config.enableDebug && vmState.config.printGCStackTrace) {
			std::cout << "Stack trace: " << std::endl;
		}

		visitAllFrameReferences(basePtr, func, instIndex, [this](StackFrameEntry frameEntry) {
			markObject(ObjectRef((RawObjectRef)frameEntry.value()));
		}, [this](RegisterValue* frameBasePtr, ManagedFunction* frameFunc, int frameCallPoint) {
			if (vmState.config.enableDebug && vmState.config.printGCStackTrace) {
				std::cout << frameFunc->def().name() << " (" << frameCallPoint << ")" << std::endl;
				Runtime::Internal::printAliveObjects(frameBasePtr, frameFunc, frameCallPoint, "\t");
			}
		});
	}

	void GarbageCollector::sweepObjects(CollectorGeneration& generation) {
		int numDeallocatedObjects = 0;

		generation.heap().visitObjects([&](ObjectRef objRef) {
			if (!objRef.isMarked()) {
				numDeallocatedObjects++;

				if (vmState.config.enableDebug && vmState.config.printDeallocation) {
					std::cout << "Deleted object: ";
					printObject(objRef);
				}

				deleteObject(objRef);
			} else {
				objRef.unmark();
			}
		});

		if (vmState.config.enableDebug && vmState.config.printGCStats) {
			std::cout << "Deallocated: " << numDeallocatedObjects << " objects." << std::endl;
			std::cout << "GC time: " << Helpers::getDuration(mGCStart) << " ms." << std::endl;
		}
	}

	BytePtr GarbageCollector::computeNewLocations(CollectorGeneration& generation, ForwardingTable& forwardingAddress, std::vector<BytePtr>& promotedObjects) {
		auto free = generation.heap().data();
		generation.heap().visitObjects([&](ObjectRef objRef) {
			if (objRef.isMarked()) {
				if (!generation.needsToPromote(objRef.survivalCount())) {
					forwardingAddress.insert({ objRef.fullPtr(), free });
					free += objRef.fullSize();
				} else {
					promotedObjects.push_back(objRef.fullPtr());
				}
			}
		});
		return free;
	}

	void GarbageCollector::updateReference(ForwardingTable& forwardingAddress, PtrValue* objRef) {
		if (*objRef != 0) {
			auto oldAddress = ((BytePtr)*objRef) - stackjit::OBJECT_HEADER_SIZE;

			//It might be that there exists no forwarding, since the object is in another generation
			if (forwardingAddress.count(oldAddress) > 0) {
				auto newAddress = forwardingAddress[oldAddress];
				*objRef = (PtrValue)(newAddress + stackjit::OBJECT_HEADER_SIZE);
			}
		}
	}

	void GarbageCollector::updateHeapReferences(CollectorGeneration& generation, ForwardingTable& forwardingAddress) {
		generation.heap().visitObjects([&](ObjectRef objRef) {
			if (objRef.isMarked()) {
				if (objRef.type()->isArray()) {
					auto arrayType = static_cast<const ArrayType*>(objRef.type());

					//Update ref elements
					if (arrayType->elementType()->isReference()) {
						ArrayRef<PtrValue> arrayRef(objRef.dataPtr());
						for (int i = 0; i < arrayRef.length(); i++) {
							updateReference(forwardingAddress, arrayRef.elementsPtr() + i);
						}
					}
				} else if (objRef.type()->isClass()) {
					//Update ref fields
					auto classType = static_cast<const ClassType*>(objRef.type());
					for (auto fieldEntry : classType->metadata()->fields()) {
						auto field = fieldEntry.second;

						if (field.type()->isReference()) {
							updateReference(forwardingAddress, (PtrValue*)(objRef.dataPtr() + field.offset()));
						}
					}
				}
			}
		});
	}

	void GarbageCollector::updateStackReferences(GCRuntimeInformation& runtimeInformation, ForwardingTable& forwardingAddress) {
		visitAllFrameReferences(
			runtimeInformation.basePtr,
			runtimeInformation.function,
			runtimeInformation.instructionIndex,
			[&](StackFrameEntry frameEntry) {
				updateReference(forwardingAddress, (PtrValue*)frameEntry.valuePtr());
			});
	}

	void GarbageCollector::updateReferences(CollectorGeneration& generation, GCRuntimeInformation& runtimeInformation, ForwardingTable& forwardingAddress) {
		updateStackReferences(runtimeInformation, forwardingAddress);
		updateHeapReferences(generation, forwardingAddress);
	}

	int GarbageCollector::moveObjects(CollectorGeneration& generation, ForwardingTable& forwardingAddress) {
		int numDeallocatedObjects = 0;
		generation.heap().visitObjects([&](ObjectRef objRef) {
			if (objRef.isMarked()) {
				objRef.unmark();
				objRef.increaseSurvivalCount();
				auto dest = forwardingAddress[objRef.fullPtr()];
				memmove(dest, objRef.fullPtr(), objRef.fullSize());
			} else {
				numDeallocatedObjects++;

				if (vmState.config.enableDebug && vmState.config.printDeallocation) {
					std::cout << "Deleted object: ";
					printObject(objRef);
				}
			}
		});

		return numDeallocatedObjects;
	}

	void GarbageCollector::promoteObjects(CollectorGeneration& generation, PromotedObjects& promotedObjects, ForwardingTable& forwardingAddress) {
		for (auto& oldObjPtr : promotedObjects) {
			ObjectRef objRef(oldObjPtr + stackjit::OBJECT_HEADER_SIZE);

			auto newObjPtr = generation.allocate(objRef.fullSize());
			memmove(newObjPtr, objRef.fullPtr(), objRef.fullSize());
			forwardingAddress.insert({ oldObjPtr, newObjPtr });

			ObjectRef newObjRef(newObjPtr + stackjit::OBJECT_HEADER_SIZE);
			newObjRef.resetSurvivalCount();
			newObjRef.unmark();

			if (vmState.config.enableDebug && vmState.config.printGCPromotion) {
				std::cout
					<< "Promoted object " << ptrToString(objRef.dataPtr()) << " (" << objRef.type()->name() << ")"
					<< " to an older generation, new address: "
					<< ptrToString(newObjRef.dataPtr())
					<< std::endl;
			}

			deleteObject(objRef); //Mark as deleted to skip when searching
		}
	}

	void GarbageCollector::compactObjects(CollectorGeneration& generation, CollectorGeneration* nextGeneration, GCRuntimeInformation& runtimeInformation) {
		ForwardingTable forwardingAddress;
		PromotedObjects promotedObjects;

		//Compute the new locations of the objects
		auto free = computeNewLocations(generation, forwardingAddress, promotedObjects);

		//Promote objects to the next generation
		if (!promotedObjects.empty()) {
			promoteObjects(*nextGeneration, promotedObjects, forwardingAddress);
		}

		//Update the references
		updateReferences(generation, runtimeInformation, forwardingAddress);
		if (!promotedObjects.empty()) {
			updateHeapReferences(*nextGeneration, forwardingAddress);
		}

		//Move the objects
		int numDeallocatedObjects = moveObjects(generation, forwardingAddress);
		generation.heap().setNextAllocation(free);

		if (vmState.config.enableDebug && vmState.config.printGCStats) {
			std::cout << "Deallocated: " << numDeallocatedObjects << " objects." << std::endl;
			std::cout << "GC time: " << Helpers::getDuration(mGCStart) << " ms." << std::endl;
		}
	}

	bool GarbageCollector::beginGC(int generationNumber, bool forceGC) {
		if (getGeneration(generationNumber).needsToCollect() || forceGC) {
			if (vmState.config.enableDebug && vmState.config.printGCStats) {
				mGCStart = std::chrono::high_resolution_clock::now();
			}

			return true;
		} else {
			return false;
		}
	}

	void GarbageCollector::collect(GCRuntimeInformation& runtimeInformation, int generationNumber, bool forceGC) {
		auto basePtr = runtimeInformation.basePtr;
		auto func = runtimeInformation.function;
		auto instIndex = runtimeInformation.instructionIndex;
		auto& generation = getGeneration(generationNumber);

		if (beginGC(generationNumber, forceGC)) {
			std::size_t startStrLength = 0;

			if (vmState.config.enableDebug && vmState.config.printGCPeriod) {
				std::string lines = "------------------------";
				auto startStr = lines + "Start GC (" + std::to_string(generationNumber) + ") in function "
								+ func->def().name() + " (" + std::to_string(instIndex) + ")"
								+ lines;
				std::cout << startStr << std::endl;
				startStrLength = startStr.length();
			}

			if (vmState.config.enableDebug && vmState.config.printAliveObjects) {
				std::cout << "Alive objects: " << std::endl;

				generation.heap().visitObjects([this](ObjectRef objRef) {
					printObject(objRef);
				});
				std::cout << std::endl;
			}

			//Mark all objects
			markAllObjects(basePtr, func, instIndex);

	//		//Sweep objects
	//		sweepObjects();
	//		mNumAllocated = 0;

			//Compact objects
			compactObjects(generation, &mOldGeneration, runtimeInformation);
			generation.collected();

			if (vmState.config.enableDebug && vmState.config.printGCPeriod) {
				printTimes('-', (int)startStrLength / 2 - 3);
				std::cout << "End GC";
				printTimes('-', ((int)startStrLength + 1) / 2 - 3);
				std::cout << std::endl;
			}
		}
	}
}
