#include "typeprovider.h"
#include "type.h"

TypeProvider::TypeProvider() {

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
        auto type = TypeSystem::makeTypeFromString(name);
        mTypes.insert({ name, type });
        return type;
    }
}

void TypeProvider::addType(const Type* type) {
	if (mTypes.count(type->name()) == 0) {
		mTypes.insert({ type->name(), type });
	}
}

const Type* TypeProvider::getType(std::string name) const {
	if (mTypes.count(name) > 0) {
        return mTypes.at(name);
    } else {
        return nullptr;
    }
}