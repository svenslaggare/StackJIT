#include "vmstate.h"
#include "type.h"
#include "objects.h"

VMState::~VMState() {
    for (auto type : types) {
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

Type* VMState::findType(std::string name) {
    if (types.count(name) > 0) {
        return types[name];
    } else {
        Type* type = TypeSystem::makeTypeFromString(name);
        types.insert({ name, type });
        return type;
    }
}

Type* VMState::getType(std::string name) const {
    if (types.count(name) > 0) {
        return types.at(name);
    } else {
        return nullptr;
    }
}

void VMState::addStructMetadata(std::string structName, StructMetadata structMetadata) {
    if (structsMetadata.count(structName) == 0) {
        structsMetadata[structName] = structMetadata;
    }
}

const StructMetadata* VMState::getStructMetadata(std::string structName) const {
    if (structsMetadata.count(structName) > 0) {
        return &structsMetadata.at(structName);
    } else {
        return nullptr;
    }
}