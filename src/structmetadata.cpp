#include "structmetadata.h"
#include "type.h"

//Field
Field::Field(const Type* type, std::size_t offset)
	: mType(type), mOffset(offset) {

}

const Type* Field::type() const {
	return mType;
}

const std::size_t Field::offset() const {
	return mOffset;
}

//Struct metadata
StructMetadata::StructMetadata(std::vector<std::pair<std::string, const Type*>> fields)
	: mSize(0) {
	for (auto field : fields) {
		mFields.insert({ field.first, Field(field.second, mSize) });
		mSize += TypeSystem::sizeOfType(field.second);
	}
}

StructMetadata::StructMetadata()
	: mSize(0) {

}

std::size_t StructMetadata::size() const {
	return mSize;
}

const std::unordered_map<std::string, Field>& StructMetadata::fields() const {
	return mFields;
}

void StructMetadata::addField(std::string name, const Type* type) {
	mFields.insert({ name, Field(type, mSize) });
	mSize += TypeSystem::sizeOfType(type);
}

//Provider
void StructMetadataProvider::add(std::string structName, StructMetadata structMetadata) {
	if (mStructsMetadata.count(structName) == 0) {
        mStructsMetadata[structName] = structMetadata;
    }
}

bool StructMetadataProvider::isDefined(std::string structName) const {
	return mStructsMetadata.count(structName) > 0;
}

const StructMetadata& StructMetadataProvider::operator[](std::string structName) const {
	if (mStructsMetadata.count(structName) > 0) {
        return mStructsMetadata.at(structName);
    } else {
        throw std::out_of_range("The struct isn't defined.");
    }
}

StructMetadata& StructMetadataProvider::operator[](std::string structName) {
	if (mStructsMetadata.count(structName) > 0) {
		return mStructsMetadata.at(structName);
	} else {
		throw std::out_of_range("The struct isn't defined.");
	}
}

const StructMetadata& StructMetadataProvider::metadataFor(const StructType* structType) const {
	return operator[](structType->structName());
}