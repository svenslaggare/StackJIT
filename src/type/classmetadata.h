#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "type.h"

class Type;
class ClassType;
class FunctionDefinition;
class VMState;

//The access modifiers
enum class AccessModifier : unsigned char {
	Private,
	Public
};

//Gets an access modifier from the given string
bool fromString(std::string str, AccessModifier& accessModifier);

//Represents a field
class Field {
private:
	const Type* mType;
	const std::size_t mOffset;
	const AccessModifier mAccessModifier;
public:
	//Creates a new field
	Field(const Type* type, std::size_t offset, AccessModifier accessModifier);

	//Returns the type of the field
	const Type* type() const;

	//Returns the offset of the field in the class
	const std::size_t offset() const;

	//Returns the access modifier
	const AccessModifier accessModifier() const;
};

//Contains metadata for a class
class ClassMetadata {
private:
	std::string mName;
	std::unordered_map<std::string, Field> mFields;
	std::size_t mSize;

	const ClassType* mParentClass;

	std::vector<std::string> mVirtualFunctions;
	std::unordered_map<std::string, int> mVirtualFunctionToIndex;
	std::vector<std::string> mIndexToVirtualFunction;
	unsigned char** mVirtualFunctionTable;
public:
	//The default access modifier
	static const AccessModifier DEFAULT_ACCESS_MODIFIER = AccessModifier::Public;

	//Creates new class metadata
	ClassMetadata(std::string name);
	~ClassMetadata();

	//Use default move
	ClassMetadata(ClassMetadata&&) = default;
	ClassMetadata& operator=(ClassMetadata&&) = default;

	//Prevent from copying
	ClassMetadata(const ClassMetadata&) = delete;
	ClassMetadata& operator=(const ClassMetadata&) = delete;

	//Returns the name of the class
	std::string name() const;

	//Returns the size of the class
	std::size_t size() const;

	//Returns the fields
	const std::unordered_map<std::string, Field>& fields() const;

	//Adds a new field to the class
	void addField(std::string name, const Type* type, AccessModifier accessModifier);

	//Returns the parent class (if any, else null)
	const ClassType* parentClass() const;

	//Sets the parent class
	void setParentClass(const ClassType* parentClass);

	//Returns the list of virtual functions
	const std::vector<std::string>& virtualFunctions() const;

	//Adds the given function to the list of virtual functions
	void addVirtualFunction(const FunctionDefinition& funcDef);

	//Returns the index of the given virtual function
	int getVirtualFunctionIndex(const FunctionDefinition& funcDef) const;

	//Returns the signature of the given virtual function
	std::string getVirtualFunctionSignature(int index) const;

	//Binds the given virtual function
	void bindVirtualFunction(const FunctionDefinition& funcDef, unsigned char* funcPtr);

	//Returns the virtual function table
	unsigned char** virtualFunctionTable() const;

	//Creates the virtual function table
	void makeVirtualFunctionTable();
};

//Provides class metadata
class ClassMetadataProvider {
private:
	std::unordered_map<std::string, ClassMetadata> mClassesMetadata;
public:
	//Adds metadata for the given class
    void add(std::string className, ClassMetadata metadata);

    //Indicates if the struct is defined
    bool isDefined(std::string className) const;

    //Returns the metadata for the given class
    const ClassMetadata& getMetadata(std::string className) const;
    ClassMetadata& getMetadata(std::string className);

	//Creates the virtual function tables
	void createVirtualFunctionTables(const VMState& vmState);
};