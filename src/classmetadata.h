#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Type;

//The access modifiers
enum class AccessModifier : char {
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
	std::unordered_map<std::string, Field> mFields;
	std::size_t mSize;
public:
	//Creates new class metadata
	ClassMetadata();

	//Returns the size of the class
	std::size_t size() const;

	//Returns the fields
	const std::unordered_map<std::string, Field>& fields() const;

	//Adds a new field to the class
	void addField(std::string name, const Type* type, AccessModifier accessModifier);

	//The default access modifier
	static const AccessModifier DEFAULT_ACCESS_MODIFIER = AccessModifier::Public;
};

class ClassType;

//Provides class metadata
class ClassMetadataProvider {
private:
	std::unordered_map<std::string, ClassMetadata> mClassesMetadata;
public:
	//Adds metadata for the given struct
    void add(std::string className, ClassMetadata metadata);

    //Indicates if the struct is defined
    bool isDefined(std::string structName) const;

    //Returns the metadata for the given class
    const ClassMetadata& getMetadata(std::string className) const;
    ClassMetadata& getMetadata(std::string className);
};