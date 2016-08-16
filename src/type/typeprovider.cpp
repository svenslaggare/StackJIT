#include "typeprovider.h"
#include "type.h"

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

namespace stackjit {
	TypeProvider::TypeProvider(ClassMetadataProvider& classMetadataProvider)
		: mClassMetadataProvider(classMetadataProvider) {

	}

	TypeProvider::~TypeProvider() {
		for (auto type : mTypes) {
	        delete type.second;
	    }
	}

	const Type* TypeProvider::makeType(std::string name) {
		if (mTypes.count(name) > 0) {
			return mTypes[name];
		}

		//Split the type name
		auto typeParts = splitTypeName(name);
		PrimitiveTypes primitiveType;
		Type* type = nullptr;

		if (TypeSystem::fromString(typeParts.at(0), primitiveType)) {
			type = new Type(typeParts.at(0));
		} else if (typeParts.at(0) == "Ref") {
			std::string elementType;
			if (extractElementType(typeParts.at(1), elementType)) {
				type = new ArrayType(makeType(elementType));
			} else if (typeParts.at(1) == "Null") {
				type = new NullReferenceType();
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

					if (mClassMetadataProvider.isDefined(className)) {
						type = new ClassType(className, &mClassMetadataProvider.getMetadata(className));
					}
				}
			}
		}

		mTypes.insert({ name, type });
		return type;
	}

	const Type* TypeProvider::getType(std::string name) const {
		if (mTypes.count(name) > 0) {
	        return mTypes.at(name);
	    } else {
	        return nullptr;
	    }
	}
}
