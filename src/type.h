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
	Type& operator=(const Type&) = delete;

	//Returns the name of the type
	std::string name() const;

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

//Represents a null reference
class NullReferenceType : public ReferenceType {
public:
	NullReferenceType();
};

//Represents an array type
class ArrayType : public ReferenceType {
private:
	const Type* mElementType;
public:
	//Creates a new array type
	ArrayType(const Type* elementType);
	virtual ~ArrayType();

	//Returns the type of the element
	const Type* elementType() const;
};

//Represents a class type
class ClassType : public ReferenceType {
private:
	const std::string mStructName;
public:
	//Creates a new class type
	ClassType(std::string name);

	//Returns the name of the class
	std::string className() const;
};

//The primitive types
enum PrimitiveTypes : unsigned char {
	Void,
	Integer,
	Float,
	Bool,
	Char
};

class ClassMetadataProvider;

namespace TypeSystem {
	//Converts the given string into a primitive type. True if correct type.
	bool fromString(std::string typeName, PrimitiveTypes& primitiveType);

	//Returns the given primitive type as a string
	std::string toString(PrimitiveTypes primitiveType);

	//Creates a new type from the given string
	Type* makeTypeFromString(std::string typeName, const ClassMetadataProvider& structProvider);

	//Indicates if the given type is of the given primitive type
	bool isPrimitiveType(const Type* type, PrimitiveTypes primitiveType);

	//Indicates if the given type is a reference type
	bool isReferenceType(const Type* type);

	//Indicates if the given type is an array
	bool isArray(const Type* type);

	//Indicates if the given type is a class
	bool isClass(const Type* type);

	//Returns the type name for an array of the given type
	std::string arrayTypeName(const Type* type);

	//Returns the size (in bytes) for the given primitive type
	std::size_t sizeOfType(PrimitiveTypes primitiveType);

	//Returns the size (in bytes) for the given type
	std::size_t sizeOfType(const Type* type);

	//Gets the class name and field from the given string
	bool getClassAndField(std::string str, std::pair<std::string, std::string>& res);
}