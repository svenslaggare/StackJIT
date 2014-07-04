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
            std::cout << "Defined function '" << func.first << "' at " << (long)funcPtr << std::endl;
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
            long calledFuncAddr = vmState.FunctionTable[calledFunc];
            unsigned char* funcCode = (unsigned char*)vmState.FunctionTable[funcName];

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
    function.GeneratedCode.push_back(0x55); //push rbp
    pushArray(function.GeneratedCode, { 0x48, 0x89, 0xE5 }); //mov rbp, rsp

    //Move function arguments from registers to stack
    if (function.NumArgs > 0) {
        //Make room for the arguments on the stack
        unsigned char argsSize = (unsigned char)(function.NumArgs * 4);
        pushArray(function.GeneratedCode, { 0x48, 0x83, 0xec, argsSize }); //sub rsp, <size of args>

        //Move the arguments from the registers to the stack
        if (function.NumArgs >= 4) {
            pushArray(function.GeneratedCode, { 0x48, 0x89, 0x4D, 0xF0 }); //mov [rbp-16], rcx
        }

        if (function.NumArgs >= 3) {
            pushArray(function.GeneratedCode, { 0x48, 0x89, 0x55, 0xF4 }); //mov [rbp-12], rdx
        }

        if (function.NumArgs >= 2) {
            pushArray(function.GeneratedCode, { 0x48, 0x89, 0x75, 0xF8 }); //mov [rbp-8], rsi
        }

        if (function.NumArgs >= 1) {
            pushArray(function.GeneratedCode, { 0x48, 0x89, 0x7D, 0xFC }); //mov [rbp-4], rdi
        }
    }

    //Generate the code for the program
    for (auto current : function.Instructions) {
        generateCode(function, vmState, current);
    }

    //Pop the return value
    function.GeneratedCode.push_back(0x58); //pop eax

    //Free the arguments
    if (function.NumArgs > 0) {
        unsigned char argsSize = (unsigned char)(function.NumArgs * 4);
        pushArray(function.GeneratedCode, { 0x48, 0x83, 0xc4, argsSize }); //add rsp, <byte> 
    }

    // pushArray(function.GeneratedCode, { 0x48, 0x89, 0xEC }); //mov rsp, rbp
    //Restore the base pointer
    function.GeneratedCode.push_back(0x5d); //pop rbp

    //Make the return
    function.GeneratedCode.push_back(0xc3); //ret

    unsigned char* code = function.GeneratedCode.data();
    int length = function.GeneratedCode.size();
    std::cout << "Func '" << function.Name <<"' size: " << length << std::endl;

    //Allocate writable/executable memory
    void *mem = mmap(nullptr, length, PROT_WRITE | PROT_EXEC,
        MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, code, length);

    //Return the generated code as a function pointer
    return (JitFunction)mem;
}

void CodeGenerator::generateCode(Function& function, const VMState& vmState, const Instruction& inst) {
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
        generatedCode.push_back(0x5b); //pop ebx
        generatedCode.push_back(0x58); //pop eax

        //Apply the operator
        switch (inst.OpCode) {
            case OpCodes::ADD:
                generatedCode.push_back(0x01); //add eax, ebx
                generatedCode.push_back(0xd8);
                break;
            case OpCodes::SUB:
                generatedCode.push_back(0x29); //sub eax, ebx
                generatedCode.push_back(0xd8);
                break;
            case OpCodes::MUL:
                generatedCode.push_back(0x0f); //imul eax, ebx
                generatedCode.push_back(0xaf);
                generatedCode.push_back(0xc3);
                break;
            case OpCodes::DIV:
                //This gives a runtime error, but I don't know why.
                generatedCode.push_back(0xf7); //idiv ebx
                generatedCode.push_back(0xfb);
                break;
            default:
                break;
        }

        //Push the result
        generatedCode.push_back(0x50); //push eax
        break;
    case OpCodes::LOAD_LOCAL:
        {
            //Load rax with the given local
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
            generatedCode.push_back(0x50); //push rax
        }
        break;
    case OpCodes::STORE_LOCAL:
        {
            //Pop the top operand
            generatedCode.push_back(0x58); //pop rax

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
                std::cout << "Calling '" << inst.StrValue + "' at " << funcAddr << std::endl;
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
    case OpCodes::LOAD_ARG:
        {
            //Load rax with the arg offset
            IntToBytes converter;
            converter.IntValue = (inst.Value + 1) * -4;

            generatedCode.push_back(0x48); //mov rax, <int>
            generatedCode.push_back(0xc7); 
            generatedCode.push_back(0xc0); 
            generatedCode.push_back(converter.ByteValues[0]);
            generatedCode.push_back(converter.ByteValues[1]);
            generatedCode.push_back(converter.ByteValues[2]);
            generatedCode.push_back(converter.ByteValues[3]);

            //Now add the base pointer
            generatedCode.push_back(0x48); //add rax, rbp
            generatedCode.push_back(0x01);
            generatedCode.push_back(0xe8);

            //Load rax with the argument from the stack
            generatedCode.push_back(0x48); //mov rax, [rax]
            generatedCode.push_back(0x8b);
            generatedCode.push_back(0x00);

            //Push the loaded value
            generatedCode.push_back(0x50); //push rax
        }
        break;
    default:
        break;
    }
}