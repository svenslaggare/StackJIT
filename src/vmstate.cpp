#include "vmstate.h"

namespace stackjit {
	VMState::VMState(VMStateConfig config)
	    : config(config),
		  mTypeProvider(mClassProvider),
		  mGC(*this),
		  mEngine(*this) {

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
	    return mClassProvider;
	}

	const ClassMetadataProvider& VMState::classProvider() const {
	    return mClassProvider;
	}

	GarbageCollector& VMState::gc() {
	    return mGC;
	}
}
