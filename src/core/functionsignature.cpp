#include "functionsignature.h"
#include "../type/type.h"
#include "function.h"

namespace stackjit {
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
		return FunctionSignature::createSignature<const Type*>(name, parameters, [](const Type* type) { return type->name(); });
	}

	FunctionSignature FunctionSignature::memberFunction(const ClassType* classType, std::string name, const std::vector<const Type*>& parameters) {
		return FunctionSignature::function(classType->className() + "::" + name, parameters);
	}

	FunctionSignature FunctionSignature::from(const FunctionDefinition& function) {
		return FunctionSignature::function(function.name(), function.callParameters());
	}

	std::ostream& operator<<(std::ostream& os, const FunctionSignature& signature) {
		os << signature.str();
		return os;
	}
}
