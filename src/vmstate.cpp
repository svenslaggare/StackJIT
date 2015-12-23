#include "vmstate.h"
#include "type/type.h"
#include "type/objects.h"

VMState::VMState()
    : mTypeProvider(mStructProvider), mGC(*this), mEngine(*this) {

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

const ExecutionEngine& VMState::engine() const {
    return mEngine;
}

const Binder& VMState::binder() const {
    return mBinder;
}

ClassMetadataProvider& VMState::classProvider() {
    return mStructProvider;
}

const ClassMetadataProvider& VMState::classProvider() const {
    return mStructProvider;
}

GarbageCollector& VMState::gc() {
    return mGC;
}