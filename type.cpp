#include "type.h"
#include <vector>
#include <regex>
#include <iostream>

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

bool Type::operator!=(const Type& type) const {
	return !(*this == type);
}

ReferenceType::ReferenceType(std::string name): Type("Ref." + name) {

}

ArrayType::ArrayType(Type* elementType): ReferenceType("Array[" + elementType->name() + "]"), mElementType(elementType) {

}

ArrayType::~ArrayType() {
	delete mElementType;
}

StructType::StructType(std::string name): ReferenceType("Struct." + name) {

}

std::string TypeSystem::getPrimitiveTypeName(PrimitiveTypes primitiveType) {
	switch (primitiveType) {
		case PrimitiveTypes::Void:
			return "Primitive.Void";
		case PrimitiveTypes::Integer:
			return "Primitive.Integer";
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

	//Check if primitive or reference
	if (typeParts[0] == "Primitive") {
		if (typeParts.size() == 2) {
			std::string primType = typeParts[1];

			if (primType == "Integer") {
				return new Type(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer));
			} else if (primType == "Void") {
				return new Type(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Void));
			}
		}
	} else if (typeParts[0] == "Ref") {
		std::smatch match;
		bool foundArray = std::regex_match(typeParts[1], match, arrayRegex);

		if (foundArray) {
			std::string elementType = match[1].str();
			elementType = elementType.substr(1, elementType.length() - 2);
			return new ArrayType(makeTypeFromString(elementType));
		} else if (typeParts[1] == "Struct") {
			if (typeParts.size() == 3) {
				return new StructType(typeParts[2]);
			}
		}
	}

	return nullptr;
}

bool TypeSystem::isPrimitiveType(Type* type, PrimitiveTypes primitiveType) {
	if (type != nullptr) {
		switch (primitiveType) {
			case PrimitiveTypes::Integer:
				return type->name().compare("Primitive.Integer") == 0;
			case PrimitiveTypes::Void:
				return type->name().compare("Primitive.Void") == 0;
		}
	}

	return false;
}

bool TypeSystem::isArray(Type* type) {
	if (type == nullptr) {
		return false;
	}

	auto typeName = type->name();
	return typeName.find("Array.", 0, typeName.length());
}