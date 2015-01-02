#pragma once
#include <map>

class Type;

//Represents a field
struct Field {
	const Type* type;
	const std::size_t offset;

	Field(const Type* type, std::size_t offset);
};

//Contains metadata for a struct
class StructMetadata {
private:
	std::map<std::string, Field> mFields;
	std::size_t mSize;
public:
	StructMetadata(std::map<std::string, const Type*> fields);
	StructMetadata();

	//Returns the given field
	const Type* getField(std::string fieldName) const;

	//Returns the offset for the given field
	std::size_t fieldOffset(std::string fieldName) const;

	//Returns the size of the struct
	std::size_t size() const;
};