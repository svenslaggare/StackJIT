#pragma once
#include "binder.h"
#include "gc.h"
#include "executionengine.h"
#include "typeprovider.h"
#include "classmetadata.h"

//Contains the state of the VM
class VMState {
private:
    ClassMetadataProvider mStructProvider;
	TypeProvider mTypeProvider;
    Binder mBinder;
    GarbageCollector mGC;
    ExecutionEngine mEngine;
public:
	//Indicates if debugging is enabled
	bool enableDebug = true;

	//Prints type checking if debug is enabled
	bool printTypeChecking = false;

	//Prints the info about the stack frame if debug is enabled
	bool printStackFrame = false;

	//Indicates if the generated code is outputted as a file
	bool outputGeneratedCode = false;

    //Indicates if the GC is disabled
    bool disableGC = false;

    //Indicates if the VM is in test mode
    bool enableTestMode = false;

    //Creates a new VM State
    VMState();

    //Prevent the VM state from being copied
    VMState(const VMState&) = delete;
    VMState& operator=(const VMState&) = delete;

    //Returns the type provider
    TypeProvider& typeProvider();
    const TypeProvider& typeProvider() const;

    //Returns the binder
    Binder& binder();
    const Binder& binder() const;

    //Returns the class metadata provider
	ClassMetadataProvider& classProvider();
    const ClassMetadataProvider& classProvider() const;

    //Returns the execution engine
    ExecutionEngine& engine();
    const ExecutionEngine& engine() const;

    //Returns the GC
    GarbageCollector& gc();
};