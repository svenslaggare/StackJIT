#pragma once
#include <string>
#include <functional>
#include <map>

//Represents a type
class Type {
private:
	const std::string mName;
public:
	Type(std::string name);
	virtual ~Type();
	Type(const Type&) = delete;

	//Returns the name of the type
	std::string name();

	//Compares if two types are equal
	bool operator==(const Type& type) const;

	//Compares if two types are not equal
	bool operator!=(const Type& type) const;
};

//Represents a reference type
class ReferenceType : public Type {
public:
	ReferenceType(std::string name);
};

//Represents an array type
class ArrayType : public ReferenceType {
private:
	const Type* mElementType;
public:
	ArrayType(Type* elementType);
	~ArrayType();

	//Returns the type of the element
	const Type* elementType() const;
};

//Representa a struct type
class StructType : public ReferenceType {
private:
	std::string mStructName;
public:
	StructType(std::string name);

	//Returns the name of the struct
	std::string structName() const;
};

//The primitive types
enum PrimitiveTypes : unsigned char {
	Void,
	Integer
};

namespace TypeSystem {
	//Returns the name of the given primitive type
	std::string getPrimitiveTypeName(PrimitiveTypes primitiveType);

	//Creates a new type from the given string
	Type* makeTypeFromString(std::string typeName);

	//Indicates if the given type is of the given primitive type
	bool isPrimitiveType(Type* type, PrimitiveTypes primitiveType);

	//Indicates if the given type is a reference type
	bool isReferenceType(Type* type);

	//Indicates if the given type is an array
	bool isArray(Type* type);

	//Indicates if the given type is a struct
	bool isStruct(Type* type);

	//Returns the size (in bytes) for the given primitive type
	std::size_t getSize(PrimitiveTypes primitiveType);

	//Returns the size (in bytes) for the given type
	std::size_t sizeOfType(Type* type);
}