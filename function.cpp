#include "function.h"
#include "codegenerator.h"
#include <stdexcept>

Function::Function(std::string name, std::vector<Type*> arguments, Type* returnType)
	: mName(name), mArguments(arguments), mReturnType(returnType), mStackSize(0) {

}

std::string Function::name() const {
	return mName;
}

const std::vector<Type*>& Function::arguments() const {
	return mArguments;
}

int Function::numArgs() const {
	return mArguments.size();
}

Type* Function::returnType() const {
	return mReturnType;
}

int Function::numLocals() const {
	return mLocalTypes.size();
}

void Function::setNumLocals(int count) {
	mLocalTypes.resize(count);
}

Type* Function::getLocal(int index) const {
	return mLocalTypes.at(index);
}

void Function::setLocal(int index, Type* type) {
	mLocalTypes.at(index) = type;
}

int Function::stackSize() const {
	return mStackSize;
}

void Function::setStackSize(int size) {
	mStackSize = size;
}