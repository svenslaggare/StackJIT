#include "gc.h"
#include "../type/type.h"
#include "../vmstate.h"
#include "../type/objects.h"
#include "../compiler/amd64.h"
#include "../stackjit.h"
#include "../helpers.h"
#include <iostream>
#include <string.h>

GarbageCollector::GarbageCollector(VMState& vmState)
	: vmState(vmState), mYoungGeneration(2 * 1024 * 1024), mOldGeneration(8 * 1024 * 1024) {

}

void GarbageCollector::initialize() {

}

unsigned char* GarbageCollector::allocateObject(ManagedHeap& heap, const Type* type, std::size_t size) {
	auto fullObjSize = sizeof(PtrValue) + 1 + size;
	auto objPtr = heap.allocate(fullObjSize);

	if (objPtr == nullptr) {
		throw std::runtime_error("Could not allocate object.");
	}

	memset(objPtr, 0, fullObjSize);

	//Set the header
	Helpers::setValue(objPtr, 0, (PtrValue)type);
	Helpers::setValue(objPtr, sizeof(PtrValue), 0); //GC info

	//The returned ptr is to the data
	return objPtr + sizeof(PtrValue) + 1;
}

unsigned char* GarbageCollector::newArray(const ArrayType* arrayType, int length) {
    auto elementType = arrayType->elementType();
    auto elemSize = TypeSystem::sizeOfType(elementType);

    std::size_t memSize = sizeof(int) + (length * elemSize);
    auto arrayPtr = allocateObject(mYoungGeneration, arrayType, memSize);

    //Set the size of the array
    IntToBytes converter;
    converter.intValue = length;
    arrayPtr[0] = converter.byteValues[0];
    arrayPtr[1] = converter.byteValues[1];
    arrayPtr[2] = converter.byteValues[2];
    arrayPtr[3] = converter.byteValues[3];

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
    std::size_t memSize = vmState.classProvider().getMetadata(classType->className()).size();
    auto classPtr = allocateObject(mYoungGeneration, classType, memSize);

    if (vmState.enableDebug && vmState.printAllocation) {
        std::cout
            << "Allocated object (size: " << memSize << " bytes, type: " <<  classType->name()
            << ") at 0x" << std::hex << (PtrValue)classPtr << std::dec
            << std::endl;
    }

    return classPtr;
}

ClassRef GarbageCollector::getClassRef(RawClassRef classRef) {
	ObjectRef objRef(classRef);
	auto classType = static_cast<const ClassType*>(objRef.type());
	auto& classMetadata = vmState.classProvider().getMetadata(classType->className());
	return ClassRef(objRef, classMetadata);
}