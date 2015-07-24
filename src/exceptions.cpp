#include "exceptions.h"
#include "memory.h"
#include "rtlibrary.h"
#include "function.h"
#include "jit.h"

//Exception handling
void ExceptionHandling::generateHandlers(MemoryManager& memoryManger) {
	std::vector<unsigned char> handlerCode;

	//Null handler
	auto nullHandlerOffset = handlerCode.size();
	Amd64Backend::moveLongToReg(handlerCode, Registers::DI, (long)&Runtime::nullReferenceError); //mov rdi, <addr of func>
	Amd64Backend::callInReg(handlerCode, Registers::DI); //call rdi

	//Array bounds handler
	auto arrayBoundsHandlerOffset = handlerCode.size();
	Amd64Backend::moveLongToReg(handlerCode, Registers::DI, (long)&Runtime::arrayOutOfBoundsError); //mov rdi, <addr of func>
	Amd64Backend::callInReg(handlerCode, Registers::DI); //call rdi

	//Array creation handler
	auto arrayCreationHandler = handlerCode.size();
	Amd64Backend::moveLongToReg(handlerCode, Registers::DI, (long)&Runtime::invalidArrayCreation); //mov rdi, <addr of func>
	Amd64Backend::callInReg(handlerCode, Registers::DI); //call rdi

	//Stack overflow handler
	auto stackOverflowHandler = handlerCode.size();
	Amd64Backend::moveLongToReg(handlerCode, Registers::DI, (long)&Runtime::stackOverflow); //mov rdi, <addr of func>
	Amd64Backend::callInReg(handlerCode, Registers::DI); //call rdi

	//Allocate and copy memory
	auto handlerMemory = memoryManger.allocateMemory(handlerCode.size());
	memcpy(handlerMemory, handlerCode.data(), handlerCode.size());

	//Set the pointers to the handlers
	mNullCheckHandler = (unsigned char*)handlerMemory + nullHandlerOffset;
	mArrayBoundsCheckHandler = (unsigned char*)handlerMemory + arrayBoundsHandlerOffset;
	mArrayCreationCheckHandler = (unsigned char*)handlerMemory + arrayCreationHandler;
	mStackOverflowCheckHandler = (unsigned char*)handlerMemory + stackOverflowHandler;
}

void ExceptionHandling::addNullCheck(FunctionCompilationData& function, Registers refReg, Registers cmpReg) const {
	auto& codeGen = function.function.generatedCode;

	//Compare the reference with null
	Amd64Backend::xorRegToReg(codeGen, cmpReg, cmpReg, true); //Zero the register
	Amd64Backend::compareRegToReg(codeGen, refReg, cmpReg); //cmp <ref>, <cmp>

	//Jump to handler if null
	Amd64Backend::jumpEqual(codeGen, 0); //je <null handler>
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (long)mNullCheckHandler });
}

void ExceptionHandling::addArrayBoundsCheck(FunctionCompilationData& function) const {
	auto& codeGen = function.function.generatedCode;

	//Get the size of the array (an int)
	Amd64Backend::moveMemoryByRegToReg(codeGen, Registers::SI, Registers::AX, true); //mov esi, [rax]

	//Compare the index and size
	Amd64Backend::compareRegToReg(codeGen, Registers::CX, Registers::SI); //cmp rcx, rsi

	//Jump to handler if out of bounds. By using an unsigned comparison, we only need one check.
	Amd64Backend::jumpGreaterThanOrEqualUnsigned(codeGen, 0); //jae <array bounds handler>.
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (long)mArrayBoundsCheckHandler });
}

void ExceptionHandling::addArrayCreationCheck(FunctionCompilationData& function) const {
	auto& codeGen = function.function.generatedCode;

	Amd64Backend::xorRegToReg(codeGen, Registers::CX, Registers::CX, true); //Zero the register
	Amd64Backend::compareRegToReg(codeGen, Registers::CX, Registers::SI); //cmp rcx, rsi

	//Jump to handler if invalid
	Amd64Backend::jumpGreaterThan(codeGen, 0); //jg <array creation handler>
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (long)mArrayCreationCheckHandler });
}

void ExceptionHandling::addStackOverflowCheck(FunctionCompilationData& function, long callStackEnd) const {
	auto& codeGen = function.function.generatedCode;

	//Move the end of the call stack to register
	Amd64Backend::moveLongToReg(codeGen, Registers::CX, callStackEnd); //mov rcx, <call stack end>

	//Compare the top and the end of the stack
	Amd64Backend::compareRegToReg(codeGen, Registers::AX, Registers::CX); //cmp rax, rcx

	//Jump to handler if overflow
	Amd64Backend::jumpGreaterThanOrEqual(codeGen, 0); //jge <stack overflow handler>.
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (long)mStackOverflowCheckHandler });
}