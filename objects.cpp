#include "objects.h"

ObjectHandle::ObjectHandle(unsigned char* handle, std::size_t objSize, Type* type)
	: handle(handle), objSize(objSize), type(type) {

}

void ObjectHandle::deleteHandle() {
	delete[] handle;
	handle = nullptr;
}

std::size_t ObjectHandle::getSize() const {
	return objSize;
}

const Type* const ObjectHandle::getType() const {
	return type;
}

const unsigned char* ObjectHandle::getHandle() const {
	return handle;
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

ArrayHandle::ArrayHandle(unsigned char* handle, std::size_t objSize, Type* type, int length)
	: ObjectHandle(handle, objSize, type), length(length) {

}

ArrayHandle::ArrayHandle(): ObjectHandle(nullptr, 0, nullptr), length(0) {

}

int ArrayHandle::getLength() const {
	return length;
}

StructHandle::StructHandle(unsigned char* handle, std::size_t objSize, Type* type)
	: ObjectHandle(handle, objSize, type) {

}

StructHandle::StructHandle(): ObjectHandle(nullptr, 0, nullptr) {

}