#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <deque>
#include "objects.h"
#include "structmetadata.h"

class Type;
class Function;

//Represents a definition for a function
class FunctionDefinition {
private:
	long mEntryPoint;
	int mFunctionSize;

	bool mIsManaged;

	Type* mReturnType;
	std::vector<Type*> mArguments;
public:
	//Creates a new managed function definition
	FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint, int funcSize);

	//Creates a new external function definition
	FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint);

	FunctionDefinition();

	//Returns the type of the return value
	Type* returnType() const;

	//Returns the types of the arguments
	const std::vector<Type*>& arguments() const;

	//Sets the function body (for managed functions)
	void setFunctionBody(long entryPoint, int functionSize);

	//Indicates if the function is implemented in managed code
	bool isManaged() const;

	//The entry point
	long entryPoint() const;

	//The size of the function
	int functionSize() const;

	//Frees the allocted memory for the function (if mananaged)
	void deleteFunction();
};

//Represents the state of the VM
using CallStackEntry = std::pair<Function*, int>;

class VMState {
private:
	std::unordered_map<std::string, Type*> types;
	std::unordered_map<std::string, StructMetadata> structsMetadata;
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

	std::unordered_map<std::string, FunctionDefinition> functionTable;

	~VMState();

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

    //Finds the type object for the given type name
    Type* findType(std::string name);

    //Returns the given type (nullptr if not found)
    Type* getType(std::string name) const;

    //Adds metadata for the given struct
    void addStructMetadata(std::string structName, StructMetadata structMetadata);

    //Returns the metadata for the given struct
    const StructMetadata* getStructMetadata(std::string structName) const;
};