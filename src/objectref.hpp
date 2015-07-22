#include "objects.h"
#include "classmetadata.h"
#include "type.h"

//Field ref
template<typename T>
FieldRef<T>::FieldRef(unsigned char* fieldPtr)
	: mFieldPtr((T*)fieldPtr) {

}

template<typename T>
T* FieldRef<T>::value() {
	return mFieldPtr;
}

//Struct ref
template<typename T>
FieldRef<T> StructRef::getField(std::string name, const Type* type) {
	if (mMetadata.fields().count(name) > 0) {
		auto& fieldRef = mMetadata.fields().at(name);

		if (*fieldRef.type() != *type) {
			throw std::runtime_error(
				"Expected field to be of type '" + type->name() + "' but got type '" + fieldRef.type()->name() + "'.");
		}

		return FieldRef<T>((unsigned char*)mHandle->handle() + (std::size_t)fieldRef.offset());
	} else {
		throw std::runtime_error(
			"There exists no field called '" + name + "' in the struct '" + mHandle->type()->name() + "'.");
	}
}

//Element ref
template<typename T>
ElementRef<T>::ElementRef(unsigned char* elementPtr, int index)
	: mElementPtr((T*)elementPtr), mIndex(index) {

}

template<typename T>
T* ElementRef<T>::value() {
	return mElementPtr;
}

template<typename T>
int ElementRef<T>::index() const {
	return mIndex;
}

//Array ref
template<typename T>
ArrayRef<T>::ArrayRef(ArrayHandle* handle)
	: mHandle(handle), mLength(handle->length()) {

}

template<typename T>
ElementRef<T> ArrayRef<T>::getElement(int index) {
	if (index >= 0 && index < mLength) {
		return ElementRef<T>((unsigned char*)mHandle->handle() + sizeof(T) * index + 4, index);
	} else {
		throw std::runtime_error("Array index is out of bounds.");
	}
}

template<typename T>
int ArrayRef<T>::length() const {
	return mLength;
}