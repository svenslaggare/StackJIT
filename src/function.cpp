#include "function.h"
#include "codegenerator.h"

ManagedFunction::ManagedFunction(const FunctionDefinition& definition, bool isConstructor)
	: mDefinition(definition),
	  mStackSize(0),
	  mOperandStackSize(0),
	  mIsConstructor(isConstructor) {

}

std::string ManagedFunction::name() const {
	return mDefinition.name();
}

const std::vector<const Type*>& ManagedFunction::parameters() const {
	return mDefinition.parameters();
}

std::size_t ManagedFunction::numParams() const {
	return mDefinition.parameters().size();
}

const Type* ManagedFunction::returnType() const {
	return mDefinition.returnType();
}

bool ManagedFunction::isMemberFunction() const {
    return mIsMemberFunction;
}

bool ManagedFunction::isConstructor() const {
    return mIsConstructor;
}

std::size_t ManagedFunction::numLocals() const {
	return mLocalTypes.size();
}

void ManagedFunction::setNumLocals(std::size_t count) {
	mLocalTypes.resize(count);
}

const Type* ManagedFunction::getLocal(std::size_t index) const {
	return mLocalTypes.at(index);
}

void ManagedFunction::setLocal(std::size_t index, const Type* type) {
	mLocalTypes.at(index) = type;
}

std::size_t ManagedFunction::stackSize() const {
	return mStackSize;
}

void ManagedFunction::setStackSize(std::size_t size) {
	mStackSize = size;
}

std::size_t ManagedFunction::operandStackSize() const {
    return mOperandStackSize;
}

void ManagedFunction::setOperandStackSize(std::size_t size) {
    mOperandStackSize = size;
}

FunctionDefinition::FunctionDefinition(
    std::string name,
    std::vector<const Type*> parameters,
    const Type* returnType,
    bool isMemberFunction)
    : mName(name),
      mParameters(parameters),
      mReturnType(returnType),
      mEntryPoint(nullptr),
      mIsManaged(true),
      mIsMemberFunction(isMemberFunction) {

}

FunctionDefinition::FunctionDefinition(
	std::string name,
	std::vector<const Type*> parameters,
	const Type* returnType,
	unsigned char* entryPoint,
	bool isMemberFunction)
    : mName(name),
      mParameters(parameters),
      mReturnType(returnType),
      mEntryPoint(entryPoint),
      mIsManaged(false),
      mIsMemberFunction(isMemberFunction) {

}

FunctionDefinition::FunctionDefinition()
    : mName(""), mReturnType(nullptr), mEntryPoint(nullptr),
	  mIsManaged(false), mIsMemberFunction(false) {

}

std::string FunctionDefinition::name() const {
    return mName;
}

const Type* FunctionDefinition::returnType() const {
    return mReturnType;
}

const std::vector<const Type*>& FunctionDefinition::parameters() const {
    return mParameters;
}

bool FunctionDefinition::isMemberFunction() const {
    return mIsMemberFunction;
}

bool FunctionDefinition::isManaged() const {
    return mIsManaged;
}

void FunctionDefinition::setEntryPoint(unsigned char* entryPoint) {
    if (mIsManaged) {
        mEntryPoint = entryPoint;
    }
}

unsigned char* FunctionDefinition::entryPoint() const {
    return mEntryPoint;
}