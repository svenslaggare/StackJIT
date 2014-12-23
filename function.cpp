#include "function.h"
#include "codegenerator.h"
#include <stdexcept>
#include <sys/mman.h>

Function::Function(std::string name, std::vector<const Type*> arguments, const Type* returnType)
	: mName(name), mArguments(arguments), mReturnType(returnType), mStackSize(0) {

}

std::string Function::name() const {
	return mName;
}

const std::vector<const Type*>& Function::arguments() const {
	return mArguments;
}

int Function::numArgs() const {
	return mArguments.size();
}

const Type* Function::returnType() const {
	return mReturnType;
}

int Function::numLocals() const {
	return mLocalTypes.size();
}

void Function::setNumLocals(int count) {
	mLocalTypes.resize(count);
}

const Type* Function::getLocal(int index) const {
	return mLocalTypes.at(index);
}

void Function::setLocal(int index, const Type* type) {
	mLocalTypes.at(index) = type;
}

int Function::stackSize() const {
	return mStackSize;
}

void Function::setStackSize(int size) {
	mStackSize = size;
}

FunctionDefinition::FunctionDefinition(std::vector<const Type*> arguments, const Type* returnType, long entryPoint, int funcSize)
    : mArguments(arguments), mReturnType(returnType), mEntryPoint(entryPoint), mFunctionSize(funcSize), mIsManaged(true) {

}

FunctionDefinition::FunctionDefinition(std::vector<const Type*> arguments, const Type* returnType, long entryPoint)
    : mArguments(arguments), mReturnType(returnType), mEntryPoint(entryPoint), mFunctionSize(0), mIsManaged(false) {

}

FunctionDefinition::FunctionDefinition()
    : mEntryPoint(0), mFunctionSize(0), mIsManaged(false), mReturnType(nullptr) {

}

void FunctionDefinition::setFunctionBody(long entryPoint, int functionSize) {
    if (mIsManaged) {
        mEntryPoint = entryPoint;
        mFunctionSize = functionSize;
    }
}

const Type* FunctionDefinition::returnType() const {
    return mReturnType;
}

const std::vector<const Type*>& FunctionDefinition::arguments() const {
    return mArguments;
}

bool FunctionDefinition::isManaged() const {
    return mIsManaged;
}

long FunctionDefinition::entryPoint() const {
    return mEntryPoint;
}

int FunctionDefinition::functionSize() const {
    return mFunctionSize;
}

void FunctionDefinition::deleteCodeMemory() {
    if (functionSize() > 0) {
        munmap((unsigned char*)entryPoint(), functionSize());
        mFunctionSize = 0;
        mEntryPoint = 0;
    }
}