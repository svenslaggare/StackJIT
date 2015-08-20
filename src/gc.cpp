#include "gc.h"
#include "type.h"
#include "vmstate.h"
#include "objects.h"
#include "amd64.h"
#include "stackjit.h"

#include <iostream>
#include <string.h>

GarbageCollector::GarbageCollector(VMState& vmState)
	: vmState(vmState) {

}

GarbageCollector::~GarbageCollector() {
    for (auto objEntry : mObjects) {
        delete objEntry.second;
    }
}

void GarbageCollector::newObject(ObjectHandle* handle) {
    mObjects.insert({ handle->handle(), handle });
    mNumAllocated++;
}

void GarbageCollector::deleteObject(ObjectHandle* handle) {
    mObjects.erase(handle->handle());
    delete handle;
}

void GarbageCollector::printObject(ObjectHandle* handle) {
    std::cout 
        << "0x" << std::hex << (PtrValue)handle->handle() << std::dec << ": " << handle->size()
        << " bytes (" << handle->type()->name() << ")" << std::endl;
}

unsigned char* GarbageCollector::newArray(const Type* elementType, int length) {
    auto elemSize = TypeSystem::sizeOfType(elementType);

    std::size_t memSize = sizeof(int) + (length * elemSize);
    unsigned char* arrayPtr = new unsigned char[memSize];
    memset(arrayPtr, 0, memSize);

    //Add the array to the list of objects
    newObject(new ArrayHandle(
        arrayPtr,
        memSize,
        vmState.typeProvider().getType(TypeSystem::arrayTypeName(elementType)),
        length));

    //Set the size of the array
    IntToBytes converter;
    converter.intValue = length;
    arrayPtr[0] = converter.byteValues[0];
    arrayPtr[1] = converter.byteValues[1];
    arrayPtr[2] = converter.byteValues[2];
    arrayPtr[3] = converter.byteValues[3];

    if (vmState.enableDebug) {
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
    unsigned char* classPtr = new unsigned char[memSize];
    memset(classPtr, 0, memSize);

    //Add the struct to the list of objects
    newObject(new ClassHandle(classPtr, memSize, classType));

    if (vmState.enableDebug) {
        std::cout
            << "Allocated object (size: " << memSize << " bytes, type: " <<  classType->name()
            << ") at 0x" << std::hex << (PtrValue)classPtr << std::dec
            << std::endl;
    }

    return classPtr;
}

void GarbageCollector::markObject(ObjectHandle* handle) {
    if (!handle->isMarked()) {
        if (TypeSystem::isArray(handle->type())) {
            auto arrayHandle = static_cast<ArrayHandle*>(handle);
            auto arrayType = static_cast<const ArrayType*>(handle->type());

            handle->mark();

            //Mark ref elements
            if (TypeSystem::isReferenceType(arrayType->elementType())) {
                ArrayRef<RegisterValue> arrayRef((unsigned char*)arrayHandle->handle());
                for (int i = 0; i < arrayRef.length(); i++) {
                    markValue(arrayRef.getElement(i), arrayType->elementType());
                }
            }
        } else if (TypeSystem::isClass(handle->type())) {
            handle->mark();

            auto structType = static_cast<const ClassType*>(handle->type());
            auto structMetadata = vmState.classProvider().getMetadata(structType);

            //Mark ref fields
            for (auto fieldEntry : structMetadata.fields()) {
                auto field = fieldEntry.second;

                if (TypeSystem::isReferenceType(field.type())) {
                    RegisterValue fieldValue = *((RegisterValue*)handle->handle() + field.offset());
                    markValue(fieldValue, field.type());
                }
            }
        }
    }
}

void GarbageCollector::markValue(RegisterValue value, const Type* type) {
    if (TypeSystem::isReferenceType(type)) {
        unsigned char* objPtr = (unsigned char*)value;

        //Don't mark nulls
        if (objPtr == nullptr) {
            return;
        }
        
        if (mObjects.count(objPtr) > 0) {
            markObject(mObjects.at(objPtr));
        } else {
            if (vmState.enableDebug) {
                //This should never happen
                std::cout << "Marking invalid object (0x" << std::hex << value << std::dec << ")" << std::endl;
            }
        }
    }
}

void GarbageCollector::sweepObjects() {
    for (auto objEntry : mObjects) {
        auto obj = objEntry.second;

        if (!obj->isMarked()) {
            mObjectsToRemove.push_back(obj);

            if (vmState.enableDebug) {
                std::cout << "Deleted object: ";
                printObject(obj);
            }
        } else {
            obj->unmark();
        }
    }

    for (auto obj : mObjectsToRemove) {
        deleteObject(obj);
    }

    mObjectsToRemove.clear();
}

bool GarbageCollector::beginGC() {
    if (mNumAllocated >= mAllocatedBeforeCollection) {
        if (vmState.enableDebug) {
            std::cout << "Alive objects: " << std::endl;

            for (auto objEntry : mObjects) {
                auto obj = objEntry.second;
                printObject(obj);
            }
        }

        return true;
    } else {
        return false;
    }
}

void GarbageCollector::endGC() {
	sweepObjects();
    mNumAllocated = 0;
}

ObjectHandle* GarbageCollector::getHandle(unsigned char* objectPtr) {
    if (mObjects.count(objectPtr) > 0) {
        return mObjects[objectPtr];
    } else {
        return nullptr;
    }
}

ClassRef GarbageCollector::getClassRef(RawClassRef classRef) {
	auto handle = static_cast<ClassHandle*>(getHandle(classRef));
	auto classType = static_cast<const ClassType*>(handle->type());
	auto& classMetadata = vmState.classProvider().getMetadata(classType->className());
	return ClassRef(handle, classMetadata);
}