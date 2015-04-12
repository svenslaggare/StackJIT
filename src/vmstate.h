#pragma once
#include <unordered_map>
#include <string>
#include <deque>

#include "structmetadata.h"
#include "function.h"
#include "binder.h"
#include "gc.h"
#include "executionengine.h"
#include "typeprovider.h"

using CallStackEntry = std::pair<Function*, int>;

//Contains the state of the VM
class VMState {
private:
	TypeProvider mTypeProvider;
    Binder mBinder;
	StructMetadataProvider mStructProvider;
    GarbageCollector mGC;
    ExecutionEngine mEngine;

	std::deque<CallStackEntry> mCallStack;
public:
	//Indicates if debugging is enabled
	bool enableDebug = true;

	//Prints type checking if debug is enabled
	bool printTypeChecking = false;

	//Prints the info about the stack frame if debug is enabled
	bool printStackFrame = false;

	//Indicates if the generated code is outputed as a file
	bool outputGeneratedCode = false;

    //Indicates if the GC is disabled
    bool disableGC = false;

    //Creates a new VM State
    VMState();
	~VMState();

    //Prevent the VM state from being copied
    VMState(const VMState&) = delete;
    VMState& operator=(const VMState&) = delete;

    //Returns the call stack
    const std::deque<CallStackEntry>& callStack() const;

    //Pops the top function
    CallStackEntry popFunc();

    //Pushes the given function to the top of the stack
    void pushFunc(Function* func, int instIndex);

    //Returns the type provider
    TypeProvider& typeProvider();
    const TypeProvider& typeProvider() const;

    //Returns the binder
    Binder& binder();
    const Binder& binder() const;

    //Returns the struct metadata provider
    StructMetadataProvider& structProvider();
    const StructMetadataProvider& structProvider() const;

    //Returns the execution engine
    ExecutionEngine& engine();

    //Returns the GC
    GarbageCollector& gc();
};