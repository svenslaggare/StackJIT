#include "stringref.h"
#include "../runtime.h"

namespace stackjit {
	StringRef::StringRef(RawClassRef stringRef) {
		auto charsField = (char**)(stringRef + sCharsFieldOffset);
		auto chars = *charsField;

		if (chars == nullptr) {
			Runtime::nullReferenceError();
		}

		ArrayRef<char> charsArray((unsigned char*)(chars));
		mChars = charsArray.elementsPtr();
		mLength = charsArray.length();
	}

	std::size_t StringRef::sCharsFieldOffset;
	const ArrayType* StringRef::sCharArrayType;
	const ClassType* StringRef::sStringType;

	const ArrayType* StringRef::charArrayType() {
		return sCharArrayType;
	}

	const ClassType* StringRef::stringType() {
		return sStringType;
	}

	void StringRef::setCharsField(RawClassRef stringRef, char* value) {
		*(char**)(stringRef + sCharsFieldOffset) = value;
	}

	void StringRef::initialize(VMState& vmState) {
		auto& classMetadata = vmState.classProvider().getMetadata("std.String");
		auto& typeProvider = vmState.typeProvider();

		auto charType = typeProvider.makeType(TypeSystem::toString(PrimitiveTypes::Char));

		sCharsFieldOffset = classMetadata.fields().at("chars").offset();
		sStringType = static_cast<const ClassType*>(typeProvider.makeType(TypeSystem::stringTypeName));
		sCharArrayType = static_cast<const ArrayType*>(typeProvider.makeType(TypeSystem::arrayTypeName(charType)));
	}
}
