#pragma once
#include <map>

class Type;

//Contains metadata for a struct
class StructMetadata {
private:
	std::map<std::string, const Type*> fields;
public:
	StructMetadata(std::map<std::string, const Type*> fields);
	StructMetadata();

	//Returns the given field
	const Type* getField(std::string fieldName) const;

	//Returns the offset for the given field
	std::size_t getFieldOffset(std::string fieldName) const;

	//Returns the size of the struct
	std::size_t getSize() const;
};