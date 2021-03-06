#include "gc.h"
#include "../type/type.h"
#include "../vmstate.h"
#include "../compiler/x64/amd64.h"
#include "../stackjit.h"
#include "../helpers.h"
#include "stackframe.h"
#include "runtime.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <cstring>

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

	GCRuntimeInformation::GCRuntimeInformation(const StackFrame& stackFrame)
			: stackFrame(stackFrame) {

	}

	GarbageCollector::GarbageCollector(VMState& vmState)
			: mVMState(vmState),
			  mYoungGeneration(4 * 1024 * 1024, (std::size_t)vmState.config.allocationsBeforeGC, 5),
			  mOldGeneration(8 * 1024 * 1024, (std::size_t)vmState.config.allocationsBeforeGC, -1, 1024) {

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

	bool GarbageCollector::isYoung(const CollectorGeneration& generation) const {
		return &mYoungGeneration == &generation;
	}

	bool GarbageCollector::isOld(const CollectorGeneration& generation) const {
		return &mOldGeneration == &generation;
	}

	RawObjectRef GarbageCollector::allocateObject(CollectorGeneration& generation, const Type* type, std::size_t size) {
		auto fullSize = stackjit::OBJECT_HEADER_SIZE + size;
		auto objPtr = generation.allocate(fullSize);

		std::memset(objPtr, 0, fullSize);

		//Set the header
		Helpers::setValue<std::size_t>(objPtr, 0, (PtrValue)type); //Type
		Helpers::setValue<unsigned char>(objPtr, sizeof(PtrValue), 0); //GC info

		//The returned pointer is to the data
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

	    if (mVMState.config.enableDebug && mVMState.config.printAllocation) {
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

	    if (mVMState.config.enableDebug && mVMState.config.printAllocation) {
	        std::cout
	            << "Allocated object (size: " << objectSize << " bytes, type: " <<  classType->name()
	            << ") at " << ptrToString(classPtr)
	            << std::endl;
	    }

	    return classPtr;
	}

	void GarbageCollector::markObject(CollectorGeneration& generation, ObjectRef objRef) {
		//Don't mark objects in the old generation
		if (isYoung(generation) && !generation.heap().inside(objRef.fullPtr())) {
			return;
		}

		if (!objRef.isMarked()) {
			if (objRef.type()->isArray()) {
				objRef.mark();

				//Mark ref elements
				auto arrayType = static_cast<const ArrayType*>(objRef.type());
				if (arrayType->elementType()->isReference()) {
					ArrayRef<PtrValue> arrayRef(objRef.dataPtr());
					for (int i = 0; i < arrayRef.length(); i++) {
						markValue(generation, arrayRef.getElement(i), arrayType->elementType());
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
						markValue(generation, fieldValue, field.type());
					}
				}
			}
		}
	}

	void GarbageCollector::markValue(CollectorGeneration& generation, RegisterValue value, const Type* type) {
		if (type->isReference()) {
			auto objPtr = (BytePtr)value;

			//Don't mark nulls
			if (objPtr == nullptr) {
				return;
			}

			markObject(generation, ObjectRef((RawObjectRef)value));
		}
	}

	void GarbageCollector::markAllObjects(CollectorGeneration& generation, const StackFrame& stackFrame) {
		if (mVMState.config.enableDebug && mVMState.config.printGCStackTrace) {
			std::cout << "Stack trace: " << std::endl;
		}

		StackWalker stackWalker(mVMState);
		stackWalker.visitReferences(stackFrame, [this, &generation](StackFrameEntry frameEntry) {
			markObject(generation, ObjectRef((RawObjectRef) frameEntry.value()));
		}, [this](const StackFrame& currentFrame) {
			if (mVMState.config.enableDebug && mVMState.config.printGCStackTrace) {
				std::cout << currentFrame.function()->def().name() << " (" << currentFrame.instructionIndex() << ")" << std::endl;
				Runtime::Internal::printAliveObjects(currentFrame, "\t");
			}
		});

		//Old objects with references to young objects are also root
		if (isYoung(generation)) {
			mOldGeneration.heap().visitObjects([this](ObjectRef objRef) {
				if (mOldGeneration.cardTable()[mOldGeneration.getCardNumber(objRef.dataPtr())]) {
					markObject(mOldGeneration, objRef);
//					std::cout << "old object " << ptrToString(objRef.dataPtr()) << std::endl;
				}
			});
		}
	}

	void GarbageCollector::sweepObjects(CollectorGeneration& generation) {
		int numDeallocatedObjects = 0;

		generation.heap().visitObjects([&](ObjectRef objRef) {
			if (!objRef.isMarked()) {
				numDeallocatedObjects++;

				if (mVMState.config.enableDebug && mVMState.config.printDeallocation) {
					std::cout << "Deleted object: ";
					printObject(objRef);
				}

				deleteObject(objRef);
			} else {
				objRef.unmark();
			}
		});

		if (mVMState.config.enableDebug && mVMState.config.printGCStats) {
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

	void GarbageCollector::updateStackReferences(const GCRuntimeInformation& runtimeInformation, ForwardingTable& forwardingAddress) {
		StackWalker stackWalker(mVMState);
		stackWalker.visitReferences(
			runtimeInformation.stackFrame,
			[&](StackFrameEntry frameEntry) {
				updateReference(forwardingAddress, (PtrValue*)frameEntry.valuePtr());
			});
	}

	int GarbageCollector::moveObjects(CollectorGeneration& generation, ForwardingTable& forwardingAddress) {
		int numDeallocatedObjects = 0;
		generation.heap().visitObjects([&](ObjectRef objRef) {
			if (objRef.isMarked()) {
				objRef.unmark();
				objRef.increaseSurvivalCount();
				auto dest = forwardingAddress[objRef.fullPtr()];
				std::memmove(dest, objRef.fullPtr(), objRef.fullSize());
			} else {
				numDeallocatedObjects++;

				if (mVMState.config.enableDebug && mVMState.config.printDeallocation) {
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
			std::memmove(newObjPtr, objRef.fullPtr(), objRef.fullSize());
			forwardingAddress.insert({ oldObjPtr, newObjPtr });

			ObjectRef newObjRef(newObjPtr + stackjit::OBJECT_HEADER_SIZE);
			newObjRef.resetSurvivalCount();
			newObjRef.unmark();

			if (mVMState.config.enableDebug && mVMState.config.printGCPromotion) {
				std::cout
					<< "Promoted object " << ptrToString(objRef.dataPtr()) << " (" << objRef.type()->name() << ")"
					<< " to an older generation, new address: "
					<< ptrToString(newObjRef.dataPtr())
					<< std::endl;
			}

			deleteObject(objRef); //Mark as deleted to skip when searching
		}
	}

	void GarbageCollector::compactObjects(CollectorGeneration& generation, CollectorGeneration* nextGeneration, const GCRuntimeInformation& runtimeInformation) {
		ForwardingTable forwardingAddress;
		PromotedObjects promotedObjects;

		//Compute the new locations of the objects
		auto free = computeNewLocations(generation, forwardingAddress, promotedObjects);

		//Promote objects to the next generation
		if (!promotedObjects.empty()) {
			promoteObjects(*nextGeneration, promotedObjects, forwardingAddress);
		}

		//Update the references
		updateStackReferences(runtimeInformation, forwardingAddress);
		updateHeapReferences(generation, forwardingAddress);

		if (!promotedObjects.empty()) {
			updateHeapReferences(*nextGeneration, forwardingAddress);
		}

		//Move the objects
		int numDeallocatedObjects = moveObjects(generation, forwardingAddress);
		generation.heap().setNextAllocation(free);

		if (mVMState.config.enableDebug && mVMState.config.printGCStats) {
			std::cout << "Deallocated: " << numDeallocatedObjects << " objects." << std::endl;
			std::cout << "GC time: " << Helpers::getDuration(mGCStart) << " ms." << std::endl;
		}
	}

	bool GarbageCollector::beginGC(int generationNumber, bool forceGC) {
		if (getGeneration(generationNumber).needsToCollect() || forceGC) {
			if (mVMState.config.enableDebug && mVMState.config.printGCStats) {
				mGCStart = std::chrono::high_resolution_clock::now();
			}

			return true;
		} else {
			return false;
		}
	}

	void GarbageCollector::collect(const GCRuntimeInformation& runtimeInformation, int generationNumber, bool forceGC) {
		auto func = runtimeInformation.stackFrame.function();
		auto instIndex = runtimeInformation.stackFrame.instructionIndex();
		auto& generation = getGeneration(generationNumber);

		if (beginGC(generationNumber, forceGC)) {
			std::size_t startStrLength = 0;

			if (mVMState.config.enableDebug && mVMState.config.printGCPeriod) {
				std::string lines = "------------------------";
				auto startStr = lines + "Start GC (" + std::to_string(generationNumber) + ") in function "
								+ func->def().name() + " (" + std::to_string(instIndex) + ")"
								+ lines;
				std::cout << startStr << std::endl;
				startStrLength = startStr.length();
			}

			if (mVMState.config.enableDebug && mVMState.config.printAliveObjects) {
				std::cout << "Alive objects: " << std::endl;

				generation.heap().visitObjects([this](ObjectRef objRef) {
					printObject(objRef);
				});
				std::cout << std::endl;
			}

			//Mark all objects
			markAllObjects(generation, runtimeInformation.stackFrame);

	//		//Sweep objects
	//		sweepObjects();
	//		mNumAllocated = 0;

			//Compact objects
			compactObjects(generation, &mOldGeneration, runtimeInformation);
			generation.collected();

			if (mVMState.config.enableDebug && mVMState.config.printGCPeriod) {
				printTimes('-', (int)startStrLength / 2 - 3);
				std::cout << "End GC";
				printTimes('-', ((int)startStrLength + 1) / 2 - 3);
				std::cout << std::endl;
			}
		}
	}
}
