#include "binder.h"
#include "verifier.h"
#include "type.h"
#include <iostream>

const std::unordered_map<std::string, FunctionDefinition>& Binder::functionTable() const {
	return mFunctionTable;
}

std::string Binder::functionSignature(std::string name, const std::vector<const Type*>& parameters) const {
	std::string argsStr = "";
    bool isFirst = true;

    for (auto param : parameters) {
        if (isFirst) {
            isFirst = false;
        } else {
            argsStr += " ";
        }

        argsStr += Verifier::typeToString(param);
    }

    return name + "(" + argsStr + ")";
}

std::string Binder::memberFunctionSignature(const ClassType* structType, std::string name, const std::vector<const Type*>& parameters) const {
	auto params = parameters;
	params.insert(params.begin(), structType);
	return functionSignature(structType->className() + "::" + name, params);
}

std::string Binder::functionSignature(const FunctionDefinition& funcDef) const {
	return functionSignature(funcDef.name(), funcDef.parameters());
}

std::string Binder::functionSignature(const Function& func) const {
	return functionSignature(func.name(), func.parameters());
}

bool Binder::define(FunctionDefinition funcDef) {
	std::string signature = functionSignature(funcDef);

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