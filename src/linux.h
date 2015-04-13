#pragma once
#include "memory.h"
#include "callingconvention.h"

#include <vector>

//Represents a code page
class CodePage {
private:
	void* mStart;
	const std::size_t mSize;
	std::size_t mUsed;
public:
	//Creates a new code page
	CodePage(void* start, std::size_t size);
	~CodePage();

	//Prevent copies
	CodePage(const CodePage&) = delete;
	CodePage& operator=(const CodePage&) = delete;

	//Returns the size of the page
	std::size_t size() const;

	//Returns the number of bytes used
	std::size_t used() const;

	//Allocates the given memory in the page. Return nullptr if no room
	void* allocateMemory(std::size_t size);

	//Makes the page executable
	void makeExecutable();
};

//Represents a memory manager for linux
class LinuxMemoryManager : public MemoryManager {
private:
	const static std::size_t PAGE_SIZE = 4096;

	std::vector<CodePage*> mPages;

	//Creates a new page
	CodePage* newPage(std::size_t size);

	//Returns the active page
	CodePage* activePage();
public:
	//Creates a new memory manager
	LinuxMemoryManager();
	~LinuxMemoryManager();

	//Prevent copies
	LinuxMemoryManager(const LinuxMemoryManager&) = delete;
	LinuxMemoryManager& operator=(const LinuxMemoryManager&) = delete;

	virtual void* allocateMemory(std::size_t size) override;
	virtual void makeMemoryExecutable() override;
};

//Represents the calling convetions for Linux
class LinuxCallingConvention : public CallingConvention {
public:
	virtual void moveArgsToStack(FunctionCompilationData& functionData) const override;
	virtual void callFunctionArgument(FunctionCompilationData& functionData, int argIndex, const Type* argType) const override;
	virtual void callFunctionArguments(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall, GetArugmentType getArgumentType) const override;
	virtual void returnValue(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const override;
};