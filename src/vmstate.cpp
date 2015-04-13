#include "vmstate.h"
#include "type.h"
#include "objects.h"

VMState::VMState()
    : mGC(*this), mEngine(*this) {

}

VMState::~VMState() {
    //Unmap function code memory
    for (auto funcEntry : mBinder.functionTable()) {
        auto func = funcEntry.second;
        func.deleteCodeMemory(mEngine.jitCompiler().memoryManager());
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

TypeProvider& VMState::typeProvider() {
    return mTypeProvider;
}

const TypeProvider& VMState::typeProvider() const {
    return mTypeProvider;
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