#include "functionsignature.h"
#include "../type/type.h"
#include "function.h"

std::string FunctionSignature::str() const {
	return mSignature;
}

FunctionSignature::FunctionSignature(std::string signature)
	: mSignature(signature) {

}

bool FunctionSignature::operator==(const FunctionSignature& rhs) const {
	return mSignature == rhs.mSignature;
}

bool FunctionSignature::operator!=(const FunctionSignature& rhs) const {
	return mSignature != rhs.mSignature;
}

FunctionSignature FunctionSignature::function(std::string name, const std::vector<const Type*>& parameters) {
	std::string argsStr = "";
	bool isFirst = true;

	for (auto param : parameters) {
		if (isFirst) {
			isFirst = false;
		} else {
			argsStr += " ";
		}

		argsStr += param->name();
	}

	return name + "(" + argsStr + ")";
}

FunctionSignature FunctionSignature::memberFunction(const ClassType* classType, std::string name, const std::vector<const Type*>& parameters) {
	auto params = parameters;
	params.insert(params.begin(), classType);
	return FunctionSignature::function(classType->className() + "::" + name, params);
}

FunctionSignature FunctionSignature::from(const FunctionDefinition& function) {
	return FunctionSignature::function(function.name(), function.parameters());
}

std::ostream& operator<<(std::ostream& os, const FunctionSignature& signature) {
	os << signature.str();
	return os;
}
