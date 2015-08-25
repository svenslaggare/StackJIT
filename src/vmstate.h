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
	bool enableDebug = false;

    //Indicates if testing mode is enabled
	bool testMode = false;

    //Indicates if the input program is an image or from stdin
    bool imageMode = false;

	//Indicates if the generated code is outputted as a file
	bool outputGeneratedCode = false;

    //Indicates if the GC is disabled
    bool disableGC = false;

    //Indicates if the runtime library is loaded at startup.
    bool loadRuntimeLibrary = true;

    //Indicates if the functions are lazily compiled
    bool lazyJIT = true;

    //Prints the info about the stack frame
    bool printStackFrame = false;

    //Prints when lazy calls are patched
    bool printLazyPatching = false;

    //Prints when a function has been compiled
    bool printFunctionGeneration = false;

    //Indicates if the start and end of a GC is printed
    bool printGCPeriod = false;

    //Indicates if alive objects are printed at GC
    bool printAliveObjects = false;

    //Indicates if the stack trace is printed at GC
    bool printGCStackTrace = false;

    //Indicates if an allocation is printed
    bool printAllocation = false;

    //Indicates if a deallocation is printed
    bool printDeallocation = false;

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