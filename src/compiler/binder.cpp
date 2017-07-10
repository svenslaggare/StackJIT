#include "binder.h"
#include "../type/type.h"
#include "../core/functionsignature.h"
#include <iostream>

namespace stackjit {
	const std::unordered_map<std::string, FunctionDefinition>& Binder::definedFunctions() const {
		return mDefinedFunctions;
	}

	bool Binder::define(FunctionDefinition funcDef) {
		std::string signature = FunctionSignature::from(funcDef).str();

		if (mDefinedFunctions.count(signature) == 0) {
			mDefinedFunctions.insert({ signature, funcDef });
			return true;
		} else {
			return false;
		}
	}

	bool Binder::isDefined(const std::string& signature) const {
		return mDefinedFunctions.count(signature) > 0;
	}

	FunctionDefinition& Binder::getFunction(const std::string& signature) {
		return mDefinedFunctions.at(signature);
	}

	const FunctionDefinition& Binder::getFunction(const std::string& signature) const {
		return mDefinedFunctions.at(signature);
	}
}
