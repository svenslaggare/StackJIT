#include "linux.h"
#include "amd64.h"
#include "jit.h"
#include "function.h"
#include "type.h"

#include <sys/mman.h>
#include <assert.h>

void* LinuxMemoryManager::allocateMemory(std::size_t size) {
	void *mem = mmap(
        nullptr,
        size,
        PROT_WRITE | PROT_READ,
        MAP_ANON | MAP_PRIVATE,
        -1,
        0);

    assert(mem != MAP_FAILED);
    return mem;
}

void LinuxMemoryManager::freeMemory(void* memory, std::size_t size) {
    munmap(memory, size);
}

void LinuxMemoryManager::makeExecutableMemory(void* memory, std::size_t size) {
	int success = mprotect(memory, size, PROT_EXEC | PROT_READ);
	assert(success == 0);
}

void LinuxCallingConvention::moveArgsToStack(FunctionCompilationData& functionData) const {
    auto& function = functionData.function;

    if (function.numArgs() > 0) {
        if (function.numArgs() >= 6) {
            if (TypeSystem::isPrimitiveType(function.arguments()[5], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -6 * Amd64Backend::REG_SIZE, FloatRegisters::XMM5); //movss [rbp-6*REG_SIZE], xmm5
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -6 * Amd64Backend::REG_SIZE, NumberedRegisters::R9); //mov [rbp-6*REG_SIZE], r9
            }
        }

        if (function.numArgs() >= 5) {
            if (TypeSystem::isPrimitiveType(function.arguments()[4], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -5 * Amd64Backend::REG_SIZE, FloatRegisters::XMM4); //movss [rbp-5*REG_SIZE], xmm4
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -5 * Amd64Backend::REG_SIZE, NumberedRegisters::R8); //mov [rbp-5*REG_SIZE], r8
            }
        }

        if (function.numArgs() >= 4) {
            if (TypeSystem::isPrimitiveType(function.arguments()[3], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -4 * Amd64Backend::REG_SIZE, FloatRegisters::XMM3); //movss [rbp-4*REG_SIZE], xmm3
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -4 * Amd64Backend::REG_SIZE, Registers::CX); //mov [rbp-4*REG_SIZE], rcx
            }
        }

        if (function.numArgs() >= 3) {
            if (TypeSystem::isPrimitiveType(function.arguments()[2], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -3 * Amd64Backend::REG_SIZE, FloatRegisters::XMM2); //movss [rbp-3*REG_SIZE], xmm2
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -3 * Amd64Backend::REG_SIZE, Registers::DX); //mov [rbp-3*REG_SIZE], rdx
            }
        }

        if (function.numArgs() >= 2) {
            if (TypeSystem::isPrimitiveType(function.arguments()[1], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -2 * Amd64Backend::REG_SIZE, FloatRegisters::XMM1); //movss [rbp-2*REG_SIZE], xmm1
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -2 * Amd64Backend::REG_SIZE , Registers::SI); //mov [rbp-2*REG_SIZE], rsi
            }
        }

        if (function.numArgs() >= 1) {
            if (TypeSystem::isPrimitiveType(function.arguments()[0], PrimitiveTypes::Float)) {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -Amd64Backend::REG_SIZE, FloatRegisters::XMM0); //movss [rbp-REG_SIZE], xmm0
            } else {
                Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -Amd64Backend::REG_SIZE, Registers::DI); //mov [rbp-REG_SIZE], rdi
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
    auto& generatedCode = functionData.function.generatedCode;

    //Set the function arguments
    if (numArgs >= 6) {
        auto argType = getArgumentType(5);
        if (argType->name() == "Float") {    
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM5);             
        } else {
            Amd64Backend::popReg(generatedCode, NumberedRegisters::R9); //pop r9
        }
    }

    if (numArgs >= 5) {
        auto argType = getArgumentType(4);
        if (argType->name() == "Float") {    
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM4);             
        } else {
            Amd64Backend::popReg(generatedCode, NumberedRegisters::R8); //pop r8
        }
    }

    if (numArgs >= 4) {
        auto argType = getArgumentType(3);
        if (argType->name() == "Float") {    
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM3);             
        } else {
            Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
        }
    }

    if (numArgs >= 3) {
        auto argType = getArgumentType(2);
        if (argType->name() == "Float") {   
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM2);            
        } else {
            Amd64Backend::popReg(generatedCode, Registers::DX); //pop rdx
        }
    }

    if (numArgs >= 2) {
        auto argType = getArgumentType(1);
        if (argType->name() == "Float") { 
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1);                 
        } else {
            Amd64Backend::popReg(generatedCode, Registers::SI); //pop rsi
        }
    }

    if (numArgs >= 1) {
        auto argType = getArgumentType(0);
        if (argType->name() == "Float") {
            Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0);
        } else {
            Amd64Backend::popReg(generatedCode, Registers::DI); //pop rdi
        }
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