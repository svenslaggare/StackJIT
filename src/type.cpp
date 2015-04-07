#include "type.h"

#include <vector>
#include <regex>
#include <iostream>
#include <unordered_map>
#include <functional>

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

StructType::StructType(std::string name)
	: ReferenceType("Struct." + name), mStructName(name) {

}

std::string StructType::structName() const {
	return mStructName;
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

Type* TypeSystem::makeTypeFromString(std::string typeName) {
	//Split the type name
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

	std::string arrayPattern = "Array.(.*).";
	std::regex arrayRegex(arrayPattern, std::regex_constants::extended);
	PrimitiveTypes primType;

	if (fromString(typeParts.at(0), primType)) {
		return new Type(typeParts.at(0));
	} else if (typeParts.at(0) == "Ref") {
		std::smatch match;
		bool foundArray = std::regex_match(typeParts.at(1), match, arrayRegex);

		if (foundArray) {
			std::string elementType = match[1].str();
			elementType = elementType.substr(1, elementType.length() - 2);
			return new ArrayType(makeTypeFromString(elementType));
		} else if (typeParts[1] == "Struct") {
			if (typeParts.size() >= 3) {
				std::string structName = "";
				bool isFirst = true;

				for (int i = 2; i < typeParts.size(); i++) {
					if (isFirst) {
						isFirst = false;
					} else {
						structName += ".";
					}

					structName += typeParts[i];
				}

				return new StructType(structName);
			}
		} else if (typeParts.at(1) == "Null") {
			return new NullReferenceType();
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

	return type->name().find("Ref.") != std::string::npos;
}

bool TypeSystem::isArray(const Type* type) {
	if (type == nullptr) {
		return false;
	}

	return type->name().find("Ref.Array") != std::string::npos;
}

bool TypeSystem::isStruct(const Type* type) {
	if (type == nullptr) {
		return false;
	}

	return type->name().find("Ref.Struct.") != std::string::npos;
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
		return sizeof(long);
	}

	return 0;
}

bool TypeSystem::getStructAndField(std::string str, std::pair<std::string, std::string>& res) {
    auto fieldSepPos = str.find("::");

    if (fieldSepPos != std::string::npos) {
        auto structName = str.substr(0, fieldSepPos);
        auto fieldName = str.substr(fieldSepPos + 2);

        res.first = structName;
        res.second = fieldName;

        return true;
    } else {
    	return false;
    }
}