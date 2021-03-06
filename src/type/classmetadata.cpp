#include "classmetadata.h"
#include "type.h"
#include "../core/functionsignature.h"
#include "../vmstate.h"
#include <stdexcept>
#include <algorithm>

namespace stackjit {
	//Field
	Field::Field(const Type* type, std::size_t offset, AccessModifier accessModifier, bool isDefined)
		: mType(type), mOffset(offset), mAccessModifier(accessModifier), mIsDefined(isDefined) {

	}

	const Type* Field::type() const {
		return mType;
	}

	std::size_t Field::offset() const {
		return mOffset;
	}

	AccessModifier Field::accessModifier() const {
		return mAccessModifier;
	}

	bool Field::isDefined() const {
		return mIsDefined;
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

	std::string toString(const AccessModifier& accessModifier) {
		switch (accessModifier) {
			case AccessModifier::Private:
				return "private";
			case AccessModifier::Public:
				return "public";
			default:
				return "";
		}
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

	const std::string& ClassMetadata::name() const {
		return mName;
	}

	std::size_t ClassMetadata::size() const {
		return mSize;
	}

	const std::unordered_map<std::string, Field>& ClassMetadata::fields() const {
		return mFields;
	}

	bool ClassMetadata::fieldExists(const std::string& name) const {
		return mFields.count(name) > 0;
	}

	void ClassMetadata::addField(const std::string& name, const Type* type, AccessModifier accessModifier) {
		mFieldDefinitions.push_back(FieldDefinition(name, type, accessModifier));
	}

	void ClassMetadata::insertField(const std::string& name, const Field& field) {
		if (mFields.count(name) > 0) {
			throw std::runtime_error("The field '" + name + "' is already defined in the class '" + mName + "'.");
		}

		mFields.insert({ name, field });
	}

	void ClassMetadata::makeFields() {
		if (mFields.size() == 0) {
			//Add from parent class
			if (mParentClass != nullptr) {
				mParentClass->metadata()->makeFields();

				for (auto& fieldDef : mParentClass->metadata()->mFieldDefinitions) {
					insertField(fieldDef.name, Field(fieldDef.type, mSize, fieldDef.accessModifier, false));
					mSize += TypeSystem::sizeOfType(fieldDef.type);
				}
			}

			for (auto& fieldDef : mFieldDefinitions) {
				insertField(fieldDef.name, Field(fieldDef.type, mSize, fieldDef.accessModifier));
				mSize += TypeSystem::sizeOfType(fieldDef.type);
			}
		}
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

	const std::map<int, std::string>& ClassMetadata::virtualFunctions() const {
		return mIndexToVirtualFunction;
	}

	void ClassMetadata::addVirtualFunction(const FunctionDefinition& funcDef) {
		mVirtualFunctions.push_back(&funcDef);
	}

	int ClassMetadata::getVirtualFunctionIndex(const FunctionDefinition& funcDef) const {
		auto rootDef = getVirtualFunctionRootDefinition(&funcDef);
		auto signature = FunctionSignature::from(*rootDef).str();
		if (mVirtualFunctionToIndex.count(signature) == 0) {
			throw std::runtime_error("There exists no virtual function '" + signature + "' in the class '" + mName + "'.");
		}

		return mVirtualFunctionToIndex.at(signature);
	}

	const std::string &ClassMetadata::getVirtualFunctionSignature(int index) const {
		//No bounds checks, we assume that this function is only called with valid indices
		return mVirtualFunctionMapping[index];
	}

	void ClassMetadata::bindVirtualFunction(const FunctionDefinition& funcDef, BytePtr funcPtr) {
		if (mVirtualFunctionTable == nullptr) {
			throw std::runtime_error("Virtual function table not created.");
		}

		auto index = getVirtualFunctionIndex(funcDef);
		mVirtualFunctionTable[index] = funcPtr;
	}

	BytePtr* ClassMetadata::virtualFunctionTable() const {
		return mVirtualFunctionTable;
	}

	const FunctionDefinition* ClassMetadata::getVirtualFunctionRootDefinition(const FunctionDefinition* funcDef) const {
		if (mParentClass != nullptr) {
			for (auto parentDef : mParentClass->metadata()->mVirtualFunctions) {
				if (funcDef->memberName() == parentDef->memberName()
					&& TypeSystem::areEqual(funcDef->callParameters(), parentDef->callParameters())) {
					return mParentClass->metadata()->getVirtualFunctionRootDefinition(parentDef);
				}
			}
		}

		return funcDef;
	}

	bool ClassMetadata::makeVirtualFunctionTable() {
		if (mVirtualFunctionTable == nullptr && (mVirtualFunctions.size() > 0 || mParentClass != nullptr)) {
			int virtualFuncIndex = 0;
			bool hasParentVirtual = false;
			std::unordered_map<std::string, std::string> virtualFuncMapping;

			//Create for parent class
			if (mParentClass != nullptr) {
				mParentClass->metadata()->makeVirtualFunctionTable();

				//Add the parent class virtual functions
				for (auto& virtualFunc : mParentClass->metadata()->mIndexToVirtualFunction) {
					auto name = virtualFunc.second;
					auto index = virtualFunc.first;
					mIndexToVirtualFunction.insert({ index, name });
					mVirtualFunctionToIndex.insert({ name, index });
					virtualFuncMapping[name] = name;
					virtualFuncIndex = std::max(virtualFuncIndex, index);
					hasParentVirtual = true;
				}
			}

			if (hasParentVirtual) {
				virtualFuncIndex++;
			}

			//Now for this class
			for (auto& virtualFunc : mVirtualFunctions) {
				auto signature = FunctionSignature::from(*virtualFunc).str();
				auto rootDef = getVirtualFunctionRootDefinition(virtualFunc);
				auto rootSignature = FunctionSignature::from(*rootDef).str();

				if (mVirtualFunctionToIndex.count(rootSignature) == 0) {
					mIndexToVirtualFunction.insert({ virtualFuncIndex, signature });
					mVirtualFunctionToIndex.insert({ signature, virtualFuncIndex });
					virtualFuncIndex++;
				}

				virtualFuncMapping[rootSignature] = signature;
			}

			//Create the actual table. Note that these functions are bound when compiled.
			mVirtualFunctionTable = new BytePtr[mIndexToVirtualFunction.size()];
			for (std::size_t i = 0; i < mIndexToVirtualFunction.size(); i++) {
				mVirtualFunctionTable[i] = nullptr;
			}

			//Create the final mapping
			mVirtualFunctionMapping.resize(virtualFuncMapping.size());
			for (auto& virtualFunc : virtualFuncMapping) {
				mVirtualFunctionMapping[mVirtualFunctionToIndex[virtualFunc.first]] = virtualFunc.second;
			}

			return true;
		}

		return false;
	}

	//Provider
	void ClassMetadataProvider::add(const std::string& className, ClassMetadata metadata) {
		if (mClassesMetadata.count(className) == 0) {
			mClassesMetadata.emplace(className, std::move(metadata));
	    }
	}

	bool ClassMetadataProvider::isDefined(const std::string& className) const {
		return mClassesMetadata.count(className) > 0;
	}

	const ClassMetadata& ClassMetadataProvider::getMetadata(const std::string& className) const {
		if (mClassesMetadata.count(className) > 0) {
	        return mClassesMetadata.at(className);
	    } else {
	        throw std::out_of_range("The class isn't defined.");
	    }
	}

	ClassMetadata& ClassMetadataProvider::getMetadata(const std::string& className) {
		if (mClassesMetadata.count(className) > 0) {
			return mClassesMetadata.at(className);
		} else {
			throw std::out_of_range("The class isn't defined.");
		}
	}

	void ClassMetadataProvider::createVirtualFunctionTables(const VMState& vmState) {
		for (auto& current : mClassesMetadata) {
			auto& currentClass = current.second;
			auto createdVTable = currentClass.makeVirtualFunctionTable();

			if (createdVTable && vmState.config.enableDebug && vmState.config.printVirtualFunctionTableLayout) {
				std::cout << "V-table for " << currentClass.name() << std::endl;

				for (auto& virtualFunc : currentClass.virtualFunctions()) {
					std::cout << virtualFunc.first << ": " << virtualFunc.second << std::endl;
				}

				std::cout << std::endl;
			}
		}
	}

	const std::unordered_map<std::string, ClassMetadata>& ClassMetadataProvider::classesMetadata() const {
		return mClassesMetadata;
	}
}
