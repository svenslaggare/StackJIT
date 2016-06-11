#pragma once
#include <string>
#include <functional>
#include "classmetadata.h"

class ClassMetadata;

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
	const std::string mClassName;
	ClassMetadata* mMetadata;
public:
	//Creates a new class type
	ClassType(std::string name, ClassMetadata* metadata);

	//Returns the name of the class
	std::string className() const;

	//Returns the metadata for the class
	ClassMetadata* metadata() const;
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
	//The string type name
	const std::string stringTypeName = "Ref.std.String";

	//The type type name
	const std::string nullTypeName = "Ref.Null";

	//Converts the given string into a primitive type. Returns true if valid type.
	bool fromString(std::string typeName, PrimitiveTypes& primitiveType);

	//Returns the given primitive type as a string
	std::string toString(PrimitiveTypes primitiveType);

	//Creates a new type from the given string
	Type* makeTypeFromString(std::string typeName, ClassMetadataProvider& classProvider);

	//Indicates if the given type is of the given primitive type
	bool isPrimitiveType(const Type* type, PrimitiveTypes primitiveType);

	//Indicates if the given type is a reference type
	bool isReferenceType(const Type* type);

	//Indicates if the given type is the null type
	bool isNullType(const Type* type);

	//Indicates if the given type is an array
	bool isArray(const Type* type);

	//Indicates if the given type is a class
	bool isClass(const Type* type);

	//Indicates if the given class is a subtype of the given class
	bool isSubtypeOf(const ClassType* baseClass, const ClassType* subClass);

	//Returns the type name for an array of the given type
	std::string arrayTypeName(const Type* type);

	//Returns the size (in bytes) for the given primitive type
	std::size_t sizeOfType(PrimitiveTypes primitiveType);

	//Returns the size (in bytes) for the given type
	std::size_t sizeOfType(const Type* type);

	//Gets the class- and field name from the given string
	bool getClassAndFieldName(std::string str, std::string& className, std::string& fieldName);
}