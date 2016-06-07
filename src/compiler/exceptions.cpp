#include "exceptions.h"
#include "../runtime/runtime.h"
#include "../core/function.h"
#include "jit.h"
#include "callingconvention.h"
#include <string.h>

std::size_t ExceptionHandling::createHandlerCall(std::vector<unsigned char>& handlerCode, CallingConvention& callingConvention, PtrValue handlerPtr) {
	int shadowSpace = callingConvention.calculateShadowStackSize();

	auto handlerOffset = handlerCode.size();

	if (shadowSpace > 0) {
		Amd64Backend::subByteFromReg(handlerCode, Registers::SP, shadowSpace);
	}

	Amd64Backend::moveLongToReg(handlerCode, ExtendedRegisters::R11, handlerPtr); //mov r11, <addr of func>
	Amd64Backend::callInReg(handlerCode, ExtendedRegisters::R11); //call r11

	if (shadowSpace > 0) {
		Amd64Backend::addByteToReg(handlerCode, Registers::SP, shadowSpace);
	}

	return handlerOffset;
}

void ExceptionHandling::generateHandlers(MemoryManager& memoryManger, CallingConvention& callingConvention) {
	std::vector<unsigned char> handlerCode;

	//Create handler calls
	auto nullHandlerOffset = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::nullReferenceError);
	auto arrayBoundsHandlerOffset = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::arrayOutOfBoundsError);
	auto arrayCreationHandler = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::invalidArrayCreation);
	auto stackOverflowHandler = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::stackOverflow);

	//Allocate and copy memory
	auto handlerMemory = memoryManger.allocateMemory(handlerCode.size());
	memcpy(handlerMemory, handlerCode.data(), handlerCode.size());

	//Set the pointers to the handlers
	mNullCheckHandler = (unsigned char*)handlerMemory + nullHandlerOffset;
	mArrayBoundsCheckHandler = (unsigned char*)handlerMemory + arrayBoundsHandlerOffset;
	mArrayCreationCheckHandler = (unsigned char*)handlerMemory + arrayCreationHandler;
	mStackOverflowCheckHandler = (unsigned char*)handlerMemory + stackOverflowHandler;
}

void ExceptionHandling::addNullCheck(FunctionCompilationData& function, Registers refReg, ExtendedRegisters cmpReg) const {
	auto& codeGen = function.function.generatedCode();

	//Compare the reference with null
	Amd64Backend::xorRegToReg(codeGen, cmpReg, cmpReg); //Zero the register
	Amd64Backend::compareRegToReg(codeGen, refReg, cmpReg); //cmp <ref>, <cmp>

	//Jump to handler if null
	Amd64Backend::jumpEqual(codeGen, 0); //je <null handler>
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mNullCheckHandler });
}

void ExceptionHandling::addArrayBoundsCheck(FunctionCompilationData& function) const {
	auto& codeGen = function.function.generatedCode();

	//Get the size of the array (an int)
	Amd64Backend::moveMemoryByRegToReg(codeGen, Registers::CX, Registers::AX, true); //mov ecx, [rax]

	//Compare the index and size
	Amd64Backend::compareRegToReg(codeGen, ExtendedRegisters::R10, Registers::CX); //cmp r11, rcx

	//Jump to handler if out of bounds. By using an unsigned comparison, we only need one check.
	Amd64Backend::jumpGreaterThanOrEqualUnsigned(codeGen, 0); //jae <array bounds handler>.
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mArrayBoundsCheckHandler });
}

void ExceptionHandling::addArrayCreationCheck(FunctionCompilationData& function) const {
	auto& codeGen = function.function.generatedCode();

	Amd64Backend::xorRegToReg(codeGen, ExtendedRegisters::R11, ExtendedRegisters::R11); //Zero the register
	Amd64Backend::compareRegToReg(codeGen, ExtendedRegisters::R11, RegisterCallArguments::Arg1); //cmp rcx, <arg 1>

	//Jump to handler if invalid
	Amd64Backend::jumpGreaterThan(codeGen, 0); //jg <array creation handler>
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mArrayCreationCheckHandler });
}

void ExceptionHandling::addStackOverflowCheck(FunctionCompilationData& function, PtrValue callStackEnd) const {
	auto& codeGen = function.function.generatedCode();

	//Move the end of the call stack to register
	Amd64Backend::moveLongToReg(codeGen, Registers::CX, callStackEnd); //mov rcx, <call stack end>

	//Compare the top and the end of the stack
	Amd64Backend::compareRegToReg(codeGen, Registers::AX, Registers::CX); //cmp rax, rcx

	//Jump to handler if overflow
	Amd64Backend::jumpGreaterThanOrEqual(codeGen, 0); //jge <stack overflow handler>.
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mStackOverflowCheckHandler });
}