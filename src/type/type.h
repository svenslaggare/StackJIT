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
		std::string name() const;

		//Indicates if the current type is a reference type
		virtual bool isReferenceType() const = 0;

		//Indicates if the current type is an array type
		virtual bool isArrayType() const = 0;

		//Indicates if the current type is a class type
		virtual bool isClassType() const = 0;

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

		virtual bool isReferenceType() const override;
		virtual bool isArrayType() const override;
		virtual bool isClassType() const override;
	};

	//Represents a reference type
	class ReferenceType : public Type {
	public:
		ReferenceType(std::string name);

		virtual bool isReferenceType() const override;
	};

	//Represents a null reference
	class NullReferenceType : public ReferenceType {
	public:
		NullReferenceType();

		virtual bool isArrayType() const override;
		virtual bool isClassType() const override;
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

		virtual bool isArrayType() const override;
		virtual bool isClassType() const override;
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

		virtual bool isArrayType() const override;
		virtual bool isClassType() const override;
	};

	namespace TypeSystem {
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

		//Indicates if the given types are equal
		bool sameType(const Type* type1, const Type* type2);

		//Indicates if the given list of types are the same
		bool areEqual(const std::vector<const Type*>& list1, const std::vector<const Type*>& list2);

		//Returns the type name for an array of the given type
		std::string arrayTypeName(const Type* type);

		//Returns the size (in bytes) for the given primitive type
		std::size_t sizeOfType(PrimitiveTypes primitiveType);

		//Returns the size (in bytes) for the given type
		std::size_t sizeOfType(const Type* type);

		//Gets the class- and field name from the given string
		bool getClassAndFieldName(std::string str, std::string& className, std::string& fieldName);
	}
}
