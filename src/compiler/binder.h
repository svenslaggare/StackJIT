#pragma once
#include <unordered_map>
#include <string>
#include "../function.h"

class Type;
class ClassType;

//Represents a binder
class Binder {
private:
	std::unordered_map<std::string, FunctionDefinition> mFunctionTable;
public:
	//Returns the function table
	const std::unordered_map<std::string, FunctionDefinition>& functionTable() const;

	//Defines the given function
	bool define(FunctionDefinition funcDef);

	//Defines the given external signature
	bool defineExternal(std::string signature, std::string externalSignature);

	//Indicates if the given function signature is defined
	bool isDefined(std::string signature) const;

	//Returns the function with the given signature
	FunctionDefinition& getFunction(std::string signature);
	const FunctionDefinition& getFunction(std::string signature) const;

	//Returns the definition for the given function
	const FunctionDefinition& getFunction(const ManagedFunction& function) const;
};