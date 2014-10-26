#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "objects.h"
#include "structmetadata.h"

class Type;

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
	Type* const returnType() const;

	//Returns the types of the arguments
	const std::vector<Type*>& arguments() const;

	//Sets the function body (for managed functions)
	void setFunctionBody(long entryPoint, int functionSize);

	//Indicates if the function is implemented in managed code
	bool isManaged() const;

	long entryPoint() const;
	int functionSize() const;
};

//Represents the state of the VM
class VMState {
private:
	std::unordered_map<std::string, Type*> types;
	std::unordered_map<std::string, StructMetadata> structsMetadata;
	std::vector<ObjectHandle*> mObjects;
public:
	~VMState();

    std::unordered_map<std::string, FunctionDefinition> functionTable;

    //Returns the handles for the allocated objects
    const std::vector<ObjectHandle*>& getObjects() const;

    //Adds the given handle to the list of objects
    void newObject(ObjectHandle* handle);

    //Finds the type object for the given type name
    Type* findType(std::string name);

    //Returns the given type (nullptr if not found)
    Type* getType(std::string name) const;

    //Adds metadata for the given struct
    void addStructMetadata(std::string structName, StructMetadata structMetadata);

    //Returns the metadata for the given struct
    const StructMetadata* const getStructMetadata(std::string structName) const;
};