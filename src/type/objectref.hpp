#include "../type/classmetadata.h"
#include "../type/type.h"
#include "../stackjit.h"

namespace stackjit {
	//Field ref
	template<typename T>
	FieldRef<T>::FieldRef(unsigned char* fieldPtr)
		: mFieldPtr((T*)fieldPtr) {

	}

	template<typename T>
	T* FieldRef<T>::value() {
		return mFieldPtr;
	}

	//Class ref
	template<typename T>
	FieldRef<T> ClassRef::getField(std::string name, const Type* type) {
		if (mMetadata.fields().count(name) > 0) {
			auto& fieldRef = mMetadata.fields().at(name);

			if (*fieldRef.type() != *type) {
				throw std::runtime_error(
					"Expected field to be of type '" + type->name() + "' but got type '" + fieldRef.type()->name() + "'.");
			}

			return FieldRef<T>(mObjRef.dataPtr() + (std::size_t)fieldRef.offset());
		} else {
			throw std::runtime_error(
				"There exists no field called '" + name + "' in the class '" + mObjRef.type()->name() + "'.");
		}
	}

	//Array ref
	template<typename T>
	ArrayRef<T>::ArrayRef(const RawArrayRef arrayRef)
		: mElementsPtr((T*)(arrayRef + stackjit::ARRAY_LENGTH_SIZE)), mLength(*(int*)arrayRef) {

	}

	template<typename T>
	T* ArrayRef<T>::elementsPtr() const {
		return mElementsPtr;
	}

	template<typename T>
	T ArrayRef<T>::getElement(int index) const {
		return mElementsPtr[index];
	}

	template<typename T>
	int ArrayRef<T>::length() const {
		return mLength;
	}
}
