#include "linux.h"
#include "amd64.h"
#include "jit.h"
#include "function.h"
#include "type.h"

#include <iostream>
#include <sys/mman.h>

CodePage::CodePage(void* start, std::size_t size)
    : mStart(start), mSize(size), mUsed(0) {

}

CodePage::~CodePage() {
    munmap(mStart, mSize);
}

void* CodePage::start() const {
    return mStart;
}

std::size_t CodePage::size() const {
    return mSize;
}

std::size_t CodePage::used() const {
    return mUsed;
}

void* CodePage::allocateMemory(std::size_t size) {
    if (mUsed + size < mSize) {
        void* newPtr = (char*)mStart + mUsed;
        mUsed += size;
        return newPtr;
    } else {
        return nullptr;
    }
}

void CodePage::makeExecutable() {
    int success = mprotect(mStart, mSize, PROT_EXEC | PROT_READ);

	if (success != 0) {
		throw std::runtime_error("Unable to make memory executable.");
	}
}

LinuxMemoryManager::LinuxMemoryManager() {

}

LinuxMemoryManager::~LinuxMemoryManager() {
    for (auto codePage : mPages) {
        delete codePage;
    }
}

CodePage* LinuxMemoryManager::newPage(std::size_t size) {
    //Align to page size
    size = ((size + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE;

    void *mem = mmap(
        nullptr,
        size,
        PROT_WRITE | PROT_READ,
        MAP_ANON | MAP_PRIVATE,
        -1,
        0);

    if (mem == MAP_FAILED) {
        throw std::runtime_error("Unable to allocate memory.");
    }

    auto newPage = new CodePage(mem, size);
    mPages.push_back(newPage);
    return newPage;
}

void* LinuxMemoryManager::allocateMemory(std::size_t size) {
    CodePage* page = nullptr;

    //Find a page with enough size
    for (auto currentPage : mPages) {
        if (currentPage->used() + size < currentPage->size()) {
            page = currentPage;
            break;
        }
    }

    if (page == nullptr) {
        page = newPage(size);
    }

    return page->allocateMemory(size);
}

void LinuxMemoryManager::makeMemoryExecutable() {
	for (auto codePage : mPages) {
        codePage->makeExecutable();
    }
}

namespace {
	//The maximum number of register for argument passing
	const int NUM_NONE_FLOAT_ARGUMENT_REGISTERS = 6;
	const int NUM_FLOAT_ARGUMENT_REGISTERS = 8;

	//Returns the float argument index for the given argument index
	int getFloatArgIndex(const std::vector<const Type*>& parameters, int argIndex) {
		int floatArgIndex = 0;

		int index = 0;
		for (auto param : parameters) {
			if (index == argIndex) {
				break;
			}

			if (TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
				floatArgIndex++;
			}

			index++;
		}

		return floatArgIndex;
	}

	//Returns the none float arg for the given argument index
	int getNoneFloatArgIndex(const std::vector<const Type*>& parameters, int argIndex) {
		int noneFloatArgIndex = 0;

		int index = 0;
		for (auto param : parameters) {
			if (index == argIndex) {
				break;
			}

			if (!TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
				noneFloatArgIndex++;
			}

			index++;
		}

		return noneFloatArgIndex;
	}

	//Calculates the number of arguments that are passed via the stack
	int numStackArguments(FunctionCompilationData& functionData) {
		int stackArgs = 0;
		auto& parameters = functionData.function.parameters();

		int argIndex = 0;
		for (auto param : parameters) {
			if (TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
				if (getFloatArgIndex(parameters, argIndex) >= NUM_FLOAT_ARGUMENT_REGISTERS) {
					stackArgs++;
				}
			} else {
				if (getNoneFloatArgIndex(parameters, argIndex) >= NUM_NONE_FLOAT_ARGUMENT_REGISTERS) {
					stackArgs++;
				}
			}

			argIndex++;
		}

		return stackArgs;
	}

	//Returns the stack argument index for the given argument
	int getStackArgumentIndex(FunctionCompilationData& functionData, int argIndex) {
		int stackArgIndex = 0;
		auto& parameters = functionData.function.parameters();

		int index = 0;
		for (auto param : parameters) {
			if (index == argIndex) {
				break;
			}

			if (TypeSystem::isPrimitiveType(param, PrimitiveTypes::Float)) {
				if (getFloatArgIndex(parameters, index) >= NUM_FLOAT_ARGUMENT_REGISTERS) {
					stackArgIndex++;
				}
			} else {
				if (getNoneFloatArgIndex(parameters, index) >= NUM_NONE_FLOAT_ARGUMENT_REGISTERS) {
					stackArgIndex++;
				}
			}

			index++;
		}

		return stackArgIndex;
	}

	//Moves a relative none float argument to the stack. The argument is relative to the type of the register.
	void moveNoneFloatArgToStack(FunctionCompilationData& functionData, int argIndex, int relativeArgIndex, int numStackArgs) {
		auto& function = functionData.function;

		char argStackOffset = -(char)((1 + argIndex) * Amd64Backend::REG_SIZE);

		if (relativeArgIndex >= 6) {
			int stackArgIndex = getStackArgumentIndex(functionData, argIndex);
			Amd64Backend::moveMemoryRegWithOffsetToReg(
				function.generatedCode,
				Registers::AX,
				Registers::BP,
				(char)(Amd64Backend::REG_SIZE * (numStackArgs - stackArgIndex + 1))); //mov rax, [rbp+REG_SIZE*<arg offset>]

			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, Registers::AX); //mov [rbp+<arg offset>], rax
		}

        if (relativeArgIndex == 5) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, NumberedRegisters::R9); //mov [rbp+<arg offset>], r9
        }

        if (relativeArgIndex == 4) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, NumberedRegisters::R8); //mov [rbp+<arg offset>], r8
        }

        if (relativeArgIndex == 3) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, Registers::CX); //mov [rbp+<arg offset>], rcx
        }

        if (relativeArgIndex == 2) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, Registers::DX); //mov [rbp+<arg offset>], rdx
        }

        if (relativeArgIndex == 1) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, Registers::SI); //mov [rbp+<arg offset>], rsi
        }

        if (relativeArgIndex == 0) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, Registers::DI); //mov [rbp+<arg offset>], rdi
        }
	}

	//Moves a relative float argument to the stack. The argument is relative to the type of the register.
	void moveFloatArgToStack(FunctionCompilationData& functionData, int argIndex, int relativeArgIndex) {
		auto& function = functionData.function;

		//The code that are used for none float arguments should work, but doesn't :(.
		if (relativeArgIndex > 7) {
			throw std::runtime_error("Internal limitation: Only 8 float arguments are supported.");
		}

		char argStackOffset = -(char)((1 + argIndex) * Amd64Backend::REG_SIZE);

		if (relativeArgIndex == 7) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM7); //movss [rbp+<arg offset>], xmm7
		}

		if (relativeArgIndex == 6) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM6); //movss [rbp+<arg offset>], xmm6
		}

		if (relativeArgIndex == 5) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM5); //movss [rbp+<arg offset>], xmm5
		}

		if (relativeArgIndex == 4) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM4); //movss [rbp+<arg offset>], xmm4
		}

		if (relativeArgIndex == 3) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM3); //movss [rbp+<arg offset>], xmm3
		}

		if (relativeArgIndex == 2) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM2); //movss [rbp+<arg offset>], xmm2
		}

		if (relativeArgIndex == 1) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM1); //movss [rbp+<arg offset>], xmm1
		}

		if (relativeArgIndex == 0) {
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode,
				Registers::BP, argStackOffset, FloatRegisters::XMM0); //movss [rbp+<arg offset>], xmm0
		}
	}
}

