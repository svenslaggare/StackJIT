#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <deque>
#include "structmetadata.h"
#include "function.h"
#include "binder.h"

class Type;
class StructType;
class ObjectHandle;

using CallStackEntry = std::pair<Function*, int>;

//Contains the state of the VM
class VMState {
private:
	std::unordered_map<std::string, Type*> mTypes;
    Binder mBinder;
	std::unordered_map<std::string, StructMetadata> mStructsMetadata;

	std::unordered_map<const unsigned char*, ObjectHandle*> mObjects;
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

    //Creates a new VM State
    VMState();
	~VMState();

    //Prevent the VM state from being copied
    VMState(const VMState&) = delete;
    VMState& operator=(const VMState&) = delete;

    //Returns the handles for the allocated objects
    const std::unordered_map<const unsigned char*, ObjectHandle*>& getObjects() const;

    //Adds the given handle to the list of objects
    void newObject(ObjectHandle* handle);

    //Deletes the given object
    void deleteObject(ObjectHandle* handle);

    //Returns the call stack
    const std::deque<CallStackEntry>& callStack() const;

    //Pops the top function
    CallStackEntry popFunc();

    //Pushes the given function to the top of the stack
    void pushFunc(Function* func, int instIndex);

    //Returns the binder
    Binder& binder();
    const Binder& binder() const;

    //Finds the type object for the given type name
    const Type* findType(std::string name);

    //Returns the given type (nullptr if not found)
    const Type* getType(std::string name) const;

    //Adds metadata for the given struct
    void addStructMetadata(std::string structName, StructMetadata structMetadata);

    //Indicates if the stuct is defined
    bool isStructDefined(std::string structName) const;

    //Returns the metadata for the given struct
    const StructMetadata& getStructMetadata(std::string structName) const;

    //Returns the metadata for the given struct
    const StructMetadata& getStructMetadata(const StructType* structType) const;
};