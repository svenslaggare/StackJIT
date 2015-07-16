#include "function.h"
#include "codegenerator.h"
#include "memory.h"

Function::Function(std::string name, std::vector<const Type*> parameters, const Type* returnType, bool isMemberFunction, bool isConstructor)
	: mName(name),
      mParameters(parameters),
      mReturnType(returnType),
      mStackSize(0), 
      mOperandStackSize(0),
      mIsMemberFunction(isMemberFunction),
      mIsConstructor(isConstructor) {

}

std::string Function::name() const {
	return mName;
}

const std::vector<const Type*>& Function::parameters() const {
	return mParameters;
}

std::size_t Function::numParams() const {
	return mParameters.size();
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

std::size_t Function::numLocals() const {
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


MacroFunctionContext::MacroFunctionContext(
	const VMState& vmState,
	const CallingConvention& callingConvention,
	const ExceptionHandling& exceptionHandling,
	FunctionCompilationData& functionData,
	const Instruction& inst,
	const int instIndex)
	: vmState(vmState),
	  callingConvention(callingConvention),
	  exceptionHandling(exceptionHandling),
	  functionData(functionData),
	  inst(inst),
	  instIndex(instIndex) {

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
      mIsMemberFunction(isMemberFunction),
	  mIsMacroFunction(false) {

}

FunctionDefinition::FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, long entryPoint)
    : mName(name),
      mArguments(parameters),
      mReturnType(returnType),
      mEntryPoint(entryPoint),
      mFunctionSize(0),
      mIsManaged(false),
      mIsMemberFunction(false),
	  mIsMacroFunction(false) {

}

FunctionDefinition::FunctionDefinition(std::string name, std::vector<const Type*> parameters, const Type* returnType, MacroFunction macroFunction)
	: mName(name),
	  mArguments(parameters),
	  mReturnType(returnType),
	  mEntryPoint(0),
	  mFunctionSize(0),
	  mIsManaged(false),
	  mIsMemberFunction(false),
	  mIsMacroFunction(true),
	  mMacroFunction(macroFunction) {

}

FunctionDefinition::FunctionDefinition()
    : mName(""), mReturnType(nullptr), mEntryPoint(0), mFunctionSize(0),
	  mIsManaged(false), mIsMemberFunction(false),
	  mIsMacroFunction(false) {

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

bool FunctionDefinition::isMacroFunction() const {
	return mIsMacroFunction;
}

MacroFunction FunctionDefinition::macroFunction() const {
	return mMacroFunction;
}
