#include <sys/mman.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <assert.h>

#include "codegenerator.h"
#include "typechecker.h"
#include "type.h"
#include "vmstate.h"
#include "rtlibrary.h"
#include "program.h"
#include "function.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "amd64.h"

FunctionCompilationData::FunctionCompilationData(Function& function)
    : function(function), operandStackSize(0) {

}

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
    Amd64Backend::moveLongToReg(codeGen, Registers::DI, (long)&Runtime::arrayOutOfBoundsError); //mov rdi, <addr of func>
    Amd64Backend::callInReg(codeGen, Registers::DI); //call rdi
}

//Generates null check
void generateNullCheck(CodeGen& codeGen) {
    //Compare the reference with null
    Amd64Backend::moveIntToReg(codeGen, Registers::SI, 0); //mov rsi, 0
    Amd64Backend::compareRegToReg(codeGen, Registers::AX, Registers::SI); //cmp rcx, rsi

    pushArray(codeGen, { 0x75, 10 + 2 }); //jnz <after call>

    //If null, call the error func
    Amd64Backend::moveLongToReg(codeGen, Registers::DI, (long)&Runtime::nullReferenceError); //mov rdi, <addr of func>
    Amd64Backend::callInReg(codeGen, Registers::DI); //call rdi
}

//Generates a call to the given function
void generateCall(CodeGen& codeGen, long funcPtr) {
    Amd64Backend::moveLongToReg(codeGen, Registers::AX, funcPtr);
    Amd64Backend::callInReg(codeGen, Registers::AX);
}

JitFunction CodeGenerator::generateProgram(Program& program, VMState& vmState) {
    std::map<FunctionCall, std::string> callTable;

    //Add the functions to the func table
    for (auto currentFunc : program.functions) {
        auto func = currentFunc.second;
        FunctionDefinition funcDef(func->name(), func->arguments(), func->returnType(), 0, 0);
        auto& binder = vmState.binder();
        binder.define(funcDef);
    }

    //Generate instructions for all functions
    for (auto currentFunc : program.functions) {
        auto func = currentFunc.second;
        FunctionCompilationData funcData { *func };

        auto funcPtr = generateFunction(funcData, vmState);

        if (vmState.enableDebug) {
            std::cout << "Defined function '" << func->name() << "' at 0x" << std::hex << (long)funcPtr << std::dec << "." << std::endl;
        }

        //Add the unresolved call to the program call table
        for (auto call : funcData.callTable) {
            callTable[call.first] = call.second;
        }

        auto signature = vmState.binder().functionSignature(func->name(), func->arguments());

        //Set the entry point & size for the function
        vmState.binder().getFunction(signature).setFunctionBody((long)funcPtr, func->generatedCode.size());
    }

    //Fix unresolved calls
    for (auto call : callTable) {
        auto funcName = call.first.first;
        auto offset = call.first.second;
        auto calledFunc = call.second;

        //Get a pointer to the functions instructions
        long calledFuncAddr = vmState.binder().getFunction(calledFunc).entryPoint();
        unsigned char* funcCode = (unsigned char*)(vmState.binder().getFunction(funcName).entryPoint());

        //Update the call target
        LongToBytes converter;
        converter.LongValue = calledFuncAddr;

        int base = offset + 2;
        for (int i = 0; i < sizeof(long); i++) {
            funcCode[base + i] = converter.ByteValues[i];
        }
    }

    //Make the functions memory executable, but not writable.
    for (auto currentFunc : program.functions) {
        auto func = currentFunc.second;
        auto signature = vmState.binder().functionSignature(func->name(), func->arguments());

        void* mem = (void*)vmState.binder().getFunction(signature).entryPoint();
        int length = func->generatedCode.size();

        int success = mprotect(mem, length, PROT_EXEC | PROT_READ);
        assert(success == 0);
    }

    //Return the main func as entry point
    return (JitFunction)vmState.binder().getFunction("main()").entryPoint();
}

