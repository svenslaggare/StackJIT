#include "binder.h"
#include "typechecker.h"

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

        argsStr += TypeChecker::typeToString(param);
    }

    return name + "(" + argsStr + ")";
}

std::string Binder::functionSignature(const FunctionDefinition& funcDef) const {
	return functionSignature(funcDef.name(), funcDef.arguments());
}

bool Binder::define(FunctionDefinition funcDef) {
	auto signature = functionSignature(funcDef);

	if (mFunctionTable.count(signature) == 0) {
		mFunctionTable.insert({ signature, funcDef });
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

FunctionDefinition& Binder::operator[](std::string signature) {
	return getFunction(signature);
}

const FunctionDefinition& Binder::operator[](std::string signature) const {
	return getFunction(signature);
}