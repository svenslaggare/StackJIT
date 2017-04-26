#pragma once
#include <string>
#include <functional>
#include "classmetadata.h"

namespace stackjit {
	class ClassMetadata;

	//The primitive types
	enum class PrimitiveTypes : unsigned char {
		Void,
		Integer,
		Float,
		Bool,
		Char
	};

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
		const std::string& name() const;

		//Indicates if the current type is a reference type
		virtual bool isReference() const = 0;

		//Indicates if the current type is an array type
		virtual bool isArray() const = 0;

		//Indicates if the current type is a class type
		virtual bool isClass() const = 0;

		//Compares if two types are equal
		bool operator==(const Type& type) const;

		//Compares if two types are not equal
		bool operator!=(const Type& type) const;
	};

	//Represents a primitive type
	class PrimitiveType : public Type {
	public:
		//Creates a primitive type of the given type
		PrimitiveType(PrimitiveTypes primitiveType);

		virtual bool isReference() const override;
		virtual bool isArray() const override;
		virtual bool isClass() const override;
	};

	//Represents a reference type
	class ReferenceType : public Type {
	public:
		ReferenceType(std::string name);

		virtual bool isReference() const override;
	};

	//Represents a null reference
	class NullReferenceType : public ReferenceType {
	public:
		NullReferenceType();

		virtual bool isArray() const override;
		virtual bool isClass() const override;
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

		virtual bool isArray() const override;
		virtual bool isClass() const override;
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
		const std::string& className() const;

		//Returns the metadata for the class
		ClassMetadata* metadata() const;

		virtual bool isArray() const override;
		virtual bool isClass() const override;
	};

	namespace TypeSystem {
		//The name of the string class
		const std::string stringClassName = "std.String";

		//The string type name
		const std::string stringTypeName = "Ref." + stringClassName;

		//The type type name
		const std::string nullTypeName = "Ref.Null";

		//Converts the given string into a primitive type. Returns true if valid type.
		bool fromString(std::string typeName, PrimitiveTypes& primitiveType);

		//Returns the given primitive type as a string
		std::string toString(PrimitiveTypes primitiveType);

		//Indicates if the given type is of the given primitive type
		bool isPrimitiveType(const Type* type, PrimitiveTypes primitiveType);

		//Indicates if the given type is the null type
		bool isNullType(const Type* type);

		//Indicates if the given class is a subtype of the given class
		bool isSubtypeOf(const ClassType* baseClass, const ClassType* subClass);

		//Indicates if the given list of types are the same
		bool areEqual(const std::vector<const Type*>& list1, const std::vector<const Type*>& list2);

		//Returns the type name for an array of the given type
		std::string arrayTypeName(const Type* type);

		//Returns the type name for the given class
		std::string classTypeName(std::string className);

		//Returns the size (in bytes) for the given primitive type
		std::size_t sizeOfType(PrimitiveTypes primitiveType);

		//Returns the size (in bytes) for the given type
		std::size_t sizeOfType(const Type* type);

		//Gets the class- and field name from the given string
		bool getClassAndFieldName(std::string str, std::string& className, std::string& fieldName);
	}
}
