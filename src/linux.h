#pragma once
#include "memory.h"
#include "callingconvention.h"

//Represents a memory manager for linux
class LinuxMemoryManager : public MemoryManager {
public:
	virtual void* allocateMemory(std::size_t size) override;
	virtual void makeExecutableMemory(void* memory, std::size_t size) override;
};

//Represents the calling convetions for Linux
class LinuxCallingConvention : public CallingConvention {
public:
	virtual void moveArgsToStack(FunctionCompilationData& functionData) const override;
	virtual void callFunctionArgument(FunctionCompilationData& functionData, int argIndex, const Type* argType) const override;
	virtual void callFunctionArguments(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall, GetArugmentType getArgumentType) const override;
	virtual void returnValue(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const override;
};