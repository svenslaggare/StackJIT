#include "exceptions.h"
#include "../runtime/runtime.h"
#include "../core/function.h"
#include "jit.h"
#include "callingconvention.h"
#include <string.h>

namespace stackjit {
	std::size_t ExceptionHandling::createHandlerCall(CodeGen& handlerCode, CallingConvention& callingConvention, PtrValue handlerPtr) {
		Amd64Assembler assembler(handlerCode);
		auto handlerOffset = handlerCode.size();

		int shadowSpace = callingConvention.calculateShadowStackSize();
		if (shadowSpace > 0) {
			assembler.sub(Registers::SP, shadowSpace);
		}

		assembler.moveLong(ExtendedRegisters::R11, handlerPtr);
		assembler.call(ExtendedRegisters::R11);

		if (shadowSpace > 0) {
			assembler.add(Registers::SP, shadowSpace);
		}

		return handlerOffset;
	}

	void ExceptionHandling::generateHandlers(MemoryManager& memoryManger, CallingConvention& callingConvention) {
		CodeGen handlerCode;

		//Create handler calls
		auto nullHandlerOffset = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::nullReferenceError);
		auto arrayBoundsHandlerOffset = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::arrayOutOfBoundsError);
		auto arrayCreationHandler = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::invalidArrayCreation);
		auto stackOverflowHandler = createHandlerCall(handlerCode, callingConvention, (PtrValue)&Runtime::stackOverflow);

		//Allocate and copy memory
		auto handlerMemory = memoryManger.allocateMemory(handlerCode.size());
		memcpy(handlerMemory, handlerCode.data(), handlerCode.size());

		//Set the pointers to the handlers
		mNullCheckHandler = (BytePtr)handlerMemory + nullHandlerOffset;
		mArrayBoundsCheckHandler = (BytePtr)handlerMemory + arrayBoundsHandlerOffset;
		mArrayCreationCheckHandler = (BytePtr)handlerMemory + arrayCreationHandler;
		mStackOverflowCheckHandler = (BytePtr)handlerMemory + stackOverflowHandler;
	}

	void ExceptionHandling::addNullCheck(FunctionCompilationData& function, Registers refReg, ExtendedRegisters cmpReg) const {
		auto& codeGen = function.function.generatedCode();
		Amd64Assembler assembler(codeGen);

		//Compare the reference with null
		assembler.bitwiseXor(cmpReg, cmpReg); //Zero the register
		assembler.compare(refReg, cmpReg);

		//Jump to handler if null
		assembler.jump(JumpCondition::Equal, 0);
		function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mNullCheckHandler });
	}

	void ExceptionHandling::addArrayBoundsCheck(FunctionCompilationData& function) const {
		auto& codeGen = function.function.generatedCode();
		Amd64Assembler assembler(codeGen);

		//Get the size of the array (an int)
		assembler.move(Registers::CX, MemoryOperand(Registers::AX), DataSize::Size32);

		//Compare the index and size
		assembler.compare(ExtendedRegisters::R10, Registers::CX);

		//Jump to handler if out of bounds. By using an unsigned comparison, we only need one check.
		assembler.jump(JumpCondition::GreaterThanOrEqual, 0, true);
		function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mArrayBoundsCheckHandler });
	}

	void ExceptionHandling::addArrayCreationCheck(FunctionCompilationData& function) const {
		auto& codeGen = function.function.generatedCode();
		Amd64Assembler assembler(codeGen);

		assembler.bitwiseXor(ExtendedRegisters::R11, ExtendedRegisters::R11); //Zero the register
		assembler.compare(ExtendedRegisters::R11, RegisterCallArguments::Arg1);

		//Jump to handler if invalid
		assembler.jump(JumpCondition::GreaterThan, 0);
		function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mArrayCreationCheckHandler });
	}

	void ExceptionHandling::addStackOverflowCheck(FunctionCompilationData& function, PtrValue callStackEnd) const {
		auto& codeGen = function.function.generatedCode();
		Amd64Assembler assembler(codeGen);

		//Move the end of the call stack to register
		assembler.moveLong(Registers::CX, callStackEnd);

		//Compare the top and the end of the stack
		assembler.compare(Registers::AX, Registers::CX);

		//Jump to handler if overflow
		assembler.jump(JumpCondition::GreaterThanOrEqual, 0);
		function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (PtrValue)mStackOverflowCheckHandler });
	}
}
