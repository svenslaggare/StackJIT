#pragma once
#include <map>
#include <unordered_map>
#include <vector>

class Type;

//Represents a field
class Field {
private:
	const Type* mType;
	const std::size_t mOffset;
public:
	//Creates a new field
	Field(const Type* type, std::size_t offset);

	//Returns the type of the field
	const Type* type() const;

	//Returns the offset of the field in the struct
	const std::size_t offset() const;
};

//Contains metadata for a class
class ClassMetadata {
private:
	std::unordered_map<std::string, Field> mFields;
	std::size_t mSize;
public:
	//Creates a new class with the given fields
	ClassMetadata(std::vector<std::pair<std::string, const Type*>> fields);
	ClassMetadata();

	//Returns the size of the class
	std::size_t size() const;

	//Returns the fields
	const std::unordered_map<std::string, Field>& fields() const;

	//Adds a new field to the class
	void addField(std::string name, const Type* type);
};

class ClassType;

//Provides class metadata
class ClassMetadataProvider {
private:
	std::unordered_map<std::string, ClassMetadata> mClassesMetadata;
public:
	//Adds metadata for the given struct
    void add(std::string structName, ClassMetadata classMetadata);

    //Indicates if the struct is defined
    bool isDefined(std::string structName) const;

    //Returns the metadata for the given class
    const ClassMetadata& operator[](std::string className) const;
    ClassMetadata& operator[](std::string className);

    //Returns the metadata for the given class
    const ClassMetadata& metadataFor(const ClassType* classType) const;
};