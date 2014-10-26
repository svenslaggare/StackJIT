#include "vmstate.h"
#include "type.h"

FunctionDefinition::FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint, int funcSize)
    : mArguments(arguments), mReturnType(returnType), mEntryPoint(entryPoint), mFunctionSize(funcSize), mIsManaged(true) {

}

FunctionDefinition::FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint)
    : mArguments(arguments), mReturnType(returnType), mEntryPoint(entryPoint), mIsManaged(false) {

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

const std::vector<ObjectHandle*>& VMState::getObjects() const {
    return mObjects;
}

void VMState::newObject(ObjectHandle* handle) {
    mObjects.push_back(handle);
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