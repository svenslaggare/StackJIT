#include "gc.h"
#include "../type/type.h"
#include "../vmstate.h"
#include "../compiler/amd64.h"
#include "../stackjit.h"
#include "../helpers.h"
#include "stackframe.h"
#include "runtime.h"
#include <iostream>
#include <string.h>

namespace {
	void printTimes(char c, int times) {
		for (int i = 0; i < times; i++) {
			std::cout << c;
		}
	}
}

GCRuntimeInformation::GCRuntimeInformation(RegisterValue* basePtr, ManagedFunction* function, int instIndex)
	: basePtr(basePtr), function(function), instIndex(instIndex) {

}

GarbageCollector::GarbageCollector(VMState& vmState)
	: vmState(vmState), mHeap(10 * 1024 * 1024) {

}

void GarbageCollector::initialize() {
	mAllocatedBeforeCollection = (std::size_t)vmState.allocationsBeforeGC;
}

void GarbageCollector::printObject(ObjectRef objRef) {
	std::cout
	<< "0x" << std::hex << (PtrValue)objRef.dataPtr() << std::dec << ": " << objRef.size()
	<< " bytes (" << objRef.type()->name() << ")"
	<< std::endl;
}

unsigned char* GarbageCollector::allocateObject(ManagedHeap& heap, const Type* type, std::size_t size) {
	auto fullSize = StackJIT::OBJECT_HEADER_SIZE + size;
	auto objPtr = heap.allocate(fullSize);

	if (objPtr == nullptr) {
		throw std::runtime_error("Could not allocate object.");
	}

	memset(objPtr, 0, fullSize);

	//Set the header
	Helpers::setValue(objPtr, 0, (PtrValue)type);
	Helpers::setValue(objPtr, sizeof(PtrValue), 0); //GC info

	mNumAllocated++;

	//The returned ptr is to the data
	return objPtr + StackJIT::OBJECT_HEADER_SIZE;
}

void GarbageCollector::deleteObject(ManagedHeap& heap, ObjectRef objRef) {
	//TODO: We just do some temp deleting, so that the object is avoided when visiting the objects.
	auto fullPtr = objRef.dataPtr() - StackJIT::OBJECT_HEADER_SIZE;
	Helpers::setValue<std::size_t>(fullPtr, 0, objRef.fullSize());  //The amount of data to skip from the start.
	Helpers::setValue<unsigned char>(fullPtr, sizeof(std::size_t), 0xFF); //Indicator for dead object
}

unsigned char* GarbageCollector::newArray(const ArrayType* arrayType, int length) {
    auto elementType = arrayType->elementType();
    auto elemSize = TypeSystem::sizeOfType(elementType);

    std::size_t memSize = StackJIT::ARRAY_LENGTH_SIZE + (length * elemSize);
    auto arrayPtr = allocateObject(mHeap, arrayType, memSize);

    //Set the length of the array
	Helpers::setValue(arrayPtr, 0, length);

    if (vmState.enableDebug && vmState.printAllocation) {
        std::cout
            << "Allocated array ("
            << "size: " << memSize << " bytes, "
			<< "length: " << length << ", type: " << elementType->name()
            << ") at 0x" << std::hex << (PtrValue)arrayPtr << std::dec
            << std::endl;
    }

    return arrayPtr;
}

unsigned char* GarbageCollector::newClass(const ClassType* classType) {
    std::size_t memSize = classType->classMetadata()->size();
    auto classPtr = allocateObject(mHeap, classType, memSize);

    if (vmState.enableDebug && vmState.printAllocation) {
        std::cout
            << "Allocated object (size: " << memSize << " bytes, type: " <<  classType->name()
            << ") at 0x" << std::hex << (PtrValue)classPtr << std::dec
            << std::endl;
    }

    return classPtr;
}

