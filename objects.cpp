#include "objects.h"

ArrayHandle::ArrayHandle(int size, int* elements)
	: size(size), elements(elements) {
	handle = ((unsigned char*)elements) - 4;
}

ArrayHandle::ArrayHandle() : size(0), elements(nullptr)
{

}

void ArrayHandle::deleteHandle() {
	delete[] handle;
}

const unsigned char* ArrayHandle::getHandle() const {
	return handle;
}