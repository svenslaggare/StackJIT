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

	const Type* TypeProvider::makeType(std::string name) {
		if (mTypes.count(name) > 0) {
	        return mTypes[name];
	    } else {
	        auto type = TypeSystem::makeTypeFromString(name, mClassMetadataProvider);
	        mTypes.insert({ name, type });
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
