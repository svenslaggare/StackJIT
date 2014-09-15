#include <string>

//Represents a type
class Type {
private:
	const std::string mName;
public:
	Type(std::string name);
	virtual ~Type();

	//Returns the name of the type
	std::string name();

	//Compares if two types are equal
	bool operator==(const Type& type) const;
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

	const Type* elementType() const;
};

//Representa a stuct type
class StructType : public ReferenceType {
public:
	StructType(std::string name);
};

//The primitive types
enum PrimitiveTypes : unsigned char {
	Void,
	Integer
};

namespace TypeSystem {
	//Creates a new primitive type
	Type* makePrimitiveType(PrimitiveTypes primitiveType);
}