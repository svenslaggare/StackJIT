#include <sys/mman.h>
#include <string.h>
#include <iostream>

#include "codegenerator.h"
#include "stackjit.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "amd64.h"

union IntToBytes {
    int IntValue;
    unsigned char ByteValues[sizeof(int)];
};

union LongToBytes {
    long LongValue;
    unsigned char ByteValues[sizeof(long)];
};

void pushArray(std::vector<unsigned char>& dest, const std::vector<unsigned char>& values) {
    for (auto current : values) {
        dest.push_back(current);
    }
}

JitFunction CodeGenerator::generateProgram(Program& program, VMState& vmState) {
    std::map<FunctionCall, std::string> callTable;

    //Generate code for all functions
    for (auto func : program.Functions) {
        Function newFunc;
        newFunc.Name = func.first;
        newFunc.NumArgs = func.second.NumArgs;
        newFunc.Instructions = *func.second.Instructions;

        auto funcPtr = generateFunction(newFunc, vmState);

        if (ENABLE_DEBUG) {
            std::cout << "Defined function '" << func.first << "' at 0x" << std::hex << (long)funcPtr << std::dec << "." << std::endl;
        }

        //Add the unresolved call to the program call table
        for (auto call : newFunc.CallTable) {
            callTable[call.first] = call.second;
        }

        vmState.FunctionTable[func.first] = (long)funcPtr;
    }

    //Fix unresolved calls
    for (auto call : callTable) {
        auto funcName = call.first.first;
        auto offset = call.first.second;
        auto calledFunc = call.second;

        //Check if defined
        if (vmState.FunctionTable.count(calledFunc) > 0) {
            //Get a pointer to the functions instructions
            long calledFuncAddr = vmState.FunctionTable[calledFunc];
            unsigned char* funcCode = (unsigned char*)vmState.FunctionTable[funcName];

            //Update the call target
            LongToBytes converter;
            converter.LongValue = calledFuncAddr;

            int base = offset + 2;
            for (int i = 0; i < 8; i++) {
                funcCode[base + i] = converter.ByteValues[i];
            }
        } else {
            throw std::string("Function '" + calledFunc + "' not found.");
        }
    }

    //Return the main func as entry point
    return (JitFunction)vmState.FunctionTable["main"];
}

JitFunction CodeGenerator::generateFunction(Function& function, const VMState& vmState) {
    //Save the base pointer
    Amd64Backend::pushReg(function.GeneratedCode, Registers::BP); //push rbp
    Amd64Backend::moveRegToReg(function.GeneratedCode, Registers::BP, Registers::SP); //mov rbp, rsp

    //Move function arguments from registers to stack
    if (function.NumArgs > 0) {
        //Make room for the arguments on the stack
        unsigned char argsSize = (unsigned char)(function.NumArgs * 4);
        Amd64Backend::subByteFromReg(function.GeneratedCode, Registers::SP, argsSize); //sub rsp, <size of args>

        //Move the arguments from the registers to the stack
        if (function.NumArgs >= 4) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.GeneratedCode, Registers::BP, -16, Registers::CX); //mov [rbp-16], rcx
        }

        if (function.NumArgs >= 3) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.GeneratedCode, Registers::BP, -12, Registers::DX); //mov [rbp-12], rdx
        }

        if (function.NumArgs >= 2) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.GeneratedCode, Registers::BP, -8, Registers::SI); //mov [rbp-8], rsi
        }

        if (function.NumArgs >= 1) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.GeneratedCode, Registers::BP, -4, Registers::DI); //mov [rbp-4], rdi
        }
    }

    //Generate the code for the program
    for (auto current : function.Instructions) {
        generateInstruction(function, vmState, current);
    }

    //Pop the return value
    Amd64Backend::popReg(function.GeneratedCode, Registers::AX); //pop eax

    //Free the arguments
    if (function.NumArgs > 0) {
        unsigned char argsSize = (unsigned char)(function.NumArgs * 4);
        Amd64Backend::addByteToReg(function.GeneratedCode, Registers::SP, argsSize); //add rsp, <byte>
    }

    // pushArray(function.GeneratedCode, { 0x48, 0x89, 0xEC }); //mov rsp, rbp

    //Restore the base pointer
    Amd64Backend::popReg(function.GeneratedCode, Registers::BP); //pop rbp

    //Make the return
    Amd64Backend::ret(function.GeneratedCode); //ret

    unsigned char* code = function.GeneratedCode.data();
    int length = function.GeneratedCode.size();

    if (ENABLE_DEBUG) {
        std::cout << "Generated function '" << function.Name << "' of size: " << length << " bytes." << std::endl;
    }

    //Allocate writable and executable memory
    void *mem = mmap(
        nullptr,
        length,
        PROT_WRITE | PROT_EXEC,
        MAP_ANON | MAP_PRIVATE,
        -1,
        0);

    //Copy the instructions
    memcpy(mem, code, length);

    //Return the generated code as a function pointer
    return (JitFunction)mem;
}

