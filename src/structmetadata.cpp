#include "structmetadata.h"
#include "type.h"

Field::Field(const Type* type, std::size_t offset)
	: type(type), offset(offset) {

}

StructMetadata::StructMetadata(std::map<std::string, const Type*> fields)
	: mSize(0) {
	for (auto field : fields) {
		mFields.insert({ field.first, Field(field.second, mSize) });
		mSize += TypeSystem::sizeOfType(field.second);
	}
}

StructMetadata::StructMetadata()
	: mSize(0) {

}

const Type* StructMetadata::getField(std::string fieldName) const {
	if (mFields.count(fieldName) > 0) {
		return mFields.at(fieldName).type;
	} else {
		return nullptr;
	}
}

std::size_t StructMetadata::fieldOffset(std::string fieldName) const {
	if (mFields.count(fieldName) > 0) {
		return mFields.at(fieldName).offset;
	} else {
		throw std::out_of_range("The given field doesn't exist in the current type.");
	}
}

std::size_t StructMetadata::size() const {
	return mSize;
}

const std::map<std::string, Field>& StructMetadata::fields() const {
	return mFields;
}