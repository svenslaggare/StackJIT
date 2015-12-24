#include "function.h"

ManagedFunction::ManagedFunction(const FunctionDefinition& definition)
	: mDefinition(definition),
	  mOperandStackSize(0) {

}

const FunctionDefinition& ManagedFunction::def() const {
	return mDefinition;
}

std::vector<Instruction>& ManagedFunction::instructions() {
	return mInstructions;
}

const std::vector<Instruction>& ManagedFunction::instructions() const {
	return mInstructions;
}

std::vector<unsigned char>& ManagedFunction::generatedCode() {
	return mGeneratedCode;
}

const std::vector<unsigned char>& ManagedFunction::generatedCode() const {
	return mGeneratedCode;
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
	const ClassType* classType,
	AccessModifier accessModifier,
	bool isConstructor)
    : mName(name),
      mParameters(parameters),
      mReturnType(returnType),
      mEntryPoint(nullptr),
      mIsManaged(true),
      mIsMemberFunction(classType != nullptr),
	  mClassType(classType),
	  mAccessModifier(accessModifier),
	  mIsConstructor(isConstructor)
	  {

}

FunctionDefinition::FunctionDefinition(
	std::string name,
	std::vector<const Type*> parameters,
	const Type* returnType,
	unsigned char* entryPoint,
	const ClassType* classType,
	AccessModifier accessModifier,
	bool isConstructor)
    : mName(name),
      mParameters(parameters),
      mReturnType(returnType),
      mEntryPoint(entryPoint),
      mIsManaged(false),
	  mIsMemberFunction(classType != nullptr),
	  mClassType(classType),
	  mAccessModifier(accessModifier),
	  mIsConstructor(isConstructor) {

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

std::size_t FunctionDefinition::numParams() const {
	return mParameters.size();
}

bool FunctionDefinition::isManaged() const {
	return mIsManaged;
}

bool FunctionDefinition::isMemberFunction() const {
    return mIsMemberFunction;
}

const ClassType* FunctionDefinition::classType() const {
	return mClassType;
}

AccessModifier FunctionDefinition::accessModifier() const {
	return mAccessModifier;
}

bool FunctionDefinition::isConstructor() const {
	return mIsConstructor;
}

void FunctionDefinition::setEntryPoint(unsigned char* entryPoint) {
    if (mIsManaged) {
        mEntryPoint = entryPoint;
    }
}

unsigned char* FunctionDefinition::entryPoint() const {
    return mEntryPoint;
}