#include <sys/mman.h>
#include <string.h>
#include <iostream>

#include "codegenerator.h"
#include "stackjit.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"

union IntToBytes {
    int IntValue;
    unsigned char ByteValues[4];
};

union LongToBytes {
    long LongValue;
    unsigned char ByteValues[8];
};

void pushArray(std::vector<unsigned char>& insts, const std::vector<unsigned char>& values) {
    for (auto current : values) {
        insts.push_back(current);
    }
}

JitFunction generateProgram(Program& program, VMState& vmState) {
    std::map<FunctionCall, std::string> callTable;

    //Generate code for all functions
    for (auto func : program.Functions) {
        Function newFunc;
        newFunc.Name = func.first;
        newFunc.Instructions = *func.second;

        auto funcPtr = generateFunction(newFunc, vmState);

        if (ENABLE_DEBUG) {
            std::cout << "Defined function '" << func.first << "' at " << (long)funcPtr << std::endl;
        }

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
        long calledFuncAddr = vmState.FunctionTable[calledFunc];

        unsigned char* funcCode = (unsigned char*)vmState.FunctionTable[funcName];

        LongToBytes converter;
        converter.LongValue = calledFuncAddr;

        int base = offset + 2;
        for (int i = 0; i < 8; i++) {
            funcCode[base + i] = converter.ByteValues[i];
        }
    }

    //Return the main func as entry point
    return (JitFunction)vmState.FunctionTable["main"];
}

JitFunction generateFunction(Function& function, VMState& vmState) {
    for (auto current : function.Instructions) {
        generateCode(function, vmState, current);
    }

    auto generatedCode = function.GeneratedCode;

    //The return instruction
    generatedCode.push_back(0x58); //pop eax
    generatedCode.push_back(0xc3); //ret

    unsigned char* code = generatedCode.data();
    int length = generatedCode.size();

    //Allocate writable/executable memory
    void *mem = mmap(nullptr, length, PROT_WRITE | PROT_EXEC,
        MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, code, length);

    //Return the generated code as a function pointer
    return (int (*)())mem;
}

void generateCode(Function& function, VMState& vmState, const Instruction& inst) {
    std::vector<unsigned char>& generatedCode = function.GeneratedCode;

    switch (inst.OpCode) {
    case OpCodes::PUSH_INT:
        //An operand, push the value
        generatedCode.push_back(0x68); //push <value>

        //Convert the int to four bytes
        IntToBytes converter;
        converter.IntValue = inst.Value;
        generatedCode.push_back(converter.ByteValues[0]);
        generatedCode.push_back(converter.ByteValues[1]);
        generatedCode.push_back(converter.ByteValues[2]);
        generatedCode.push_back(converter.ByteValues[3]);
        break;
    case OpCodes::ADD:
    case OpCodes::SUB:
    case OpCodes::MUL:
    case OpCodes::DIV:
        //Pop 2 operands
        generatedCode.push_back(0x59); //pop ecx
        generatedCode.push_back(0x58); //pop eax

        //Apply the operator
        switch (inst.OpCode) {
            case OpCodes::ADD:
                generatedCode.push_back(0x01); //add eax, ecx
                generatedCode.push_back(0xc8);
                break;
            case OpCodes::SUB:
                generatedCode.push_back(0x29); //sub eax, ecx
                generatedCode.push_back(0xc8);
                break;
            case OpCodes::MUL:
                generatedCode.push_back(0x0f); //imul eax, ecx
                generatedCode.push_back(0xaf);
                generatedCode.push_back(0xc1);
                break;
            case OpCodes::DIV:
                //This gives a runtime error, but I don't know why.
                generatedCode.push_back(0xf7); //idiv ecx
                generatedCode.push_back(0xf9);
                break;
            default:
                break;
        }

        //Push the result
        generatedCode.push_back(0x50); //push eax
        break;
    case OpCodes::LOAD_LOCAL:
        {
            //Load eax with the given local
            long localsAddr = (long)(&vmState.Locals[0 + inst.Value]);

            LongToBytes converter;
            converter.LongValue = localsAddr;

            generatedCode.push_back(0xa1); //mov rax, [<mem addr>]
            generatedCode.push_back(converter.ByteValues[0]);
            generatedCode.push_back(converter.ByteValues[1]);
            generatedCode.push_back(converter.ByteValues[2]);
            generatedCode.push_back(converter.ByteValues[3]);
            generatedCode.push_back(converter.ByteValues[4]);
            generatedCode.push_back(converter.ByteValues[5]);
            generatedCode.push_back(converter.ByteValues[6]);
            generatedCode.push_back(converter.ByteValues[7]);

            //Push the loaded value
            generatedCode.push_back(0x50); //push eax
        }
        break;
    case OpCodes::STORE_LOCAL:
        {
            //Pop the top operand
            generatedCode.push_back(0x58); //pop eax

            //Store eax at the given local
            long localsAddr = (long)(&vmState.Locals[0 + inst.Value]);

            LongToBytes converter;
            converter.LongValue = localsAddr;

            generatedCode.push_back(0xa3); //mov [<mem addr>], rax
            generatedCode.push_back(converter.ByteValues[0]);
            generatedCode.push_back(converter.ByteValues[1]);
            generatedCode.push_back(converter.ByteValues[2]);
            generatedCode.push_back(converter.ByteValues[3]);
            generatedCode.push_back(converter.ByteValues[4]);
            generatedCode.push_back(converter.ByteValues[5]);
            generatedCode.push_back(converter.ByteValues[6]);
            generatedCode.push_back(converter.ByteValues[7]);
        }
        break;
    case OpCodes::CALL:
        {
            //Get the address of the function to call
            long funcAddr = vmState.FunctionTable[inst.StrValue];
            int numArgs = inst.Value;

            if (ENABLE_DEBUG) {
                std::cout << "Calling '" << inst.StrValue + "' at " << funcAddr << std::endl;
            }

            //Check if the function is defined yet
            if (funcAddr == 0) {
                //Mark that the function call needed to be patched with the address later
                function.CallTable[make_pair(function.Name, generatedCode.size())] = inst.StrValue;
            }

            LongToBytes converter;
            converter.LongValue = funcAddr;

            generatedCode.push_back(0x48); //mov rax, <addr>
            generatedCode.push_back(0xb8);

            generatedCode.push_back(converter.ByteValues[0]);
            generatedCode.push_back(converter.ByteValues[1]);
            generatedCode.push_back(converter.ByteValues[2]);
            generatedCode.push_back(converter.ByteValues[3]);
            generatedCode.push_back(converter.ByteValues[4]);
            generatedCode.push_back(converter.ByteValues[5]);
            generatedCode.push_back(converter.ByteValues[6]);
            generatedCode.push_back(converter.ByteValues[7]);

            //Set the function arguments
            if (numArgs >= 4) {
                generatedCode.push_back(0x59); //pop rcx
            }

            if (numArgs >= 3) {
                generatedCode.push_back(0x5a); //pop rdx
            }

            if (numArgs >= 2) {
                generatedCode.push_back(0x5e); //pop rsi
            }

            if (numArgs >= 1) {
                generatedCode.push_back(0x5f); //pop rdi
            }

            //Make the call
            generatedCode.push_back(0xff); //call rax
            generatedCode.push_back(0xd0);

            //Push the result
            generatedCode.push_back(0x50); //push rax
        }
        break;
    default:
        break;
    }
}