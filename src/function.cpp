#include "function.h"
#include "codegenerator.h"
#include <stdexcept>
#include <sys/mman.h>

Function::Function(std::string name, std::vector<const Type*> arguments, const Type* returnType, bool isMemberFunction, bool isConstructor)
	: mName(name),
      mArguments(arguments),
      mReturnType(returnType),
      mStackSize(0), 
      mOperandStackSize(0),
      mIsMemberFunction(isMemberFunction),
      mIsConstructor(isConstructor) {

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

bool Function::isMemberFunction() const {
    return mIsMemberFunction;
}

bool Function::isConstructor() const {
    return mIsConstructor;
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

std::size_t Function::stackSize() const {
	return mStackSize;
}

void Function::setStackSize(std::size_t size) {
	mStackSize = size;
}

std::size_t Function::operandStackSize() const {
    return mOperandStackSize;
}

void Function::setOperandStackSize(std::size_t size) {
    mOperandStackSize = size;
}

FunctionDefinition::FunctionDefinition(
    std::string name,
    std::vector<const Type*> parameters,
    const Type* returnType,
    long entryPoint, 
    int funcSize,
    bool isMemberFunction)
    : mName(name),
      mArguments(parameters),
      mReturnType(returnType),
      mEntryPoint(entryPoint),
      mFunctionSize(funcSize),
      mIsManaged(true),
      mIsMemberFunction(isMemberFunction) {

}

FunctionDefinition::FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, long entryPoint)
    : mName(name), mArguments(parameters), mReturnType(returnType), mEntryPoint(entryPoint), mFunctionSize(0), mIsManaged(false), mIsMemberFunction(false) {

}

FunctionDefinition::FunctionDefinition()
    : mName(""), mEntryPoint(0), mFunctionSize(0), mIsManaged(false), mReturnType(nullptr), mIsMemberFunction(false) {

}

std::string FunctionDefinition::name() const {
    return mName;
}

const Type* FunctionDefinition::returnType() const {
    return mReturnType;
}

const std::vector<const Type*>& FunctionDefinition::arguments() const {
    return mArguments;
}

bool FunctionDefinition::isMemberFunction() const {
    return mIsMemberFunction;
}

bool FunctionDefinition::isManaged() const {
    return mIsManaged;
}

void FunctionDefinition::setFunctionBody(long entryPoint, int functionSize) {
    if (mIsManaged) {
        mEntryPoint = entryPoint;
        mFunctionSize = functionSize;
    }
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