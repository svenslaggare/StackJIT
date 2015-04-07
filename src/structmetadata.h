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

//Contains metadata for a struct
class StructMetadata {
private:
	std::unordered_map<std::string, Field> mFields;
	std::size_t mSize;
public:
	//Creates a new struct with the given fields
	StructMetadata(std::vector<std::pair<std::string, const Type*>> fields);
	StructMetadata();

	//Returns the given field
	const Type* getField(std::string fieldName) const;

	//Returns the offset for the given field
	std::size_t fieldOffset(std::string fieldName) const;

	//Returns the size of the struct
	std::size_t size() const;

	//Returns the fields
	const std::unordered_map<std::string, Field>& fields() const;
};

class StructType;

//Provides struct metadata
class StructMetadataProvider {
private:
	std::unordered_map<std::string, StructMetadata> mStructsMetadata;
public:
	//Adds metadata for the given struct
    void add(std::string structName, StructMetadata structMetadata);

    //Indicates if the struct is defined
    bool isDefined(std::string structName) const;

    //Returns the metadata for the given struct
    const StructMetadata& operator[](std::string structName) const;

    //Returns the metadata for the given struct
    const StructMetadata& metadataFor(const StructType* structType) const;
};