#include "classmetadata.h"
#include "type.h"
#include "../core/functionsignature.h"
#include "../vmstate.h"
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
	: mName(name),
	  mSize(0),
	  mParentClass(nullptr),
	  mVirtualFunctionTable(nullptr) {

}

ClassMetadata::~ClassMetadata() {
	if (mVirtualFunctionTable != nullptr) {
		delete[] mVirtualFunctionTable;
	}
}

std::string ClassMetadata::name() const {
	return mName;
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

const ClassType* ClassMetadata::parentClass() const {
	return mParentClass;
}

void ClassMetadata::setParentClass(const ClassType* parentClass) {
	if (mParentClass != nullptr) {
		throw std::runtime_error("The parent class has already been set.");
	}

	this->mParentClass = parentClass;
}

const std::vector<std::string>& ClassMetadata::virtualFunctions() const {
	return mIndexToVirtualFunction;
}

void ClassMetadata::addVirtualFunction(const FunctionDefinition& funcDef) {
	mVirtualFunctions.push_back(FunctionSignature::from(funcDef).str());
}

int ClassMetadata::getVirtualFunctionIndex(const FunctionDefinition& funcDef) const {
	auto signature = FunctionSignature::from(funcDef).str();
	if (mVirtualFunctionToIndex.count(signature) == 0) {
		throw std::runtime_error("There exists no virtual function '" + signature + "' in the class '" + mName + "'.");
	}

	return mVirtualFunctionToIndex.at(signature);
}

std::string ClassMetadata::getVirtualFunctionSignature(int index) const {
	//No bounds checks, we assume that this function is only called with valid indices
	return mIndexToVirtualFunction[index];
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

void ClassMetadata::makeVirtualFunctionTable() {
	if (mVirtualFunctionTable == nullptr) {
		int virtualFuncIndex = 0;

		//Create for parent class
		if (mParentClass != nullptr) {
			mParentClass->metadata()->makeVirtualFunctionTable();

			//Add the parent class virtual functions
			for (auto& virtualFunc : mParentClass->metadata()->mIndexToVirtualFunction) {
				mIndexToVirtualFunction.push_back(virtualFunc);
				mVirtualFunctionToIndex.insert({ virtualFunc, virtualFuncIndex });
				virtualFuncIndex++;
			}
		}

		//Now for this class
		for (auto& virtualFunc : mVirtualFunctions) {
			mIndexToVirtualFunction.push_back(virtualFunc);
			mVirtualFunctionToIndex.insert({ virtualFunc, virtualFuncIndex });
			virtualFuncIndex++;
		}

		//Create the actual table. Note that these functions are bound when compiled.
		mVirtualFunctionTable = new unsigned char*[mIndexToVirtualFunction.size()];
		for (std::size_t i = 0; i < mIndexToVirtualFunction.size(); i++) {
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

void ClassMetadataProvider::createVirtualFunctionTables(const VMState& vmState) {
	for (auto& current : mClassesMetadata) {
		auto& currentClass = current.second;
		currentClass.makeVirtualFunctionTable();

		if (vmState.enableDebug && vmState.printVirtualFunctionTableLayout) {
			std::cout << "V-table for " << currentClass.name() << std::endl;

			std::size_t i = 0;
			for (auto& virtualFunc : currentClass.virtualFunctions()) {
				std::cout << i << ": " << virtualFunc << std::endl;
				i++;
			}

			std::cout << std::endl;
		}
	}
}