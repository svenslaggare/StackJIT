#include "vmstate.h"
#include "type.h"
#include "objects.h"

VMState::VMState()
    : mGC(*this), mEngine(*this) {

}

VMState::~VMState() {
    for (auto type : mTypes) {
        delete type.second;
    }

    //Unmap function code memory
    for (auto funcEntry : mBinder.functionTable()) {
        auto func = funcEntry.second;
        func.deleteCodeMemory();
    }
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

ExecutionEngine& VMState::engine() {
    return mEngine;
}

const Binder& VMState::binder() const {
    return mBinder;
}

StructMetadataProvider& VMState::structProvider() {
    return mStructProvider;
}

const StructMetadataProvider& VMState::structProvider() const {
    return mStructProvider;
}

GarbageCollector& VMState::gc() {
    return mGC;
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