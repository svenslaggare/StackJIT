#pragma once
#include "amd64.h"

struct FunctionCompilationData;
class MemoryManager;

//Handles exceptions
class ExceptionHandling {
private:
	unsigned char* mNullCheckHandler;
	unsigned char* mArrayBoundsCheckHandler;
	unsigned char* mArrayCreationCheckHandler;
	unsigned char* mStackOverflowCheckHandler;
public:
	//Generates the exception handlers
	void generateHandlers(MemoryManager& memoryManger);

	//Adds a null check
	void addNullCheck(FunctionCompilationData& function, Registers refReg = Registers::AX, Registers cmpReg = Registers::SI) const;

	//Adds an array bounds check
	void addArrayBoundsCheck(FunctionCompilationData& function) const;

	//Adds an array creation check
	void addArrayCreationCheck(FunctionCompilationData& function) const;

	//Adds a stack overflow check
	void addStackOverflowCheck(FunctionCompilationData& function, long callStackEnd) const;
};
