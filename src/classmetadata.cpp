#include "classmetadata.h"
#include "type.h"
#include <stdexcept>

//Field
Field::Field(const Type* type, std::size_t offset, AccessModifier accessModifier)
	: mType(type), mOffset(offset), mAccessModifier(accessModifier) {

}

const Type* Field::type() const {
	return mType;
}

const std::size_t Field::offset() const {
	return mOffset;
}

const AccessModifier Field::accessModifier() const {
	return mAccessModifier;
}

bool fromString(std::string str, AccessModifier& accessModifier) {
	if (str == "public") {
		accessModifier = AccessModifier::Public;
		return true;
	} else if (str == "private") {
		accessModifier = AccessModifier::Private;
		return true;
	}

	return false;
}

//Class metadata
ClassMetadata::ClassMetadata()
	: mSize(0) {

}

std::size_t ClassMetadata::size() const {
	return mSize;
}

const std::unordered_map<std::string, Field>& ClassMetadata::fields() const {
	return mFields;
}

void ClassMetadata::addField(std::string name, const Type* type, AccessModifier accessModifier) {
	mFields.insert({ name, Field(type, mSize, accessModifier) });
	mSize += TypeSystem::sizeOfType(type);
}

//Provider
void ClassMetadataProvider::add(std::string className, ClassMetadata metadata) {
	if (mClassesMetadata.count(className) == 0) {
        mClassesMetadata[className] = metadata;
    }
}

bool ClassMetadataProvider::isDefined(std::string structName) const {
	return mClassesMetadata.count(structName) > 0;
}

const ClassMetadata& ClassMetadataProvider::getMetadata(std::string className) const {
	if (mClassesMetadata.count(className) > 0) {
        return mClassesMetadata.at(className);
    } else {
        throw std::out_of_range("The class isn't defined.");
    }
}

ClassMetadata& ClassMetadataProvider::getMetadata(std::string className) {
	if (mClassesMetadata.count(className) > 0) {
		return mClassesMetadata.at(className);
	} else {
		throw std::out_of_range("The class isn't defined.");
	}
}

const ClassMetadata& ClassMetadataProvider::getMetadata(const ClassType* classType) const {
	return getMetadata(classType->className());
}