#include "type.h"
#include "classmetadata.h"

#include <vector>
#include <iostream>
#include <unordered_map>

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
	delete mElementType;
}

ClassType::ClassType(std::string name)
	: ReferenceType(name), mClassName(name) {

}

std::string ClassType::className() const {
	return mClassName;
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

namespace {
	//Splits the given type name
	std::vector<std::string> splitTypeName(std::string typeName) {
		std::string token;
		std::vector<std::string> typeParts;

		bool isInsideBrackets = false;
		for (char c : typeName) {
			if (!isInsideBrackets) {
				if (c == '[') {
					isInsideBrackets = true;
				}
			} else {
				if (c == ']') {
					isInsideBrackets = false;
				}
			}

			if (c == '.' && !isInsideBrackets) {
				typeParts.push_back(token);
				token = "";
			} else {
				token += c;
			}
		}

		typeParts.push_back(token);

		return typeParts;
	}

	//Extracts the element type from the given type part. Returns true if extracted.
	bool extractElementType(std::string typePart, std::string& elementPart) {
		std::string buffer;
		bool foundArrayElement = false;
		bool foundStart = false;
		int bracketCount = 0;

		for (char c : typePart) {
			if (c == '[') {
				bracketCount++;
			}

			if (c == ']') {
				bracketCount--;
			}

			if (c == ']' && bracketCount == 0) {
				if (foundStart) {
					foundArrayElement = true;
				}

				break;
			}

			buffer += c;

			if (buffer == "Array[" && !foundStart) {
				foundStart = true;
				buffer.clear();
			}
		}

		if (foundArrayElement) {
			elementPart = buffer;
			return  true;
		} else {
			return false;
		}
	}
}

Type* TypeSystem::makeTypeFromString(std::string typeName, const ClassMetadataProvider& classProvider) {
	//Split the type name
	std::vector<std::string> typeParts = splitTypeName(typeName);
	PrimitiveTypes primitiveType;

	if (fromString(typeParts.at(0), primitiveType)) {
		return new Type(typeParts.at(0));
	} else if (typeParts.at(0) == "Ref") {
		std::string elementType;
		if (extractElementType(typeParts.at(1), elementType)) {
			return new ArrayType(makeTypeFromString(elementType, classProvider));
		} else if (typeParts.at(1) == "Null") {
			return new NullReferenceType();
		} else {
			if (typeParts.size() >= 2) {
				std::string className = "";
				bool isFirst = true;

				for (std::size_t i = 1; i < typeParts.size(); i++) {
					if (isFirst) {
						isFirst = false;
					} else {
						className += ".";
					}

					className += typeParts.at(i);
				}

				if (classProvider.isDefined(className)) {
					return new ClassType(className);
				} else {
					return nullptr;
				}
			}
		}
	}

	return nullptr;
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

bool TypeSystem::getClassAndFieldName(std::string str, std::pair<std::string, std::string>& res) {
    auto fieldSepPos = str.find("::");

    if (fieldSepPos != std::string::npos) {
        auto className = str.substr(0, fieldSepPos);
        auto fieldName = str.substr(fieldSepPos + 2);

        res.first = className;
        res.second = fieldName;

        return true;
    } else {
    	return false;
    }
}