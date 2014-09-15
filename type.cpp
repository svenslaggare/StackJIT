#include "type.h"

Type::Type(std::string name) : mName(name) {

}

Type::~Type() {

}

std::string Type::name() {
	return mName;
}

bool Type::operator==(const Type& type) const {
	return mName.compare(type.mName) == 0;
}

Type* TypeSystem::makePrimitiveType(PrimitiveTypes primitiveType) {
	switch (primitiveType) {
		case PrimitiveTypes::Void:
			return new Type("PrimitiveType.Void");
		case PrimitiveTypes::Integer:
			return new Type("PrimitiveType.Integer");
	}

	return nullptr;
}

ReferenceType::ReferenceType(std::string name): Type("ReferenceType." + name) {

}

ArrayType::ArrayType(Type* elementType): ReferenceType("Array." + elementType->name()), mElementType(elementType) {

}

ArrayType::~ArrayType() {
	delete mElementType;
}

StructType::StructType(std::string name): ReferenceType("Stuct." + name) {

}