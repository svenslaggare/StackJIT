#pragma once
#include <string>
#include <vector>

class Type;
class ClassType;
class FunctionDefinition;

//Represents a function signature
class FunctionSignature {
private:
	std::string mSignature;

	//Creates a new signature from the given string
	FunctionSignature(std::string signature);
public:
	//Constructs a signature for the given function
	static FunctionSignature function(std::string name, const std::vector<const Type*>& parameters);

	//Constructs a signature for the given member function
	static FunctionSignature memberFunction(const ClassType* classType, std::string name, const std::vector<const Type*>& parameters);

	//Constructs a signature from the given function definition
	static FunctionSignature from(const FunctionDefinition& function);

	//Returns a string representation of the current signature
	std::string str() const;

	bool operator==(const FunctionSignature& rhs) const;
	bool operator!=(const FunctionSignature& rhs) const;
};