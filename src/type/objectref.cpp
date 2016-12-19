#include "objectref.h"

namespace stackjit {
	//Object ref
	ObjectRef::ObjectRef(RawObjectRef objRef)
		: mPtr(objRef - stackjit::OBJECT_HEADER_SIZE), mType(*((const Type**)mPtr)) {
		if (type()->isArray()) {
			auto arrayType = static_cast<const ArrayType*>(type());
			auto elementType = arrayType->elementType();
			auto elemSize = TypeSystem::sizeOfType(elementType);
			auto length = *(int*)dataPtr();
			mSize = stackjit::ARRAY_LENGTH_SIZE + (length * elemSize);
		} else {
			mSize = static_cast<const ClassType*>(type())->metadata()->size();
		}
	}
	unsigned char* ObjectRef::fullPtr() const {
		return mPtr;
	}

	unsigned char* ObjectRef::dataPtr() const {
		return mPtr + sizeof(PtrValue) + 1;
	}

	std::size_t ObjectRef::size() const {
		return mSize;
	}

	std::size_t ObjectRef::fullSize() const {
		return size() + stackjit::OBJECT_HEADER_SIZE;
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
}
