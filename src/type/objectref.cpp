#include "objectref.h"

//Object ref
ObjectRef::ObjectRef(RawObjectRef objRef)
	: mPtr(objRef - (sizeof(PtrValue) + 1)), mType(*((const Type**)mPtr)) {

}

const Type* ObjectRef::type() const {
	return mType;
}

unsigned char* ObjectRef::objectPtr() {
	return mPtr + sizeof(PtrValue) + 1;
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