#include <sys/mman.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <assert.h>
#include <limits>

#include "codegenerator.h"
#include "typechecker.h"
#include "type.h"
#include "stackjit.h"
#include "vmstate.h"
#include "rtlibrary.h"
#include "program.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "amd64.h"

void pushArray(std::vector<unsigned char>& dest, const std::vector<unsigned char>& values) {
    for (auto current : values) {
        dest.push_back(current);
    }
}

//Generates array bounds checks
void generateArrayBoundsCheck(CodeGen& codeGen) {
    //Get the size of the array (an int)
    Amd64Backend::moveMemoryByRegToReg(codeGen, Registers::SI, Registers::AX, true); //mov esi, [rax]

    //Compare the index and size
    Amd64Backend::compareRegToReg(codeGen, Registers::CX, Registers::SI); //cmp rcx, rsi
    pushArray(codeGen, { 0x72, 10 + 2 }); //jb <after call>. By using an unsigned comparison, we only need one check.

    //If out of bounds, call the error func
    Amd64Backend::moveLongToReg(codeGen, Registers::DI, (long)&rt_arrayOutOfBoundsError); //mov rdi, <addr of func>
    Amd64Backend::callInReg(codeGen, Registers::DI); //call rdi
}

JitFunction CodeGenerator::generateProgram(Program& program, VMState& vmState) {
    std::map<FunctionCall, std::string> callTable;

    //Add the functions to the func table
    for (auto currentFunc : program.Functions) {
        auto func = currentFunc.second;
        vmState.FunctionTable[func->name] = FunctionDefinition(func->arguments, func->returnType, 0, 0);
    }

    //Generate instructions for all functions
    for (auto currentFunc : program.Functions) {
        auto func = currentFunc.second;
        FunctionCompilationData funcData { *func };

        auto funcPtr = generateFunction(funcData, vmState);

        if (ENABLE_DEBUG) {
            std::cout << "Defined function '" << func->name << "' at 0x" << std::hex << (long)funcPtr << std::dec << "." << std::endl;
        }

        //Add the unresolved call to the program call table
        for (auto call : funcData.CallTable) {
            callTable[call.first] = call.second;
        }

        //Set the entry point & size for the function
        vmState.FunctionTable[func->name].setFunctionBody((long)funcPtr, func->generatedCode.size());
    }

    //Fix unresolved calls
    for (auto call : callTable) {
        auto funcName = call.first.first;
        auto offset = call.first.second;
        auto calledFunc = call.second;

        //Check if defined
        if (vmState.FunctionTable.count(calledFunc) > 0) {
            //Get a pointer to the functions instructions
            long calledFuncAddr = vmState.FunctionTable[calledFunc].entryPoint();
            unsigned char* funcCode = (unsigned char*)(vmState.FunctionTable[funcName].entryPoint());

            //Update the call target
            LongToBytes converter;
            converter.LongValue = calledFuncAddr;

            int base = offset + 2;
            for (int i = 0; i < sizeof(long); i++) {
                funcCode[base + i] = converter.ByteValues[i];
            }
        } else {
            throw std::runtime_error("Function '" + calledFunc + "' not found.");
        }
    }

    //Make the functions memory executable, but not writable.
    for (auto currentFunc : program.Functions) {
        auto func = currentFunc.second;

        void* mem = (void*)vmState.FunctionTable[func->name].entryPoint();
        int length = func->generatedCode.size();

        int success = mprotect(mem, length, PROT_EXEC | PROT_READ);
        assert(success == 0);
    }

    //Return the main func as entry point
    return (JitFunction)vmState.FunctionTable["main"].entryPoint();
}