void GarbageCollector::visitFrameReference(StackFrameEntry frameEntry, VisitReferenceFn fn) {
	if (TypeSystem::isReferenceType(frameEntry.type())) {
		auto objPtr = (unsigned char*)frameEntry.value();

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

void GarbageCollector::visitAllFrameReferences(RegisterValue* basePtr, ManagedFunction* func, int instIndex,
											   VisitReferenceFn fn, VisitFrameFn frameFn) {
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
		if (TypeSystem::isArray(objRef.type())) {
			objRef.mark();

			auto arrayType = static_cast<const ArrayType*>(objRef.type());

			//Mark ref elements
			if (TypeSystem::isReferenceType(arrayType->elementType())) {
				ArrayRef<PtrValue> arrayRef(objRef.dataPtr());
				for (int i = 0; i < arrayRef.length(); i++) {
					markValue(arrayRef.getElement(i), arrayType->elementType());
				}
			}
		} else if (TypeSystem::isClass(objRef.type())) {
			objRef.mark();

			auto classType = static_cast<const ClassType*>(objRef.type());
			auto& classMetadata = vmState.classProvider().getMetadata(classType->className());

			//Mark ref fields
			for (auto fieldEntry : classMetadata.fields()) {
				auto field = fieldEntry.second;

				if (TypeSystem::isReferenceType(field.type())) {
					RegisterValue fieldValue = *(PtrValue*)(objRef.dataPtr() + field.offset());
					markValue(fieldValue, field.type());
				}
			}
		}
	}
}

void GarbageCollector::markValue(RegisterValue value, const Type* type) {
	if (TypeSystem::isReferenceType(type)) {
		auto objPtr = (unsigned char*)value;

		//Don't mark nulls
		if (objPtr == nullptr) {
			return;
		}

		markObject(ObjectRef((RawObjectRef)value));
	}
}

void GarbageCollector::markAllObjects(RegisterValue* basePtr, ManagedFunction* func, int instIndex) {
	if (vmState.enableDebug && vmState.printGCStackTrace) {
		std::cout << "Stack trace: " << std::endl;
	}

	visitAllFrameReferences(basePtr, func, instIndex, [this](StackFrameEntry frameEntry) {
		markObject(ObjectRef((RawObjectRef)frameEntry.value()));
	}, [this](RegisterValue* frameBasePtr, ManagedFunction* frameFunc, int frameCallPoint) {
		if (vmState.enableDebug && vmState.printGCStackTrace) {
			std::cout << frameFunc->def().name() << " (" << frameCallPoint << ")" << std::endl;
			Runtime::Internal::printAliveObjects(frameBasePtr, frameFunc, frameCallPoint, "\t");
		}
	});
}

void GarbageCollector::sweepObjects() {
	int numDeallocatedObjects = 0;

	mHeap.visitObjects([&](ObjectRef objRef) {
		if (!objRef.isMarked()) {
			numDeallocatedObjects++;

			if (vmState.enableDebug && vmState.printDeallocation) {
				std::cout << "Deleted object: ";
				printObject(objRef);
			}

			deleteObject(mHeap, objRef);
		} else {
			objRef.unmark();
		}
	});

	if (vmState.enableDebug && vmState.printGCStats) {
		std::cout << "Deallocated: " << numDeallocatedObjects << " objects." << std::endl;
		std::cout << "GC time: " << Helpers::getDuration(mGCStart) << " ms." << std::endl;
	}
}

bool GarbageCollector::beginGC(bool forceGC) {
	if (mNumAllocated >= mAllocatedBeforeCollection || forceGC) {
		if (vmState.enableDebug && vmState.printAliveObjects) {
			std::cout << "Alive objects: " << std::endl;

			mHeap.visitObjects([this](ObjectRef objRef) {
				printObject(objRef);
			});
		}

		if (vmState.enableDebug && vmState.printGCStats) {
			mGCStart = std::chrono::high_resolution_clock::now();
		}

		return true;
	} else {
		return false;
	}
}

void GarbageCollector::collect(GCRuntimeInformation& runtimeInformation) {
	auto basePtr = runtimeInformation.basePtr;
	auto func = runtimeInformation.function;
	auto instIndex = runtimeInformation.instIndex;

	if (beginGC()) {
		std::size_t startStrLength = 0;

		if (vmState.enableDebug && vmState.printGCPeriod) {
			auto startStr = "---------------Start GC in func " + func->def().name() + " (" + std::to_string(instIndex) +
							")---------------";
			std::cout << startStr << std::endl;
			startStrLength = startStr.length();
		}

		//Mark all objects
		markAllObjects(basePtr, func, instIndex);

		//Sweep objects
		sweepObjects();
		mNumAllocated = 0;

		if (vmState.enableDebug && vmState.printGCPeriod) {
			printTimes('-', (int)startStrLength / 2 - 3);
			std::cout << "End GC";
			printTimes('-', ((int)startStrLength + 1) / 2 - 3);
			std::cout << std::endl;
		}
	}
}

ClassRef GarbageCollector::getClassRef(RawClassRef classRef) {
	ObjectRef objRef(classRef);
	auto classType = static_cast<const ClassType*>(objRef.type());
	auto& classMetadata = vmState.classProvider().getMetadata(classType->className());
	return ClassRef(objRef, classMetadata);
}