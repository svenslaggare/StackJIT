#include "classmetadata.h"
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

//Class metadata
ClassMetadata::ClassMetadata(std::vector<std::pair<std::string, const Type*>> fields)
	: mSize(0) {
	for (auto field : fields) {
		mFields.insert({ field.first, Field(field.second, mSize) });
		mSize += TypeSystem::sizeOfType(field.second);
	}
}

ClassMetadata::ClassMetadata()
	: mSize(0) {

}

std::size_t ClassMetadata::size() const {
	return mSize;
}

const std::unordered_map<std::string, Field>& ClassMetadata::fields() const {
	return mFields;
}

void ClassMetadata::addField(std::string name, const Type* type) {
	mFields.insert({ name, Field(type, mSize) });
	mSize += TypeSystem::sizeOfType(type);
}

//Provider
void ClassMetadataProvider::add(std::string structName, ClassMetadata classMe) {
	if (mClassesMetadata.count(structName) == 0) {
        mClassesMetadata[structName] = classMe;
    }
}

bool ClassMetadataProvider::isDefined(std::string structName) const {
	return mClassesMetadata.count(structName) > 0;
}

const ClassMetadata& ClassMetadataProvider::operator[](std::string className) const {
	if (mClassesMetadata.count(className) > 0) {
        return mClassesMetadata.at(className);
    } else {
        throw std::out_of_range("The class isn't defined.");
    }
}

ClassMetadata& ClassMetadataProvider::operator[](std::string className) {
	if (mClassesMetadata.count(className) > 0) {
		return mClassesMetadata.at(className);
	} else {
		throw std::out_of_range("The class isn't defined.");
	}
}

const ClassMetadata& ClassMetadataProvider::metadataFor(const ClassType* classType) const {
	return operator[](classType->className());
}