JitFunction CodeGenerator::generateFunction(FunctionCompilationData& functionData, VMState& vmState) {
    TypeChecker::typeCheckFunction(functionData, vmState, ENABLE_DEBUG && PRINT_TYPE_CHECKING);

    auto& function = functionData.Function;

    //Save the base pointer
    Amd64Backend::pushReg(function.generatedCode, Registers::BP); //push rbp
    Amd64Backend::moveRegToReg(function.generatedCode, Registers::BP, Registers::SP); //mov rbp, rbp

    //Calculate the size of the stack
    int stackSize = (function.numArgs() + function.numLocals) * Amd64Backend::REG_SIZE;

    if (stackSize > 0) {
        //Make room for the variables on the stack
        if (stackSize < 128) {
            Amd64Backend::subByteFromReg(function.generatedCode, Registers::SP, (char)stackSize); //sub rsp, <size of stack>
        } else {
            Amd64Backend::subIntFromReg(function.generatedCode, Registers::SP, stackSize); //sub rsp, <size of stack>
        }
    }

    //Move function arguments from registers to the stack
    if (function.numArgs() > 0) {
        //Move the arguments from the registers to the stack
        if (function.numArgs() >= 4) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -Amd64Backend::REG_SIZE*4, Registers::CX); //mov [rbp-4*REG_SIZE], rcx
        }

        if (function.numArgs() >= 3) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -Amd64Backend::REG_SIZE*3, Registers::DX); //mov [rbp-3*REG_SIZE], rdx
        }

        if (function.numArgs() >= 2) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -Amd64Backend::REG_SIZE*2, Registers::SI); //mov [rbp-2*REG_SIZE], rsi
        }

        if (function.numArgs() >= 1) {
            Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, -Amd64Backend::REG_SIZE, Registers::DI); //mov [rbp-REG_SIZE], rdi
        }
    }

    //Zero the locals
    if (function.numLocals > 0) {
        //This method should be faster? but makes the generated code larger
        // Amd64Backend::moveIntToReg(function.generatedCode, Registers::AX, 0); //mov rax, 0

        // for (int i = 0; i < function.numLocals; i++) {
        //     int localOffset = (i + function.numArgs() + 1) * -Amd64Backend::REG_SIZE;
        //     Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, localOffset, Registers::AX); //mov [rbp-local], rax
        // }

        //Set the dir flag to decrease
        function.generatedCode.push_back(0xFD); //std

        //Set the address where the locals starts
        Amd64Backend::moveRegToReg(function.generatedCode, Registers::DI, Registers::BP); //mov rdi, rbp
        Amd64Backend::addByteToReg(function.generatedCode, Registers::DI, (function.numArgs() + 1) * -Amd64Backend::REG_SIZE); //add rdi, <locals offset>

        //Set the number of locals
        Amd64Backend::moveIntToReg(function.generatedCode, Registers::CX, function.numLocals); //mov rcx, <num locals>

        //Zero eax
        pushArray(function.generatedCode, { 0x31, 0xC0 }); //xor eax, eax

        //Execute the zeroing
        pushArray(function.generatedCode, { 0xF3, 0x48, 0xAB }); //rep stosq

        //Clear the dir flag
        function.generatedCode.push_back(0xFC); //cld
    }

    //Generate the native instructions for the program
    int i = 0;
    for (auto current : function.instructions) {
        generateInstruction(functionData, vmState, current, i);
        i++;
    }

    //Patch branches with the native targets
    for (auto branch : functionData.BranchTable) {
        unsigned int source = branch.first;
        unsigned int target = branch.second.first;
        unsigned int instSize = branch.second.second;

        unsigned int nativeTarget = functionData.InstructionNumMapping[target];

        //Calculate the native jump location
        IntToBytes converter;
        converter.IntValue = nativeTarget - source - instSize;

        unsigned int sourceOffset = instSize - 4;

        //Update the source with the native target
        for (int i = 0; i < 4; i++) {
            function.generatedCode[source + sourceOffset + i] = converter.ByteValues[i];
        }
    }

    //Get a pointer & size of the generated instructions
    unsigned char* code = function.generatedCode.data();
    int length = function.generatedCode.size();

    if (ENABLE_DEBUG) {
        std::string argsStr = "";
        bool isFirst = true;

        for (auto param : function.arguments) {
            if (isFirst) {
                isFirst = false;
            } else {
                argsStr += " ";
            }

            argsStr += TypeChecker::typeToString(param);
        }

        std::cout
            << "Generated function '" << function.name << "(" + argsStr + ") " << TypeChecker::typeToString(function.returnType)
            << "' of size: " << length << " bytes."
            << std::endl;
    }

    //Indicates if to output the generated code to a file
    if (OUTPUT_GENERATED_CODE) {
        std::ofstream asmFile (functionData.Function.name + ".jit", std::ios::binary);

        if (asmFile.is_open()) {
            asmFile.write((char*)code, length);
            asmFile.close();
        }
    }

    //Allocate writable and readable memory
    void *mem = mmap(
        nullptr,
        length,
        PROT_WRITE | PROT_READ,
        MAP_ANON | MAP_PRIVATE,
        -1,
        0);

    assert(mem != MAP_FAILED);

    //Copy the instructions
    memcpy(mem, code, length);

    //Return the generated instuctions as a function pointer
    return (JitFunction)mem;
}

