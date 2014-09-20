#include "vmstate.h"
#include "type.h"

VMState::~VMState() {
    for (auto type : types) {
        delete type.second;
    }
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

FunctionDefinition::FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint, int funcSize)
    : Arguments(arguments), ReturnType(returnType), mEntryPoint(entryPoint), mFunctionSize(funcSize), mIsManaged(true) {

}

FunctionDefinition::FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint)
    : Arguments(arguments), ReturnType(returnType), mEntryPoint(entryPoint), mIsManaged(false) {

}

FunctionDefinition::FunctionDefinition() {}

void FunctionDefinition::setFunctionBody(long entryPoint, int functionSize) {
    if (mIsManaged) {
        mEntryPoint = entryPoint;
        mFunctionSize = functionSize;
    }
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