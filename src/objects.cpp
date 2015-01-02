#include "objects.h"

ObjectHandle::ObjectHandle(unsigned char* handle, std::size_t objSize, const Type* type)
	: mHandle(handle), mObjSize(objSize), mType(type) {
	if (handle == nullptr) {
		throw std::invalid_argument("handle");
	}
}

ObjectHandle::~ObjectHandle() {
	deleteHandle();
}

void ObjectHandle::deleteHandle() {
	delete[] mHandle;
	mHandle = nullptr;
	mObjSize = 0;
}

std::size_t ObjectHandle::size() const {
	return mObjSize;
}

const Type* ObjectHandle::type() const {
	return mType;
}

const unsigned char* ObjectHandle::handle() const {
	return mHandle;
}

bool ObjectHandle::isMarked() const {
	return mIsMarked;
}

void ObjectHandle::mark() {
	mIsMarked = true;
}

void ObjectHandle::unmark() {
	mIsMarked = false;
}

ArrayHandle::ArrayHandle(unsigned char* handle, std::size_t objSize, const Type* type, int length)
	: ObjectHandle(handle, objSize, type), mLength(length) {

}

ArrayHandle::ArrayHandle(): ObjectHandle(nullptr, 0, nullptr), mLength(0) {

}

int ArrayHandle::length() const {
	return mLength;
}

StructHandle::StructHandle(unsigned char* handle, std::size_t objSize, const Type* type)
	: ObjectHandle(handle, objSize, type) {

}

StructHandle::StructHandle(): ObjectHandle(nullptr, 0, nullptr) {

}