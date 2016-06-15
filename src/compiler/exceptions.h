#pragma once
#include "amd64.h"
#include "../stackjit.h"

namespace stackjit {
	struct FunctionCompilationData;
	class MemoryManager;
	class CallingConvention;

	//Handles exceptions
	class ExceptionHandling {
	private:
		unsigned char* mNullCheckHandler;
		unsigned char* mArrayBoundsCheckHandler;
		unsigned char* mArrayCreationCheckHandler;
		unsigned char* mStackOverflowCheckHandler;

		//Creates a call to the given handler
		std::size_t createHandlerCall(std::vector<unsigned char>& handlerCode, CallingConvention& callingConvention, PtrValue handlerPtr);
	public:
		//Generates the exception handlers
		void generateHandlers(MemoryManager& memoryManger, CallingConvention& callingConvention);

		//Adds a null check
		void addNullCheck(FunctionCompilationData& function, Registers refReg = Registers::AX, ExtendedRegisters cmpReg = ExtendedRegisters::R11) const;

		//Adds an array bounds check
		void addArrayBoundsCheck(FunctionCompilationData& function) const;

		//Adds an array creation check
		void addArrayCreationCheck(FunctionCompilationData& function) const;

		//Adds a stack overflow check
		void addStackOverflowCheck(FunctionCompilationData& function, PtrValue callStackEnd) const;
	};
}
