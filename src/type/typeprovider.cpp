#include "typeprovider.h"
#include "type.h"

namespace stackjit {
	TypeProvider::TypeProvider(ClassMetadataProvider& classMetadataProvider)
		: mClassMetadataProvider(classMetadataProvider) {

	}

	TypeProvider::~TypeProvider() {
		for (auto type : mTypes) {
	        delete type.second;
	    }
	}

	void TypeProvider::insertType(std::string name, const Type* type) {
		mTypes.insert({ name, type });

		if (TypeSystem::isArray(type)) {
			auto arrayType = static_cast<const ArrayType*>(type);
			if (mTypes.count(arrayType->name()) == 0) {
				insertType(arrayType->elementType()->name(), arrayType->elementType());
			}
		}
	}

	const Type* TypeProvider::makeType(std::string name) {
		if (mTypes.count(name) > 0) {
	        return mTypes[name];
	    } else {
	        auto type = TypeSystem::makeTypeFromString(name, mClassMetadataProvider);
			insertType(name, type);
	        return type;
	    }
	}

	const Type* TypeProvider::getType(std::string name) const {
		if (mTypes.count(name) > 0) {
	        return mTypes.at(name);
	    } else {
	        return nullptr;
	    }
	}
}