JitFunction CodeGenerator::generateFunction(FunctionCompilationData& functionData, VMState& vmState) {
    TypeChecker::typeCheckFunction(functionData, vmState, vmState.enableDebug && vmState.printTypeChecking);

    auto& function = functionData.function;
    function.instructionOperandTypes = functionData.instructionOperandTypes;
    function.postInstructionOperandTypes = functionData.postInstructionOperandTypes;

    //Calculate the size of the stack aligned to 16 bytes
    int neededStackSize = (function.numArgs() + function.numLocals() + functionData.operandStackSize) * Amd64Backend::REG_SIZE;
    int stackSize = ((neededStackSize + 15) / 16) * 16;

    function.setStackSize(stackSize);

    //Save the base pointer
    Amd64Backend::pushReg(function.generatedCode, Registers::BP); //push rbp
    Amd64Backend::moveRegToReg(function.generatedCode, Registers::BP, Registers::SP); //mov rbp, rsp

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

    //Zero the locals
    if (function.numLocals() > 0) {
        //This method should be faster? but makes the generated code larger
        // Amd64Backend::moveIntToReg(function.generatedCode, Registers::AX, 0); //mov rax, 0

        // for (int i = 0; i < function.numLocals(); i++) {
        //     int localOffset = (i + function.numArgs() + 1) * -Amd64Backend::REG_SIZE;
        //     Amd64Backend::moveRegToMemoryRegWithOffset(function.generatedCode, Registers::BP, localOffset, Registers::AX); //mov [rbp-local], rax
        // }

        //Set the dir flag to decrease
        function.generatedCode.push_back(0xFD); //std

        //Set the address where the locals starts
        Amd64Backend::moveRegToReg(function.generatedCode, Registers::DI, Registers::BP); //mov rdi, rbp
        Amd64Backend::addByteToReg(function.generatedCode, Registers::DI, (function.numArgs() + 1) * -Amd64Backend::REG_SIZE); //add rdi, <locals offset>

        //Set the number of locals
        Amd64Backend::moveIntToReg(function.generatedCode, Registers::CX, function.numLocals()); //mov rcx, <num locals>

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
    for (auto branch : functionData.branchTable) {
        unsigned int source = branch.first;
        unsigned int target = branch.second.first;
        unsigned int instSize = branch.second.second;

        unsigned int nativeTarget = functionData.instructionNumMapping[target];

        //Calculate the native jump location
        IntToBytes converter;
        converter.IntValue = nativeTarget - source - instSize;

        unsigned int sourceOffset = instSize - sizeof(int);

        //Update the source with the native target
        for (int i = 0; i < sizeof(int); i++) {
            function.generatedCode[source + sourceOffset + i] = converter.ByteValues[i];
        }
    }

    //Get a pointer & size of the generated instructions
    unsigned char* code = function.generatedCode.data();
    int length = function.generatedCode.size();

    if (vmState.enableDebug) {
        std::string argsStr = "";
        bool isFirst = true;

        for (auto param : function.arguments()) {
            if (isFirst) {
                isFirst = false;
            } else {
                argsStr += " ";
            }

            argsStr += TypeChecker::typeToString(param);
        }

        std::cout
            << "Generated function '" << function.name() << "(" + argsStr + ") " << TypeChecker::typeToString(function.returnType())
            << "' of size " << length << " bytes."
            << std::endl;
    }

    //Indicates if to output the generated code to a file
    if (vmState.outputGeneratedCode) {
        std::ofstream asmFile (functionData.function.name() + ".jit", std::ios::binary);

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
    auto& function = functionData.function;
    auto& generatedCode = function.generatedCode;
    int stackOffset = 1; //The offset for variables allocated on the stack

    //Make the mapping
    functionData.instructionNumMapping.push_back(generatedCode.size());

    switch (inst.OpCode) {
    case OpCodes::NOP:
        generatedCode.push_back(0x90); //nop
        break;
    case OpCodes::POP:
        //Pop the value
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax
        break;
    case OpCodes::PUSH_INT:
        //Push the value
        Amd64Backend::pushInt(generatedCode, inst.Value.Int); //push <value>
        // Amd64Backend::moveLongToReg(generatedCode, Registers::AX, inst.Value.Int);
        // Amd64Backend::pushReg(generatedCode, Registers::AX);
        break;
    case OpCodes::PUSH_FLOAT:
        {
            //Extract the byte pattern for the float
            const int* floatData = reinterpret_cast<const int*>(&inst.Value.Float);

            //Push the value
            Amd64Backend::pushInt(generatedCode, *floatData); //push <value>
            //Amd64Backend::moveLongToReg(generatedCode, Registers::AX, *floatData);
            //Amd64Backend::pushReg(generatedCode, Registers::AX);
        }
        break;  
    case OpCodes::ADD:
    case OpCodes::SUB:
    case OpCodes::MUL:
    case OpCodes::DIV:
        {
            auto opType = function.instructionOperandTypes[instIndex][0];
            bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
            bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
            bool is32bits = false;

            //Pop 2 operands
            if (intOp) {
                Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
                Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax
            } else if (floatOp) {
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0);
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1);
            }

            //Apply the operator
            switch (inst.OpCode) {
                case OpCodes::ADD:
                    if (intOp) {
                        Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::CX, is32bits); //add eax, ecx
                    } else if (floatOp) {
                        pushArray(generatedCode, { 0xF3, 0x0F, 0x58, 0xC1 }); //addss xmm0, xmm1  
                    }
                    break;
                case OpCodes::SUB:
                    if (intOp) {
                        Amd64Backend::subRegFromReg(generatedCode, Registers::AX, Registers::CX, is32bits); //sub eax, ecx   
                    } else if (floatOp) {
                        pushArray(generatedCode, { 0xF3, 0x0F, 0x5C, 0xC1 }); //subss xmm0, xmm1 
                    }
                    break;
                case OpCodes::MUL:
                    if (intOp) {
                       Amd64Backend::multRegToReg(generatedCode, Registers::AX, Registers::CX, is32bits); //imul eax, ecx 
                    } else if (floatOp) {
                        pushArray(generatedCode, { 0xF3, 0x0F, 0x59, 0xC1 }); //mulss xmm0, xmm1
                    }
                    break;
                case OpCodes::DIV:
                    if (intOp) {
                        pushArray(generatedCode, { 0x99 });
                        Amd64Backend::divRegFromReg(generatedCode, Registers::AX, Registers::CX, is32bits); //idiv eax, ecx
                    } else if (floatOp) {
                        pushArray(generatedCode, { 0xF3, 0x0F, 0x5E, 0xC1 }); //divss xmm0, xmm1
                    }
                    break;
                default:
                    break;
            }

            //Push the result
            if (intOp) {
                Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
            } else if (floatOp) {
                Amd64Backend::pushReg(generatedCode, FloatRegisters::XMM0);
            }
        }
        break;
    case OpCodes::PUSH_TRUE:
        //Push the value
        Amd64Backend::pushInt(generatedCode, 1); //push 1
        break;
    case OpCodes::PUSH_FALSE:
        //Push the value
        Amd64Backend::pushInt(generatedCode, 0); //push 0
        break;
    case OpCodes::AND:
    case OpCodes::OR:
        {
            //Pop 2 operands
            Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
            Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax
            bool is32bits = false;

            //Apply the operator
            switch (inst.OpCode) {
                case OpCodes::AND:
                    Amd64Backend::andRegToReg(generatedCode, Registers::AX, Registers::CX, is32bits); //and eax, ecx
                    break;
                case OpCodes::OR:
                    Amd64Backend::orRegToReg(generatedCode, Registers::AX, Registers::CX, is32bits); //or eax, ecx
                    break;
                default:
                    break;
            }

            //Push the result
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
        break;
    case OpCodes::NOT:
        //Pop 1 operand
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

        //NOT the value
        Amd64Backend::notReg(generatedCode, Registers::AX); //not rax

        //Push the result
        Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        break;
    case OpCodes::CONVERT_INT_TO_FLOAT:
        //Pop 1 operand
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

        //Convert it
        pushArray(generatedCode, { 0xF3, 0x48, 0x0F, 0x2A, 0xC0 }); //cvtsi2ss xmm0,rax 

        //Push it
        Amd64Backend::pushReg(generatedCode, FloatRegisters::XMM0); //push xmm0
        break;
    case OpCodes::CONVERT_FLOAT_TO_INT:
        //Pop 1 operand
        Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0); //pop xmm0

        //Convert it
        pushArray(generatedCode, { 0xF3, 0x48, 0x0F, 0x2C, 0xC0 }); //cvttss2si rax,xmm0

        //Push it
        Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        break;
    case OpCodes::COMPARE_EQUAL:
    case OpCodes::COMPARE_NOT_EQUAL:
    case OpCodes::COMPARE_GREATER_THAN:
    case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
    case OpCodes::COMPARE_LESS_THAN:
    case OpCodes::COMPARE_LESS_THAN_OR_EQUAL:
        {
            auto opType = function.instructionOperandTypes[instIndex][0];
            bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
            bool boolType = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Bool);
            bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);

            if (intOp || boolType) {
                //Pop 2 operands
                Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
                Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

                //Compare
                Amd64Backend::compareRegToReg(generatedCode, Registers::AX, Registers::CX); //cmp rax, rcx
            } else if (floatOp) {
                //Pop 2 operands
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1); //pop xmm1
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0); //pop xmm0

                //Compare
                pushArray(generatedCode, { 0x0F, 0x2E, 0xC1 }); //ucomiss xmm0, xmm1 
            }

            //Jump
            int target = 5 + 5;
            int start = generatedCode.size();

            switch (inst.OpCode) {
                case OpCodes::COMPARE_EQUAL:
                    Amd64Backend::jumpEqual(generatedCode, target);
                    break;
                case OpCodes::COMPARE_NOT_EQUAL:
                    Amd64Backend::jumpNotEqual(generatedCode, target);
                    break;
                case OpCodes::COMPARE_GREATER_THAN:
                    Amd64Backend::jumpGreaterThan(generatedCode, target);
                    break;
                case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
                    Amd64Backend::jumpGreaterThanOrEqual(generatedCode, target);
                    break;
                case OpCodes::COMPARE_LESS_THAN:
                    Amd64Backend::jumpLessThan(generatedCode, target);
                    break;
                case OpCodes::COMPARE_LESS_THAN_OR_EQUAL:
                    Amd64Backend::jumpLessThanOrEqual(generatedCode, target);
                    break;
                default:
                    break;
            }

            //False
            Amd64Backend::pushInt(generatedCode, 0);
            Amd64Backend::jump(generatedCode, 5);

            //True
            Amd64Backend::pushInt(generatedCode, 1);
        }
        break;
    case OpCodes::LOAD_LOCAL:
        {
            //Load rax with the locals offset
            Amd64Backend::moveIntToReg(generatedCode, Registers::AX, (inst.Value.Int + function.numArgs() + stackOffset) * -Amd64Backend::REG_SIZE); //mov rax, <local>

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

            int localOffset = (inst.Value.Int + function.numArgs() + stackOffset) * -Amd64Backend::REG_SIZE;

            //Store the operand at the given local
            Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::BP, localOffset, Registers::AX); //mov [rbp-local], rax
        }
        break;
    case OpCodes::CALL:
        {   
            //Check if defined
            auto signature = vmState.binder().functionSignature(inst.StrValue, inst.Parameters);

            //Call the pushFunc runtime function
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::pushFunc);
            Amd64Backend::moveLongToReg(generatedCode, Registers::DI, (long)&function); //Address of the func handle as the target as first arg
            Amd64Backend::moveLongToReg(generatedCode, Registers::SI, instIndex); //Current inst index as second arg
            Amd64Backend::callInReg(generatedCode, Registers::AX);

            //Get the address of the function to call
            long funcAddr = 0;

            auto funcToCall = vmState.binder().getFunction(signature);
            int numArgs = funcToCall.arguments().size();

            //Set the function arguments
            auto opTypes = function.instructionOperandTypes[instIndex];

            if (numArgs >= 4) {
                auto argType = opTypes.at(numArgs - 4);
                if (argType->name() == "Float") {    
                    Amd64Backend::popReg(generatedCode, FloatRegisters::XMM3);             
                } else {
                    Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
                }
            }

            if (numArgs >= 3) {
                auto argType = opTypes.at(numArgs - 3);
                if (argType->name() == "Float") {   
                    Amd64Backend::popReg(generatedCode, FloatRegisters::XMM2);            
                } else {
                    Amd64Backend::popReg(generatedCode, Registers::DX); //pop rdx
                }
            }

            if (numArgs >= 2) {
                auto argType = opTypes.at(numArgs - 2);
                if (argType->name() == "Float") { 
                    Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1);                 
                } else {
                    Amd64Backend::popReg(generatedCode, Registers::SI); //pop rsi
                }
            }

            if (numArgs >= 1) {
                auto argType = opTypes.at(numArgs - 1);
                if (argType->name() == "Float") {
                    Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0);
                } else {
                    Amd64Backend::popReg(generatedCode, Registers::DI); //pop rdi
                }
            }

            //Check if the function entry point is defined yet
            if (funcToCall.entryPoint() != 0) {
                funcAddr = funcToCall.entryPoint();
            } else {
                //Mark that the function call needs to be patched with the entry point later
                functionData.callTable[make_pair(vmState.binder().functionSignature(function), generatedCode.size())] = signature;
            }

            // if (vmState.enableDebug) {
            //     //Only print external functions
            //     if (!funcToCall.isManaged()) {
            //         std::cout << "Calling '" << inst.StrValue + "' at 0x" << std::hex << funcAddr << std::dec << "." << std::endl;
            //     }
            // }

            //Move the address of the call to rax
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, funcAddr); //mov rax, <addr>

            //Make the call
            Amd64Backend::callInReg(generatedCode, Registers::AX); //call rax

            //Push the result
            if (funcToCall.returnType()->name() != "Void") {
                if (funcToCall.returnType()->name() == "Float") {
                    Amd64Backend::pushReg(generatedCode, FloatRegisters::XMM0);
                } else {
                    Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
                }
            }

            //Call the popFunc runtime function
            if (function.name() != "main") {
                Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::popFunc);
                Amd64Backend::callInReg(generatedCode, Registers::AX);
            }
        }
        break;
    case OpCodes::RET:
        {
            //If debug is enabled, print the stack frame before return
            if (vmState.enableDebug && vmState.printStackFrame) {
                Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::printStackFrame);
                Amd64Backend::moveRegToReg(generatedCode, Registers::DI, Registers::BP); //BP as the first argument
                Amd64Backend::moveLongToReg(generatedCode, Registers::SI, (long)&function); //Address of the function as second argument
                Amd64Backend::callInReg(generatedCode, Registers::AX);         
            }

            if (!TypeSystem::isPrimitiveType(function.returnType(), PrimitiveTypes::Void)) {
                //Pop the return value
                if (function.returnType()->name() == "Float") {
                    Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0);
                } else {
                    Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax
                }
            }

            //Restore the base pointer
            Amd64Backend::moveRegToReg(generatedCode, Registers::SP, Registers::BP); //mov rsp, rbp
            Amd64Backend::popReg(generatedCode, Registers::BP); //pop rbp
            //pushArray(generatedCode, { 0xC9 }); //leave

            //Make the return
            Amd64Backend::ret(generatedCode); //ret
        }
    break;
    case OpCodes::LOAD_ARG:
        {
            //Load rax with the arg offset
            Amd64Backend::moveIntToReg(generatedCode, Registers::AX, (inst.Value.Int + stackOffset) * -Amd64Backend::REG_SIZE); //mov rax, <int>

            //Now add the base pointer
            Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::BP); //add rax, rbp

            //Load rax with the argument from the stack
            Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX); //mov rax, [rax]

            //Push the loaded value
            Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        }
        break;
    case OpCodes::BRANCH:
        {
            Amd64Backend::jump(generatedCode, 0); //jmp <target>

            //As the exact target in native instructions isn't known, defer to later.
            functionData.branchTable[generatedCode.size() - 5] = std::make_pair(inst.Value.Int, 5);
        }
        break;
    case OpCodes::BRANCH_EQUAL:
    case OpCodes::BRANCH_NOT_EQUAL:
    case OpCodes::BRANCH_GREATER_THAN:
    case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
    case OpCodes::BRANCH_LESS_THAN:
    case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
        {           
            auto opType = function.instructionOperandTypes[instIndex][0];
            bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
            bool boolType = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Bool);
            bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);

            if (intOp || boolType) {
                //Pop 2 operands
                Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
                Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

                //Compare
                Amd64Backend::compareRegToReg(generatedCode, Registers::CX, Registers::AX); //cmp rcx, rax
            } else if (floatOp) {
                //Pop 2 operands
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1); //pop xmm1
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0); //pop xmm0

                //Compare
                pushArray(generatedCode, { 0x0F, 0x2E, 0xC1 }); //ucomiss xmm0, xmm1 
            } 

            switch (inst.OpCode) {
                case OpCodes::BRANCH_EQUAL:
                    Amd64Backend::jumpEqual(generatedCode, 0); //je <target>
                    break;
                case OpCodes::BRANCH_NOT_EQUAL:
                    Amd64Backend::jumpNotEqual(generatedCode, 0); //jne <target>
                    break;
                case OpCodes::BRANCH_GREATER_THAN:
                    Amd64Backend::jumpGreaterThan(generatedCode, 0); //jg <target>
                    break;
                case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
                    Amd64Backend::jumpGreaterThanOrEqual(generatedCode, 0); //jge <target>
                    break;
                case OpCodes::BRANCH_LESS_THAN:
                    Amd64Backend::jumpLessThan(generatedCode, 0); //jl <target>
                    break;
                case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
                    Amd64Backend::jumpLessThanOrEqual(generatedCode, 0); //jle <target>
                    break;
                default:
                    break;
            }

            //As the exact target in native instructions isn't known, defer to later.
            functionData.branchTable[generatedCode.size() - 6] = std::make_pair(inst.Value.Int, 6);
        }
        break;
    case OpCodes::PUSH_NULL:
        Amd64Backend::pushInt(generatedCode, 0); //push 0
        break;
    case OpCodes::NEW_ARRAY:
        {
            auto elemType = vmState.getType(inst.StrValue);

            if (!vmState.disableGC) {
                //Call the garbageCollect runtime function
                Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::garbageCollect);
                Amd64Backend::moveRegToReg(generatedCode, Registers::DI, Registers::BP); //BP as the first argument
                Amd64Backend::moveLongToReg(generatedCode, Registers::SI, (long)&function); //Address of the function as second argument
                Amd64Backend::moveIntToReg(generatedCode, Registers::DX, instIndex); //Current inst index as third argument
                Amd64Backend::callInReg(generatedCode, Registers::AX);
            }
            
            //The pointer to the type as the first arg
            Amd64Backend::moveLongToReg(generatedCode, Registers::DI, (long)elemType); //mov rdi, <addr of type pointer>

            //Pop the size as the second arg
            Amd64Backend::popReg(generatedCode, Registers::SI); //pop rsi

            //Check that the size >= 0
            Amd64Backend::moveIntToReg(generatedCode, Registers::CX, 0); //mov rax, 0
            Amd64Backend::compareRegToReg(generatedCode, Registers::CX, Registers::SI); //cmp rcx, rsi
            pushArray(generatedCode, { 0x7E, 10 + 2 }); //jle <after call>.

            //If invalid call the error func
            Amd64Backend::moveLongToReg(generatedCode, Registers::DI, (long)&Runtime::invalidArrayCreation); //mov rdi, <addr of func>
            Amd64Backend::callInReg(generatedCode, Registers::DI); //call rdi

            //Call the newArray runtime function
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::newArray);
            Amd64Backend::callInReg(generatedCode, Registers::AX);

            //Push the returned pointer
            Amd64Backend::pushReg(generatedCode, Registers::AX);
        }
        break;
    case OpCodes::STORE_ELEMENT:
        {
            auto elemType = vmState.getType(inst.StrValue);

            //Pop the operands
            Amd64Backend::popReg(generatedCode, Registers::DX); //The value to store
            Amd64Backend::popReg(generatedCode, Registers::CX); //The index of the element
            Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the array

            //Null check
            generateNullCheck(generatedCode);

            //Bounds check
            generateArrayBoundsCheck(generatedCode);

            //Compute the address of the element
            pushArray(generatedCode, { 0x48, 0x6B, 0xC9, (unsigned char)TypeSystem::sizeOfType(elemType) }); //imul rcx, <size of type>
            Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::CX); //add rax, rcx

            //Store the element
            auto elemSize = TypeSystem::sizeOfType(elemType);
            bool is32bits = elemSize == 4;
            bool is8bits = elemSize == 1;

            if (!is8bits) {
                Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, 4, Registers::DX, is32bits); //mov [rax+4], r/edx
            } else {
                pushArray(generatedCode, { 0x88, 0x50, 0x04 }); //mov [rax+4], dl
            }
        }
        break;
    case OpCodes::LOAD_ELEMENT:
        {
            auto elemType = vmState.getType(inst.StrValue);

            //Pop the operands
            Amd64Backend::popReg(generatedCode, Registers::CX); //The index of the element
            Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the array

            //Null check
            generateNullCheck(generatedCode);

            //Bounds check
            generateArrayBoundsCheck(generatedCode);

            //Compute the address of the element
            pushArray(generatedCode, { 0x48, 0x6B, 0xC9, (unsigned char)TypeSystem::sizeOfType(elemType) }); //imul rcx, <size of type>
            Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::CX); //add rax, rcx
            Amd64Backend::addByteToReg(generatedCode, Registers::AX, 4); //add rax, 4

            //Load the element
            auto elemSize = TypeSystem::sizeOfType(elemType);
            bool is32bits = elemSize == 4;
            bool is8bits = elemSize == 1;

            if (!is8bits) {
                Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX, is32bits); //mov r/ecx, [rax]
            } else {
                pushArray(generatedCode, { 0x8A, 0x08 }); //mov cl, [rax]
            }

            Amd64Backend::pushReg(generatedCode, Registers::CX); //pop rcx
        }
        break;
    case OpCodes::LOAD_ARRAY_LENGTH:
        //Pop the array ref
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax

        //Null check
        generateNullCheck(generatedCode);

        //Get the size of the array (an int)
        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX, true); //mov eax, [rax]

        //Push the size
        Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        break;
    case OpCodes::NEW_OBJECT:
        {
            auto structType = vmState.getType(inst.StrValue);

            //Call the garbageCollect runtime function
            if (!vmState.disableGC) {
                Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::garbageCollect);
                Amd64Backend::moveRegToReg(generatedCode, Registers::DI, Registers::BP); //BP as the first argument
                Amd64Backend::moveLongToReg(generatedCode, Registers::SI, (long)&function); //Address of the function as second argument
                Amd64Backend::moveIntToReg(generatedCode, Registers::DX, instIndex); //Current inst index as third argument
                Amd64Backend::callInReg(generatedCode, Registers::AX);
            }

            //Call the newObject runtime function
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::newObject);
            Amd64Backend::moveLongToReg(generatedCode, Registers::DI, (long)structType); //The pointer to the type as the first arg
            Amd64Backend::callInReg(generatedCode, Registers::AX);

            //Push the returned pointer
            Amd64Backend::pushReg(generatedCode, Registers::AX);
        }
        break;
    case OpCodes::GARBAGE_COLLECT:
        {
            //Call the garbageCollect runtime function
            Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (long)&Runtime::garbageCollect);
            Amd64Backend::moveRegToReg(generatedCode, Registers::DI, Registers::BP); //BP as the first argument
            Amd64Backend::moveLongToReg(generatedCode, Registers::SI, (long)&function); //Address of the function as second argument
            Amd64Backend::moveIntToReg(generatedCode, Registers::DX, instIndex); //Current inst index as third argument
            Amd64Backend::callInReg(generatedCode, Registers::AX);
        }
        break;
    case OpCodes::LOAD_FIELD:
    case OpCodes::STORE_FIELD:
        {
            //Get the field
            std::pair<std::string, std::string> structAndField;
            TypeSystem::getStructAndField(inst.StrValue, structAndField);

            auto structMetadata = vmState.structProvider()[structAndField.first];
            int fieldOffset = structMetadata.fieldOffset(structAndField.second);

            //Get the size of the field
            auto elemSize = TypeSystem::sizeOfType(structMetadata.getField(structAndField.second));
            bool is32bits = elemSize == 4;
            bool is8bits = elemSize == 1;

            if (inst.OpCode == OpCodes::LOAD_FIELD) {
                //Pop the operand
                Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the object

                //Null check
                generateNullCheck(generatedCode);

                //Compute the address of the field
                Amd64Backend::addByteToReg(generatedCode, Registers::AX, fieldOffset); //add rax, <field offset>

                //Load the field
                //Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX); //mov rcx, [rax]
                if (!is8bits) {
                    Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX, is32bits); //mov r/ecx, [rax]
                } else {
                    pushArray(generatedCode, { 0x8A, 0x08 }); //mov cl, [rax]
                }

                Amd64Backend::pushReg(generatedCode, Registers::CX); //pop rcx
            } else {
                //Pop the operand
                Amd64Backend::popReg(generatedCode, Registers::DX); //The value to store
                Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the object

                //Null check
                generateNullCheck(generatedCode);

                //Store the field
                //Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, fieldOffset, Registers::DX); //mov [rax+<fieldOffset>], rdx
                if (!is8bits) {
                    Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, fieldOffset, Registers::DX, is32bits); //mov [rax+<fieldOffset>], r/edx
                } else {
                    pushArray(generatedCode, { 0x88, 0x50, (unsigned char)fieldOffset }); //mov [rax+4], dl
                }
            }
        }
        break;
    }
}
