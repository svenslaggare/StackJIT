#include "objectref.h"

namespace stackjit {
	//Object ref
	ObjectRef::ObjectRef(RawObjectRef objRef)
		: mPtr(objRef - stackjit::OBJECT_HEADER_SIZE), mType(*((const Type**)mPtr)) {
		if (type()->isArray()) {
			auto arrayType = static_cast<const ArrayType*>(type());
			auto elementType = arrayType->elementType();
			auto elementSize = TypeSystem::sizeOfType(elementType);
			auto length = *(int*)dataPtr();
			mSize = stackjit::ARRAY_LENGTH_SIZE + (length * elementSize);
		} else {
			mSize = static_cast<const ClassType*>(type())->metadata()->size();
		}
	}

	BytePtr ObjectRef::fullPtr() const {
		return mPtr;
	}

	BytePtr ObjectRef::dataPtr() const {
		return mPtr + sizeof(PtrValue) + 1;
	}

	std::size_t ObjectRef::size() const {
		return mSize;
	}

	std::size_t ObjectRef::fullSize() const {
		return size() + stackjit::OBJECT_HEADER_SIZE;
	}

	void ObjectRef::setGCInfo(bool isMarked, int count) {
		int gcInfo = isMarked | (count << 1);
		mPtr[sizeof(PtrValue)] = (unsigned char)gcInfo;
	}

	void ObjectRef::setMarked(bool isMarked) {
		setGCInfo(isMarked, survivalCount());
	}

	bool ObjectRef::isMarked() const {
		return (bool)(mPtr[sizeof(PtrValue)] & 0x1);
	}

	void ObjectRef::mark() {
		setMarked(true);
	}

	void ObjectRef::unmark() {
		setMarked(false);
	}

	int ObjectRef::survivalCount() const {
		return ((mPtr[sizeof(PtrValue)] >> 1) & 0x7f);
	}

	void ObjectRef::increaseSurvivalCount() {
		int nextCount = survivalCount() + 1;
		if (nextCount > 127) {
			nextCount = 127;
		}

		setGCInfo(isMarked(), nextCount);
	}

	void ObjectRef::resetSurvivalCount() {
		setGCInfo(isMarked(), 0);
	}

	//Class ref
	ClassRef::ClassRef(ObjectRef objRef, const ClassMetadata& metadata)
		: mObjRef(objRef), mMetadata(metadata) {

	}
}