void CodeGenerator::generateInstruction(Function& function, const VMState& vmState, const Instruction& inst) {
   auto& generatedCode = function.GeneratedCode;

    switch (inst.OpCode) {
    case OpCodes::PUSH_INT:
        //An operand, push the value
        Amd64Backend::pushInt(generatedCode, inst.Value); //push <value>
        break;
    case OpCodes::ADD:
    case OpCodes::SUB:
    case OpCodes::MUL:
    case OpCodes::DIV:
        //Pop 2 operands
        Amd64Backend::popReg(generatedCode, Registers::BX); //pop ebx
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop eax

        //Apply the operator
        switch (inst.OpCode) {
            case OpCodes::ADD:
                Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::BX, true); //add eax, ebx
                break;
            case OpCodes::SUB:
                Amd64Backend::subRegFromReg(generatedCode, Registers::AX, Registers::BX, true); //sub eax, ebx
                break;
            case OpCodes::MUL:
                Amd64Backend::multRegToReg(generatedCode, Registers::AX, Registers::BX, true); //imul eax, ebx
                break;
            case OpCodes::DIV:
                Amd64Backend::divRegFromReg(generatedCode, Registers::AX, Registers::BX, true); //idiv eax, ebx
                break;
            default:
                break;
        }

        //Push the result
        Amd64Backend::pushReg(generatedCode, Registers::AX); //push eax
        break;
    case OpCodes::LOAD_LOCAL:
        {
            //Load rax with the given local
            long localsAddr = (long)(&vmState.Locals[0 + inst.Value]);
            Amd64Backend::moveMemoryToReg(generatedCode, Registers::AX, localsAddr); //mov rax, [<mem addr>]

            //Push the loaded value
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
        break;
    case OpCodes::STORE_LOCAL:
        {
            //Pop the top operand
            Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

            //Store eax at the given local
            long localsAddr = (long)(&vmState.Locals[0 + inst.Value]);
            Amd64Backend::moveRegToMemory(generatedCode, localsAddr, Registers::AX); //mov [<mem addr>], rax
        }
        break;
    case OpCodes::CALL:
        {
            //Get the address of the function to call
            long funcAddr = 0;

            //Check if the function is defined yet
            if (vmState.FunctionTable.count(inst.StrValue) > 0) {
                funcAddr = vmState.FunctionTable.at(inst.StrValue);
            } else {
                //Mark that the function call needs to be patched with the address later
                function.CallTable[make_pair(function.Name, generatedCode.size())] = inst.StrValue;
            }

            int numArgs = inst.Value;

            if (ENABLE_DEBUG) {
                std::cout << "Calling '" << inst.StrValue + "' at " << std::hex << funcAddr << std::dec << "." << std::endl;
            }

            //Move the address of the call to rax
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, funcAddr); //mov rax, <addr>

            //Set the function arguments
            if (numArgs >= 4) {
                Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
            }

            if (numArgs >= 3) {
                Amd64Backend::popReg(generatedCode, Registers::DX); //pop rdx
            }

            if (numArgs >= 2) {
                Amd64Backend::popReg(generatedCode, Registers::SI); //pop rsi
            }

            if (numArgs >= 1) {
                Amd64Backend::popReg(generatedCode, Registers::DI); //pop rdi
            }

            //Make the call
            Amd64Backend::callInReg(generatedCode, Registers::AX); //call rax

            //Push the result
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
        break;
    case OpCodes::LOAD_ARG:
        {
            //Load rax with the arg offset
            IntToBytes converter;
            converter.IntValue = (inst.Value + 1) * -4;

            //mov rax, <int>
            Amd64Backend::moveIntToReg(generatedCode, Registers::AX, (inst.Value + 1) * -4);

            //Now add the base pointer
            Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::BP); //add rax, rbp

            //Load rax with the argument from the stack
            Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX); //mov rax, [rax]

            //Push the loaded value
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
        break;
    default:
        break;
    }
}
