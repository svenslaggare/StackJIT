#include "objectref.h"

//Object ref
ObjectRef::ObjectRef(RawObjectRef objRef)
	: mPtr(objRef - StackJIT::OBJECT_HEADER_SIZE), mType(*((const Type**)mPtr)) {
	if (TypeSystem::isArray(type())) {
		auto arrayType = static_cast<const ArrayType*>(type());
		auto elementType = arrayType->elementType();
		auto elemSize = TypeSystem::sizeOfType(elementType);
		auto length = *(int*)objectPtr();
		mObjectSize = StackJIT::ARRAY_LENGTH_SIZE + (length * elemSize);
	} else {
		mObjectSize = static_cast<const ClassType*>(type())->classMetadata()->size();
	}
}

const Type* ObjectRef::type() const {
	return mType;
}

unsigned char* ObjectRef::objectPtr() const {
	return mPtr + sizeof(PtrValue) + 1;
}

std::size_t ObjectRef::objectSize() const {
	return mObjectSize;
}

std::size_t ObjectRef::fullObjectSize() const {
	return objectSize() + StackJIT::OBJECT_HEADER_SIZE;
}

void ObjectRef::setMarked(bool isMarked) {
	mPtr[sizeof(PtrValue)] = (unsigned char)isMarked;
}

bool ObjectRef::isMarked() const {
	return (bool)mPtr[sizeof(PtrValue)];
}

void ObjectRef::mark() {
	setMarked(true);
}

void ObjectRef::unmark() {
	setMarked(false);
}

//Class ref
ClassRef::ClassRef(ObjectRef objRef, const ClassMetadata& metadata)
	: mObjRef(objRef), mMetadata(metadata) {

}