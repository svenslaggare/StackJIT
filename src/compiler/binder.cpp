#include "binder.h"
#include "../type/type.h"
#include "../core/functionsignature.h"
#include <iostream>

const std::unordered_map<std::string, FunctionDefinition>& Binder::functionTable() const {
	return mFunctionTable;
}

bool Binder::define(FunctionDefinition funcDef) {
	std::string signature = FunctionSignature::from(funcDef).str();

	if (mFunctionTable.count(signature) == 0) {
		mFunctionTable.insert({ signature, funcDef });
		return true;
	} else {
		return false;
	}
}

bool Binder::defineExternal(std::string signature, std::string externalSignature) {
	if (mFunctionTable.count(signature) == 0 && mFunctionTable.count(externalSignature) > 0) {
		auto& externalFunc = mFunctionTable[externalSignature];

		if (!externalFunc.isManaged()) {
 			mFunctionTable.insert({ signature, externalFunc });
 			return true;
		} else {
			return false;
		}
		return true;
	} else {
		return false;
	}
}

bool Binder::isDefined(std::string signature) const {
	return mFunctionTable.count(signature) > 0;
}

FunctionDefinition& Binder::getFunction(std::string signature) {
	return mFunctionTable.at(signature);
}

const FunctionDefinition& Binder::getFunction(std::string signature) const {
	return mFunctionTable.at(signature);
}

const FunctionDefinition& Binder::getFunction(const ManagedFunction& function) const {
	return mFunctionTable.at(FunctionSignature::from(function.def()).str());
}
