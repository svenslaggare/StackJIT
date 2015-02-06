#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <deque>
#include "structmetadata.h"
#include "function.h"
#include "binder.h"
#include "gc.h"

class Type;
class StructType;
class ObjectHandle;

using CallStackEntry = std::pair<Function*, int>;

//Contains the state of the VM
class VMState {
private:
	std::unordered_map<std::string, Type*> mTypes;
    Binder mBinder;
	StructMetadataProvider mStructProvider;
    GarbageCollector mGC;

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

    //Returns the GC
    GarbageCollector& gc();

    //Returns the struct metadata provider
    StructMetadataProvider& structProvider();
    const StructMetadataProvider& structProvider() const;

    //Returns the binder
    Binder& binder();
    const Binder& binder() const;

    //Tries to find or construct the given type name name. Nullptr if not found.
    const Type* findType(std::string name);

    //Returns the given type. Nullptr if not found.
    const Type* getType(std::string name) const;
};