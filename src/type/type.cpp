#include "type.h"
#include "classmetadata.h"

#include <vector>
#include <iostream>
#include <unordered_map>

namespace stackjit {
	Type::Type(std::string name)
		: mName(name) {

	}

	Type::~Type() {

	}

	std::string Type::name() const {
		return mName;
	}

	bool Type::operator==(const Type& type) const {
		if (this == &type) {
			return true;
		}

		return mName.compare(type.mName) == 0;
	}

	bool Type::operator!=(const Type& type) const {
		return !(*this == type);
	}

	ReferenceType::ReferenceType(std::string name): Type("Ref." + name) {

	}

	NullReferenceType::NullReferenceType(): ReferenceType("Null") {

	}

	ArrayType::ArrayType(const Type* elementType)
		: ReferenceType("Array[" + elementType->name() + "]"), mElementType(elementType) {

	}

	const Type* ArrayType::elementType() const {
		return mElementType;
	}

	ArrayType::~ArrayType() {

	}

	ClassType::ClassType(std::string name, ClassMetadata* metadata)
		: ReferenceType(name), mClassName(name), mMetadata(metadata) {

	}

	std::string ClassType::className() const {
		return mClassName;
	}

	ClassMetadata* ClassType::metadata() const {
		return mMetadata;
	}

	bool TypeSystem::fromString(std::string typeName, PrimitiveTypes& primitiveType) {
		if (typeName == "Int") {
			primitiveType = PrimitiveTypes::Integer;
			return true;
		} else if (typeName == "Float") {
			primitiveType = PrimitiveTypes::Float;
			return true;
		} else if (typeName == "Bool") {
			primitiveType = PrimitiveTypes::Bool;
			return true;
		} else if (typeName == "Char") {
			primitiveType = PrimitiveTypes::Char;
			return true;
		} else if (typeName == "Void") {
			primitiveType = PrimitiveTypes::Void;
			return true;
		}

		return false;
	}

	std::string TypeSystem::toString(PrimitiveTypes primitiveType) {
		switch (primitiveType) {
			case PrimitiveTypes::Void:
				return "Void";
			case PrimitiveTypes::Integer:
				return "Int";
			case PrimitiveTypes::Float:
				return "Float";
			case PrimitiveTypes::Bool:
				return "Bool";
			case PrimitiveTypes::Char:
				return "Char";
		}

		return "";
	}

	bool TypeSystem::isPrimitiveType(const Type* type, PrimitiveTypes primitiveType) {
		if (type != nullptr) {
			PrimitiveTypes outType;

			if (fromString(type->name(), outType)) {
				return outType == primitiveType;
			}
		}

		return false;
	}

	bool TypeSystem::isReferenceType(const Type* type) {
		if (type == nullptr) {
			return false;
		}

		return dynamic_cast<const ReferenceType*>(type) != nullptr;
	}

	bool TypeSystem::isNullType(const Type* type) {
		if (type == nullptr) {
			return false;
		}

		return dynamic_cast<const NullReferenceType*>(type) != nullptr;
	}

	bool TypeSystem::isArray(const Type* type) {
		if (type == nullptr) {
			return false;
		}

		return dynamic_cast<const ArrayType*>(type) != nullptr;
	}

	bool TypeSystem::isClass(const Type* type) {
		if (type == nullptr) {
			return false;
		}

		return dynamic_cast<const ClassType*>(type) != nullptr;
	}

	bool TypeSystem::isSubtypeOf(const ClassType* baseClass, const ClassType* subClass) {
		if (subClass->metadata()->parentClass() == nullptr) {
			return false;
		}

		if (*subClass->metadata()->parentClass() == *baseClass) {
			return true;
		}

		return isSubtypeOf(baseClass, subClass->metadata()->parentClass());
	}

	bool TypeSystem::sameType(const Type* type1, const Type* type2) {
		return
			*type1 == *type2
			|| (TypeSystem::isReferenceType(type1) && TypeSystem::isNullType(type2))
			|| (TypeSystem::isReferenceType(type2) && TypeSystem::isNullType(type1));
	}

	bool TypeSystem::areEqual(const std::vector<const Type*>& list1, const std::vector<const Type*>& list2) {
		if (list1.size() != list2.size()) {
			return false;
		}

		for (std::size_t i = 0; i < list1.size(); i++) {
			if (*list1[i] != *list2[i]) {
				return false;
			}
		}

		return true;
	}

	std::string TypeSystem::arrayTypeName(const Type* type) {
		return "Ref.Array[" + type->name() +  "]";
	}

	std::size_t TypeSystem::sizeOfType(PrimitiveTypes primitiveType) {
		switch (primitiveType) {
		case PrimitiveTypes::Void:
			return 0;
		case PrimitiveTypes::Integer:
			return 4;
		case PrimitiveTypes::Float:
			return 4;
		case PrimitiveTypes::Bool:
			return 1;
		case PrimitiveTypes::Char:
			return 1;
		}

		return 0;
	}

	std::size_t TypeSystem::sizeOfType(const Type* type) {
		auto typeName = type->name();
		PrimitiveTypes primitiveType;

		if (fromString(typeName, primitiveType)) {
			return sizeOfType(primitiveType);
		} else if (TypeSystem::isReferenceType(type)) {
			return sizeof(unsigned char*);
		}

		return 0;
	}

	bool TypeSystem::getClassAndFieldName(std::string str,  std::string& className, std::string& fieldName) {
	    auto fieldSepPos = str.find("::");

	    if (fieldSepPos != std::string::npos) {
	        className = str.substr(0, fieldSepPos);
	        fieldName = str.substr(fieldSepPos + 2);
	        return true;
	    } else {
	    	return false;
	    }
	}
}
