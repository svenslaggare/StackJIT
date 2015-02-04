#include "vmstate.h"
#include "type.h"
#include "objects.h"

VMState::VMState() {

}

VMState::~VMState() {
    for (auto type : mTypes) {
        delete type.second;
    }
}

const std::unordered_map<const unsigned char*, ObjectHandle*>& VMState::getObjects() const {
    return mObjects;
}

void VMState::newObject(ObjectHandle* handle) {
    mObjects.insert({ handle->handle(), handle });
}

void VMState::deleteObject(ObjectHandle* handle) {
    mObjects.erase(handle->handle());
    handle->deleteHandle();
    delete handle;
}

const std::deque<CallStackEntry>& VMState::callStack() const {
    return mCallStack;
}

CallStackEntry VMState::popFunc() {
    auto top = std::make_pair(mCallStack.front().first, mCallStack.front().second);
    mCallStack.pop_front();
    return top;
}

void VMState::pushFunc(Function* func, int instIndex) {
    auto newEntry = std::make_pair(func, instIndex);
    mCallStack.push_front(newEntry);
}

Binder& VMState::binder() {
    return mBinder;
}

const Binder& VMState::binder() const {
    return mBinder;
}

const Type* VMState::findType(std::string name) {
    if (mTypes.count(name) > 0) {
        return mTypes[name];
    } else {
        auto type = TypeSystem::makeTypeFromString(name);
        mTypes.insert({ name, type });
        return type;
    }
}

const Type* VMState::getType(std::string name) const {
    if (mTypes.count(name) > 0) {
        return mTypes.at(name);
    } else {
        return nullptr;
    }
}

void VMState::addStructMetadata(std::string structName, StructMetadata structMetadata) {
    if (mStructsMetadata.count(structName) == 0) {
        mStructsMetadata[structName] = structMetadata;
    }
}

bool VMState::isStructDefined(std::string structName) const {
    return mStructsMetadata.count(structName) > 0;
}

const StructMetadata& VMState::getStructMetadata(std::string structName) const {
    if (mStructsMetadata.count(structName) > 0) {
        return mStructsMetadata.at(structName);
    } else {
        throw std::out_of_range("The struct isn't defined.");
    }
}

const StructMetadata& VMState::getStructMetadata(const StructType* structType) const {
    return getStructMetadata(structType->structName());
}