void LinuxCallingConvention::moveArgsToStack(FunctionCompilationData& functionData) const {
    auto& function = functionData.function;
	auto& parameters = function.parameters();

	int numStackArgs = numStackArguments(functionData);
	for (int arg = (int)function.numParams() - 1; arg >= 0; arg--) {
		if (TypeSystem::isPrimitiveType(function.parameters()[arg], PrimitiveTypes::Float)) {
			moveFloatArgToStack(functionData, arg, getFloatArgIndex(parameters, arg));
		} else {
			moveNoneFloatArgToStack(functionData, arg, getNoneFloatArgIndex(parameters, arg), numStackArgs);
		}
	}
}

void LinuxCallingConvention::callFunctionArgument(FunctionCompilationData& functionData,
												  int argIndex, const Type* argType, const FunctionDefinition& funcToCall) const {
    auto& generatedCode = functionData.function.generatedCode;

	if (TypeSystem::isPrimitiveType(argType, PrimitiveTypes::Float)) {
		//Arguments of index >= 8 are already on the stack.
		int relativeIndex = getFloatArgIndex(funcToCall.arguments(), argIndex);

		if (relativeIndex == 7) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM7);
		}

		if (relativeIndex == 6) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM6);
		}

		if (relativeIndex == 5) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM5);
		}

		if (relativeIndex == 4) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM4);
		}

		if (relativeIndex == 3) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM3);
		}

		if (relativeIndex == 2) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM2);
		}

		if (relativeIndex == 1) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1);
		}

		if (relativeIndex == 0) {
			Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0);
		}
	} else {
		//Arguments of index >= 6 are already on the stack.
		int relativeIndex = getNoneFloatArgIndex(funcToCall.arguments(), argIndex);

		if (relativeIndex == 5) {
			Amd64Backend::popReg(generatedCode, NumberedRegisters::R9); //pop r9
		}

		if (relativeIndex == 4) {
			Amd64Backend::popReg(generatedCode, NumberedRegisters::R8); //pop r8
		}

		if (relativeIndex == 3) {
			Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
		}

		if (relativeIndex == 2) {
			Amd64Backend::popReg(generatedCode, Registers::DX); //pop rdx
		}

		if (relativeIndex == 1) {
			Amd64Backend::popReg(generatedCode, Registers::SI); //pop rsi
		}

		if (relativeIndex == 0) {
			Amd64Backend::popReg(generatedCode, Registers::DI); //pop rdi
		}
	}
}

void LinuxCallingConvention::callFunctionArguments(FunctionCompilationData& functionData,
												   const FunctionDefinition& funcToCall, GetArgumentType getArgumentType) const {
    int numArgs = (int)funcToCall.arguments().size();

	//Set the function arguments
    for (int arg = numArgs - 1; arg >= 0; arg--) {
		callFunctionArgument(functionData, arg, getArgumentType(arg), funcToCall);
	}
}

void LinuxCallingConvention::returnValue(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall) const {
    auto& generatedCode = functionData.function.generatedCode;

    if (funcToCall.returnType()->name() != "Void") {
        if (funcToCall.returnType()->name() == "Float") {
            Amd64Backend::pushReg(generatedCode, FloatRegisters::XMM0); //push xmm0
        } else {
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
    }
}