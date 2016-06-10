#include "classmetadata.h"
#include "type.h"
#include "../core/functionsignature.h"
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
ClassMetadata::ClassMetadata(std::string name)
	: mName(name), mSize(0), mNextVirtualFunction(0), mVirtualFunctionTable(nullptr) {

}

ClassMetadata::~ClassMetadata() {
	if (mVirtualFunctionTable != nullptr) {
		delete[] mVirtualFunctionTable;
	}
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

void ClassMetadata::addVirtualFunction(const FunctionDefinition& funcDef) {
	auto signature = FunctionSignature::from(funcDef).str();
	mVirtualFunctions.insert({ signature, mNextVirtualFunction++ });
	mIndexToVirtualFunc.push_back(signature);
}

int ClassMetadata::getVirtualFunctionIndex(const FunctionDefinition& funcDef) const {
	auto signature = FunctionSignature::from(funcDef).str();
	if (mVirtualFunctions.count(signature) == 0) {
		throw std::runtime_error("There exists no virtual function '" + signature + "' in the class '" + mName + "'.");
	}

	return mVirtualFunctions.at(signature);
}

std::string ClassMetadata::getVirtualFunctionSignature(int index) const {
	//No bounds checks, we assume that this function is only called by valid indices
	return mIndexToVirtualFunc[index];
}

void ClassMetadata::bindVirtualFunction(const FunctionDefinition& funcDef, unsigned char* funcPtr) {
	if (mVirtualFunctionTable == nullptr) {
		throw std::runtime_error("Virtual function table not created.");
	}

	auto index = getVirtualFunctionIndex(funcDef);
	mVirtualFunctionTable[index] = funcPtr;
}

unsigned char** ClassMetadata::virtualFunctionTable() const {
	return mVirtualFunctionTable;
}

void ClassMetadata::makeFunctionTable() {
	if (mVirtualFunctionTable == nullptr && mVirtualFunctions.size() > 0) {
		mVirtualFunctionTable = new unsigned char*[mVirtualFunctions.size()];
		for (std::size_t i = 0; i < mVirtualFunctions.size(); i++) {
			mVirtualFunctionTable[i] = nullptr;
		}
	}
}

//Provider
void ClassMetadataProvider::add(std::string className, ClassMetadata metadata) {
	if (mClassesMetadata.count(className) == 0) {
		mClassesMetadata.emplace(className, std::move(metadata));
    }
}

bool ClassMetadataProvider::isDefined(std::string className) const {
	return mClassesMetadata.count(className) > 0;
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

void ClassMetadataProvider::createVirtualFunctionTables() {
	for (auto& currentClass : mClassesMetadata) {
		currentClass.second.makeFunctionTable();
	}
}