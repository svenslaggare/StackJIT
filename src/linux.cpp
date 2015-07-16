#include "linux.h"
#include "amd64.h"
#include "jit.h"
#include "function.h"
#include "type.h"

#include <iostream>
#include <sys/mman.h>
#include <assert.h>

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
    assert(success == 0);
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

    assert(mem != MAP_FAILED);
    auto newPage = new CodePage(mem, size);
    mPages.push_back(newPage);
    return newPage;
}

void* LinuxMemoryManager::allocateMemory(std::size_t size) {
    CodePage* page = nullptr;

    //Find a page wite enough size
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

void LinuxCallingConvention::moveArgsToStack(FunctionCompilationData& functionData) const {
    auto& function = functionData.function;

    if (function.numParams() > 0) {
        if (function.numParams() >= 6) {
            if (TypeSystem::isPrimitiveType(function.parameters()[5], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(
                    function.generatedCode,
					Registers::BP, -6 * Amd64Backend::REG_SIZE, FloatRegisters::XMM5); //movss [rbp-6*REG_SIZE], xmm5
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode, Registers::BP,
					-6 * Amd64Backend::REG_SIZE, NumberedRegisters::R9); //mov [rbp-6*REG_SIZE], r9
            }
        }

        if (function.numParams() >= 5) {
            if (TypeSystem::isPrimitiveType(function.parameters()[4], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode, Registers::BP,
					-5 * Amd64Backend::REG_SIZE, FloatRegisters::XMM4); //movss [rbp-5*REG_SIZE], xmm4
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode, Registers::BP,
					-5 * Amd64Backend::REG_SIZE, NumberedRegisters::R8); //mov [rbp-5*REG_SIZE], r8
            }
        }

        if (function.numParams() >= 4) {
            if (TypeSystem::isPrimitiveType(function.parameters()[3], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -4 * Amd64Backend::REG_SIZE, FloatRegisters::XMM3); //movss [rbp-4*REG_SIZE], xmm3
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -4 * Amd64Backend::REG_SIZE, Registers::CX); //mov [rbp-4*REG_SIZE], rcx
            }
        }

        if (function.numParams() >= 3) {
            if (TypeSystem::isPrimitiveType(function.parameters()[2], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -3 * Amd64Backend::REG_SIZE, FloatRegisters::XMM2); //movss [rbp-3*REG_SIZE], xmm2
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -3 * Amd64Backend::REG_SIZE, Registers::DX); //mov [rbp-3*REG_SIZE], rdx
            }
        }

        if (function.numParams() >= 2) {
            if (TypeSystem::isPrimitiveType(function.parameters()[1], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -2 * Amd64Backend::REG_SIZE, FloatRegisters::XMM1); //movss [rbp-2*REG_SIZE], xmm1
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -2 * Amd64Backend::REG_SIZE , Registers::SI); //mov [rbp-2*REG_SIZE], rsi
            }
        }

        if (function.numParams() >= 1) {
            if (TypeSystem::isPrimitiveType(function.parameters()[0], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -Amd64Backend::REG_SIZE, FloatRegisters::XMM0); //movss [rbp-REG_SIZE], xmm0
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(
					function.generatedCode,
					Registers::BP, -Amd64Backend::REG_SIZE, Registers::DI); //mov [rbp-REG_SIZE], rdi
            }
        }
    }
}

void LinuxCallingConvention::callFunctionArgument(FunctionCompilationData& functionData, int argIndex, const Type* argType) const {
    auto& generatedCode = functionData.function.generatedCode;

    if (argIndex == 5) {
        if (argType->name() == "Float") {    
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM5);             
        } else {
            Amd64Backend::popReg(generatedCode, NumberedRegisters::R9); //pop r9
        }
    }

    if (argIndex == 4) {
        if (argType->name() == "Float") {    
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM4);             
        } else {
            Amd64Backend::popReg(generatedCode, NumberedRegisters::R8); //pop r8
        }
    }

    if (argIndex == 3) {
        if (argType->name() == "Float") {    
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM3);             
        } else {
            Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
        }
    }

    if (argIndex == 2) {
        if (argType->name() == "Float") {   
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM2);            
        } else {
            Amd64Backend::popReg(generatedCode, Registers::DX); //pop rdx
        }
    }

    if (argIndex == 1) {
        if (argType->name() == "Float") { 
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1);                 
        } else {
            Amd64Backend::popReg(generatedCode, Registers::SI); //pop rsi
        }
    }

    if (argIndex == 0) {
        if (argType->name() == "Float") {
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0);
        } else {
            Amd64Backend::popReg(generatedCode, Registers::DI); //pop rdi
        }
    }
}

void LinuxCallingConvention::callFunctionArguments(FunctionCompilationData& functionData, const FunctionDefinition& funcToCall, GetArugmentType getArgumentType) const {
    int numArgs = funcToCall.arguments().size();

    //Set the function arguments
    if (numArgs >= 6) {
        callFunctionArgument(functionData, 5, getArgumentType(5));
    }

    if (numArgs >= 5) {
        callFunctionArgument(functionData, 4, getArgumentType(4));
    }

    if (numArgs >= 4) {
        callFunctionArgument(functionData, 3, getArgumentType(3));
    }

    if (numArgs >= 3) {
        callFunctionArgument(functionData, 2, getArgumentType(2));
    }

    if (numArgs >= 2) {
        callFunctionArgument(functionData, 1, getArgumentType(1));
    }

    if (numArgs >= 1) {
        callFunctionArgument(functionData, 0, getArgumentType(0));
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