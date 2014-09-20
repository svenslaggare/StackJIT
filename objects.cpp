#include "objects.h"

ArrayHandle::ArrayHandle(int size, Type* type, unsigned char* handle)
	: size(size), type(type), handle(handle) {

}

ArrayHandle::ArrayHandle() : size(0), type(nullptr), handle(nullptr) {

}

void ArrayHandle::deleteHandle() {
	delete[] handle;
}

const unsigned char* ArrayHandle::getHandle() const {
	return handle;
}