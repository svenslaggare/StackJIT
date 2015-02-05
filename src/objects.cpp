#include "objects.h"

ObjectHandle::ObjectHandle(unsigned char* handle, std::size_t size, const Type* type)
	: mHandle(handle), mSize(size), mType(type) {
	if (handle == nullptr) {
		throw std::invalid_argument("handle");
	}
}

ObjectHandle::~ObjectHandle() {
	delete[] mHandle;
	mHandle = nullptr;
	mSize = 0;
}

std::size_t ObjectHandle::size() const {
	return mSize;
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

ArrayHandle::ArrayHandle(unsigned char* handle, std::size_t size, const Type* type, int length)
	: ObjectHandle(handle, size, type), mLength(length) {

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