void CodeGenerator::generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex) {
    auto& function = functionData.Function;
    auto& generatedCode = function.generatedCode;
    int stackOffset = 1; //The offset for variables allocated on the stack

    //Make the mapping
    functionData.InstructionNumMapping.push_back(generatedCode.size());

    switch (inst.OpCode) {
    case OpCodes::PUSH_INT:
        //Push the value
        Amd64Backend::pushInt(generatedCode, inst.Value); //push <value>
        break;
    case OpCodes::POP:
        //Pop the value
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop eax
        break;
    case OpCodes::ADD:
    case OpCodes::SUB:
    case OpCodes::MUL:
    case OpCodes::DIV:
        //Pop 2 operands
        Amd64Backend::popReg(generatedCode, Registers::CX); //pop ecx
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop eax

        //Apply the operator
        switch (inst.OpCode) {
            case OpCodes::ADD:
                Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::CX, true); //add eax, ecx
                break;
            case OpCodes::SUB:
                Amd64Backend::subRegFromReg(generatedCode, Registers::AX, Registers::CX, true); //sub eax, ecx
                break;
            case OpCodes::MUL:
                Amd64Backend::multRegToReg(generatedCode, Registers::AX, Registers::CX, true); //imul eax, ecx
                break;
            case OpCodes::DIV:
                Amd64Backend::divRegFromReg(generatedCode, Registers::AX, Registers::CX, true); //idiv eax, ecx
                break;
            default:
                break;
        }

        //Push the result
        Amd64Backend::pushReg(generatedCode, Registers::AX); //push eax
        break;
    case OpCodes::LOAD_LOCAL:
        {
            //Load rax with the locals offset
            Amd64Backend::moveIntToReg(generatedCode, Registers::AX, (inst.Value + function.numArgs() + stackOffset) * -Amd64Backend::REG_SIZE); //mov rax, <int>

            //Now add the base pointer
            Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::BP); //add rax, rbp

            //Load rax with the local from the stack
            Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX); //mov rax, [rax]

            //Push the loaded value
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
        break;
    case OpCodes::STORE_LOCAL:
        {
            //Pop the top operand
            Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

            int localOffset = (inst.Value + function.numArgs() + stackOffset) * -Amd64Backend::REG_SIZE;

            //Store the operand at the given local
            Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::BP, localOffset, Registers::AX); //mov [rbp-local], rax
        }
        break;
    case OpCodes::CALL:
        {
            //Get the address of the function to call
            long funcAddr = 0;

            auto funcToCall = vmState.FunctionTable.at(inst.StrValue);
            int numArgs = funcToCall.Arguments.size();

            //Check if the function entry point is defined yet
            if (funcToCall.entryPoint() != 0) {
                funcAddr = funcToCall.entryPoint();
            } else {
                //Mark that the function call needs to be patched with the entry point later
                functionData.CallTable[make_pair(function.name, generatedCode.size())] = inst.StrValue;
            }

            if (ENABLE_DEBUG) {
                //Only print external functions
                if (!funcToCall.isManaged()) {
                    std::cout << "Calling '" << inst.StrValue + "' at 0x" << std::hex << funcAddr << std::dec << "." << std::endl;
                }
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
    case OpCodes::RET:
        {
            //If debug is enabled, print the stack frame before return (maybe add when called also?)
            if (ENABLE_DEBUG && PRINT_STACK_FRAME) {
                Amd64Backend::moveLongToReg(function.generatedCode, Registers::AX, (long)&rt_printStackFrame);
                Amd64Backend::moveRegToReg(function.generatedCode, Registers::DI, Registers::BP); //BP as the first argument
                Amd64Backend::moveLongToReg(function.generatedCode, Registers::SI, (long)&function); //Address of the function as second argument
                Amd64Backend::callInReg(function.generatedCode, Registers::AX);
            }

            if (!TypeSystem::isPrimitiveType(function.returnType, PrimitiveTypes::Void)) {
                //Pop the return value
                Amd64Backend::popReg(generatedCode, Registers::AX); //pop eax
            }

            //Restore the base pointer
            Amd64Backend::moveRegToReg(generatedCode, Registers::SP, Registers::BP); //mov rsp, rbp
            Amd64Backend::popReg(generatedCode, Registers::BP); //pop rbp

            //Make the return
            Amd64Backend::ret(generatedCode); //ret
        }
    break;
    case OpCodes::LOAD_ARG:
        {
            //Load rax with the arg offset
            Amd64Backend::moveIntToReg(generatedCode, Registers::AX, (inst.Value + stackOffset) * -Amd64Backend::REG_SIZE); //mov rax, <int>

            //Now add the base pointer
            Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::BP); //add rax, rbp

            //Load rax with the argument from the stack
            Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX); //mov rax, [rax]

            //Push the loaded value
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
        break;
    case OpCodes::BR:
        {
            Amd64Backend::jump(generatedCode, 0); //jmp <target>

            //As the exact target in native instructions isn't known, defer to later.
            functionData.BranchTable[generatedCode.size() - 5] = std::make_pair(inst.Value, 5);
        }
        break;
    case OpCodes::BEQ:
    case OpCodes::BNE:
    case OpCodes::BGT:
    case OpCodes::BGE:
    case OpCodes::BLT:
    case OpCodes::BLE:
        {            
            //Pop 2 operands
            Amd64Backend::popReg(generatedCode, Registers::CX); //pop ecx
            Amd64Backend::popReg(generatedCode, Registers::AX); //pop eax

            //Compare and jump
            Amd64Backend::compareRegToReg(generatedCode, Registers::AX, Registers::CX); //cmp rax, rcx
            
            switch (inst.OpCode) {
                case OpCodes::BEQ:
                    Amd64Backend::jumpEqual(generatedCode, 0); //je <target>
                    break;
                case OpCodes::BNE:
                    Amd64Backend::jumpNotEqual(generatedCode, 0); //jne <target>
                    break;
                case OpCodes::BGT:
                    Amd64Backend::jumpGreaterThan(generatedCode, 0); //jg <target>
                    break;
                case OpCodes::BGE:
                    Amd64Backend::jumpGreaterThanOrEqual(generatedCode, 0); //jge <target>
                    break;
                case OpCodes::BLT:
                    Amd64Backend::jumpLessThan(generatedCode, 0); //jl <target>
                    break;
                case OpCodes::BLE:
                    Amd64Backend::jumpLessThanOrEqual(generatedCode, 0); //jle <target>
                    break;
                default:
                    break;
            }

            //As the exact target in native instructions isn't known, defer to later.
            functionData.BranchTable[generatedCode.size() - 6] = std::make_pair(inst.Value, 6);
        }
        break;
    case OpCodes::NEW_ARRAY:
        {
            // auto opTypes = functionData.InstructionOperandTypes[instIndex];
            // Type* elemType = opTypes[0];
            Type* elemType = vmState.getType(inst.StrValue);

            //The pointer to the type as the first arg
            Amd64Backend::moveLongToReg(generatedCode, Registers::DI, (long)elemType); //mov rdi, <addr of type pointer>

            //Pop the size as the second arg
            Amd64Backend::popReg(generatedCode, Registers::SI); //pop rsi

            //Call the newArray runtime function
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&rt_newArray);
            Amd64Backend::callInReg(generatedCode, Registers::AX);

            //Push the returned pointer
            Amd64Backend::pushReg(generatedCode, Registers::AX);
        }
        break;
    case OpCodes::STORE_ELEMENT:
        //Pop the operands
        Amd64Backend::popReg(generatedCode, Registers::DX); //The value to store
        Amd64Backend::popReg(generatedCode, Registers::CX); //The index of the element
        Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the array

        //Bounds check
        generateArrayBoundsCheck(generatedCode);

        //Compute the address of the element
        pushArray(generatedCode, { 0x48, 0x6B, 0xC9, 0x04 }); //imul rcx, 4
        Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::CX); //add rax, rcx

        //Store the element
        Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, 4, Registers::DX); //mov [rax+4], rdx
        break;
    case OpCodes::LOAD_ELEMENT:
        //Pop the operands
        Amd64Backend::popReg(generatedCode, Registers::CX); //The index of the element
        Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the array

        //Bounds check
        generateArrayBoundsCheck(generatedCode);

        //Compute the address of the element
        pushArray(generatedCode, { 0x48, 0x6B, 0xC9, 0x04 }); //imul rcx, 4
        Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::CX); //add rax, rcx
        Amd64Backend::addByteToReg(generatedCode, Registers::AX, 4); //add rax, 4

        //Load the element
        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX); //mov rcx, [rax]
        Amd64Backend::pushReg(generatedCode, Registers::CX); //pop rcx
        break;
    case OpCodes::LOAD_ARRAY_LENGTH:
        //Pop the array ref
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

        //Get the size of the array (an int)
        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX, true); //mov eax, [rax]

        //Push the size
        Amd64Backend::pushReg(generatedCode, Registers::AX); //push eax
        break;
    case OpCodes::NEW_OBJECT:
        {
            Type* structType = vmState.getType(inst.StrValue);

            //The pointer to the type as the first arg
            Amd64Backend::moveLongToReg(generatedCode, Registers::DI, (long)structType); //mov rdi, <addr of type pointer>

            //Call the newObject runtime function
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&rt_newObject);
            Amd64Backend::callInReg(generatedCode, Registers::AX);

            //Push the returned pointer
            Amd64Backend::pushReg(generatedCode, Registers::AX);
        }
        break;
    case OpCodes::LOAD_FIELD:
        {
            //Get the field
            int fieldSepPos = inst.StrValue.find("::");

            auto structName = inst.StrValue.substr(0, fieldSepPos);
            auto fieldName = inst.StrValue.substr(fieldSepPos + 2);

            auto structMetadata = vmState.getStructMetadata(structName);

            int fieldOffset = structMetadata->getFieldOffset(fieldName);

            //Pop the operand
            Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the object

            //Type check
            //generateTypeCheck(generatedCode, structMetadata);

            //Compute the address of the field
            Amd64Backend::addByteToReg(generatedCode, Registers::AX, fieldOffset); //add rax, 4

            //Load the field
            Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX); //mov rcx, [rax]
            Amd64Backend::pushReg(generatedCode, Registers::CX); //pop rcx
        }
        break;
    case OpCodes::STORE_FIELD:
        {
            //Get the field
            int fieldSepPos = inst.StrValue.find("::");

            auto structName = inst.StrValue.substr(0, fieldSepPos);
            auto fieldName = inst.StrValue.substr(fieldSepPos + 2);

            auto structMetadata = vmState.getStructMetadata(structName);

            int fieldOffset = structMetadata->getFieldOffset(fieldName);

            //Pop the operand
            Amd64Backend::popReg(generatedCode, Registers::DX); //The value to store
            Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the object

            //Type check
            //generateTypeCheck(generatedCode, structMetadata);

            //Store the field
            Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, fieldOffset, Registers::DX); //mov [rax+<fieldOffset>], rdx
        }
        break;
    default:
        break;
    }
}
