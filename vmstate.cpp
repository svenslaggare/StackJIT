#include "vmstate.h"
#include "type.h"
#include "program.h"

FunctionDefinition::FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint, int funcSize)
    : mArguments(arguments), mReturnType(returnType), mEntryPoint(entryPoint), mFunctionSize(funcSize), mIsManaged(true) {

}

FunctionDefinition::FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint)
    : mArguments(arguments), mReturnType(returnType), mEntryPoint(entryPoint), mFunctionSize(0), mIsManaged(false) {

}

FunctionDefinition::FunctionDefinition() {}

void FunctionDefinition::setFunctionBody(long entryPoint, int functionSize) {
    if (mIsManaged) {
        mEntryPoint = entryPoint;
        mFunctionSize = functionSize;
    }
}

Type* const FunctionDefinition::returnType() const {
    return mReturnType;
}

const std::vector<Type*>& FunctionDefinition::arguments() const {
    return mArguments;
}

bool FunctionDefinition::isManaged() const {
    return mIsManaged;
}

long FunctionDefinition::entryPoint() const {
    return mEntryPoint;
}

int FunctionDefinition::functionSize() const {
    return mFunctionSize;
}

VMState::~VMState() {
    for (auto type : types) {
        delete type.second;
    }
}

const std::unordered_map<const unsigned char*, ObjectHandle*>& VMState::getObjects() const {
    return mObjects;
}

void VMState::newObject(ObjectHandle* handle) {
    mObjects.insert({ handle->getHandle(), handle });
}

void VMState::deleteObject(ObjectHandle* handle) {
    mObjects.erase(handle->getHandle());
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

const StructMetadata* const VMState::getStructMetadata(std::string structName) const {
    if (structsMetadata.count(structName) > 0) {
        return &structsMetadata.at(structName);
    } else {
        return nullptr;
    }
}