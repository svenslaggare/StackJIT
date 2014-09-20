#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "objects.h"

class Type;

//Represents a definition for a function
class FunctionDefinition {
private:
	long mEntryPoint;
	int mFunctionSize;

	bool mIsManaged; //Indicates if the function is implemented in managed code
public:
	std::vector<Type*> Arguments;
	Type* ReturnType;

	//Creates a new managed function definition
	FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint, int funcSize);

	//Creates a new external function definition
	FunctionDefinition(std::vector<Type*> arguments, Type* returnType, long entryPoint);

	FunctionDefinition();

	//Sets the function body (for managed functions)
	void setFunctionBody(long entryPoint, int functionSize);

	bool isManaged() const;
	long entryPoint() const;
	int functionSize() const;
};


//Represents the state of the VM
class VMState {
private:
	std::unordered_map<std::string, Type*> types;
public:
	~VMState();

    std::unordered_map<std::string, FunctionDefinition> FunctionTable;
    std::vector<ArrayHandle> Objects;

    //Finds the type object for the given type name
    Type* findType(std::string name);

    //Returns the given type (nullptr if not found)
    Type* getType(std::string name) const;
};