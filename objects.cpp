#include "objects.h"

ArrayHandle::ArrayHandle(int size, int* elements)
	: Size(size), Elements(elements)
{
	handle = ((unsigned char*)elements) - 4;
}

ArrayHandle::ArrayHandle() : Size(0), Elements(nullptr)
{

}

void ArrayHandle::deleteHandle() {
	delete[] handle;
}

const unsigned char* ArrayHandle::getHandle() {
	return handle;
}