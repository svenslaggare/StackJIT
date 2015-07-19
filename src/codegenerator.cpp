#include "codegenerator.h"
#include "typechecker.h"
#include "type.h"
#include "vmstate.h"
#include "rtlibrary.h"
#include "function.h"
#include "instructions.h"

#include <string.h>
#include <iostream>

namespace {
    void pushArray(std::vector<unsigned char>& dest, const std::vector<unsigned char>& values) {
        for (auto current : values) {
            dest.push_back(current);
        }
    }
}

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

	//Allocate and copy memory
	auto handlerMemory = memoryManger.allocateMemory(handlerCode.size());
	memcpy(handlerMemory, handlerCode.data(), handlerCode.size());

	//Set the pointers to the handlers
	mNullCheckHandler = (unsigned char*)handlerMemory + nullHandlerOffset;
	mArrayBoundsCheckHandler = (unsigned char*)handlerMemory + arrayBoundsHandlerOffset;
	mArrayCreationCheckHandler = (unsigned char*)handlerMemory + arrayCreationHandler;
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
	//pushArray(codeGen, { 0x7E, 10 + 2 }); //jle <after call>.

	//Jump to handler if invalid
	Amd64Backend::jumpGreaterThan(codeGen, 0); //jg <array creation handler>
	function.unresolvedNativeBranches.insert({ codeGen.size() - 6, (long)mArrayCreationCheckHandler });
}

CodeGenerator::CodeGenerator(const CallingConvention& callingConvention, const ExceptionHandling& exceptionHandling)
    : mCallingConvention(callingConvention), mExceptionHandling(exceptionHandling) {

}

void CodeGenerator::generateCall(CodeGen& codeGen, long funcPtr, Registers addrReg) {
	Amd64Backend::moveLongToReg(codeGen, addrReg, funcPtr);
	Amd64Backend::callInReg(codeGen, addrReg);
}

void CodeGenerator::generateGCCall(CodeGen& generatedCode, Function& function, int instIndex, bool saveBSP) {
	if (saveBSP) {
		Amd64Backend::pushReg(generatedCode, Registers::BP);
	}

	Amd64Backend::moveRegToReg(generatedCode, RegisterCallArguments::Arg0, Registers::BP); //BP as the first argument
	Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg1, (long)&function); //Address of the function as second argument
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg2, instIndex); //Current inst index as third argument
	generateCall(generatedCode, (long)&Runtime::garbageCollect);

	if (saveBSP) {
		Amd64Backend::popReg(generatedCode, Registers::BP);
	}
}

void CodeGenerator::initializeFunction(FunctionCompilationData& functionData) {
    auto& function = functionData.function;

    //Calculate the size of the stack aligned to 16 bytes
//    std::size_t neededStackSize = (function.numParams() + function.numLocals() + functionData.operandStackSize) * Amd64Backend::REG_SIZE;
    std::size_t neededStackSize = (function.numParams() + function.numLocals()) * Amd64Backend::REG_SIZE;
    std::size_t stackSize = ((neededStackSize + 15) / 16) * 16;
//     std::size_t stackSize = neededStackSize;

    function.setStackSize(stackSize);

    //Save the base pointer
    Amd64Backend::pushReg(function.generatedCode, Registers::BP); //push rbp
    Amd64Backend::moveRegToReg(function.generatedCode, Registers::BP, Registers::SP); //mov rbp, rsp

    if (stackSize > 0) {
        //Make room for the variables on the stack
        if (stackSize < 128) {
            Amd64Backend::subByteFromReg(function.generatedCode, Registers::SP, (char)stackSize); //sub rsp, <size of stack>
        } else {
            Amd64Backend::subIntFromReg(function.generatedCode, Registers::SP, (int)stackSize); //sub rsp, <size of stack>
        }
    }

    mCallingConvention.moveArgsToStack(functionData);
    zeroLocals(functionData);
}

void CodeGenerator::zeroLocals(FunctionCompilationData& functionData) {
    auto& function = functionData.function;

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
        Amd64Backend::addByteToReg(function.generatedCode, Registers::DI, (function.numParams() + 1) * -Amd64Backend::REG_SIZE); //add rdi, <locals offset>

        //Set the number of locals
        Amd64Backend::moveIntToReg(function.generatedCode, Registers::CX, function.numLocals()); //mov rcx, <num locals>

        //Zero eax
		Amd64Backend::xorRegToReg(function.generatedCode, Registers::AX, Registers::AX, true); //xor eax, eax

        //Execute the zeroing
        pushArray(function.generatedCode, { 0xF3, 0x48, 0xAB }); //rep stosq

        //Clear the dir flag
        function.generatedCode.push_back(0xFC); //cld
    }
}

void CodeGenerator::generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex) {
    auto& function = functionData.function;
    auto& generatedCode = function.generatedCode;
    int stackOffset = 1; //The offset for variables allocated on the stack

    //Make the mapping
    functionData.instructionNumMapping.push_back(generatedCode.size());

    switch (inst.opCode()) {
    case OpCodes::NOP:
        generatedCode.push_back(0x90); //nop
        break;
    case OpCodes::POP:
        //Pop the value
        Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax
        break;
    case OpCodes::PUSH_INT:
        //Push the value
        Amd64Backend::pushInt(generatedCode, inst.intValue); //push <value>
        break;
    case OpCodes::PUSH_FLOAT:
        {
            //Extract the byte pattern for the float
            const int* floatData = reinterpret_cast<const int*>(&inst.floatValue);

            //Push the value
            Amd64Backend::pushInt(generatedCode, *floatData); //push <value>
        }
        break;
     case OpCodes::PUSH_CHAR:
        //Push the value
        pushArray(generatedCode, { 0x6A, (unsigned char)inst.charValue }); //push <value>
        break;
    case OpCodes::ADD:
    case OpCodes::SUB:
    case OpCodes::MUL:
    case OpCodes::DIV:
        {
            auto opType = inst.operandTypes()[0];
            bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
            bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
            bool is32bits = true;

            //Pop 2 operands
            if (intOp) {
                Amd64Backend::popReg(generatedCode, Registers::CX); //pop rcx
                Amd64Backend::popReg(generatedCode, Registers::AX); //pop rax
            } else if (floatOp) {
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM0);
                Amd64Backend::popReg(generatedCode, FloatRegisters::XMM1);
            }

            //Apply the operator
            switch (inst.opCode()) {
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
                        pushArray(generatedCode, { 0x99 }); //cdq
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
            switch (inst.opCode()) {
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
            auto opType = inst.operandTypes()[0];
            bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
            bool boolType = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Bool);
            bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
            bool unsignedComparison = false;

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
                unsignedComparison = true;
            }

            //Jump
            int target = 5 + 5;

            switch (inst.opCode()) {
                case OpCodes::COMPARE_EQUAL:
                    Amd64Backend::jumpEqual(generatedCode, target);
                    break;
                case OpCodes::COMPARE_NOT_EQUAL:
                    Amd64Backend::jumpNotEqual(generatedCode, target);
                    break;
                case OpCodes::COMPARE_GREATER_THAN:
                    if (unsignedComparison) {
                        Amd64Backend::jumpGreaterThanUnsigned(generatedCode, target);
                    } else {
                        Amd64Backend::jumpGreaterThan(generatedCode, target);
                    }
                    break;
                case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
                    if (unsignedComparison) {
                        Amd64Backend::jumpGreaterThanOrEqualUnsigned(generatedCode, target);
                    } else {
                        Amd64Backend::jumpGreaterThanOrEqual(generatedCode, target);
                    }
                    break;
                case OpCodes::COMPARE_LESS_THAN:
                    if (unsignedComparison) {
                        Amd64Backend::jumpLessThanUnsigned(generatedCode, target);
                    } else {
                        Amd64Backend::jumpLessThan(generatedCode, target);
                    }
                    break;
                case OpCodes::COMPARE_LESS_THAN_OR_EQUAL:
                    if (unsignedComparison) {
                        Amd64Backend::jumpLessThanOrEqualUnsigned(generatedCode, target);
                    } else {
                        Amd64Backend::jumpLessThanOrEqual(generatedCode, target);
                    }
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
            int localOffset = (inst.intValue + (int)function.numParams() + stackOffset) * -Amd64Backend::REG_SIZE;
            Amd64Backend::moveIntToReg(generatedCode, Registers::AX, localOffset); //mov rax, <local>

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

            int localOffset = (inst.intValue + (int)function.numParams() + stackOffset) * -Amd64Backend::REG_SIZE;

            //Store the operand at the given local
            Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::BP, (char)localOffset, Registers::AX); //mov [rbp-local], rax
        }
        break;
    case OpCodes::CALL:
    case OpCodes::CALL_INSTANCE:
        {
            std::string calledSignature = "";

            if (inst.opCode() == OpCodes::CALL_INSTANCE) {
                calledSignature = vmState.binder().memberFunctionSignature(inst.calledStructType, inst.strValue, inst.parameters);
            } else {
                calledSignature = vmState.binder().functionSignature(inst.strValue, inst.parameters);
            }

            auto funcToCall = vmState.binder().getFunction(calledSignature);

			if (!funcToCall.isMacroFunction()) {
				//Call the pushFunc runtime function
				Amd64Backend::pushReg(generatedCode, Registers::BP);
				Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0, (long) &function); //Address of the func handle as the target as first arg
				Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg1, instIndex); //Current inst index as second arg
				generateCall(generatedCode, (long) &Runtime::pushFunc);
				Amd64Backend::popReg(generatedCode, Registers::BP);

				//Get the address of the function to call
				long funcAddr = 0;
				int numArgs = (int)funcToCall.arguments().size();

				//Set the function arguments
				auto& opTypes = inst.operandTypes();

				mCallingConvention.callFunctionArguments(functionData, funcToCall, [&](int arg) {
					return opTypes.at(numArgs - 1 - arg);
				});

				if (inst.opCode() == OpCodes::CALL_INSTANCE) {
					//Null check
					Amd64Backend::pushReg(generatedCode, Registers::CX);
					mExceptionHandling.addNullCheck(functionData, RegisterCallArguments::Arg0, Registers::CX);
					Amd64Backend::popReg(generatedCode, Registers::CX);
				}

				if (funcToCall.isManaged()) {
					//Mark that the function call needs to be patched with the entry point later
					functionData.unresolvedCalls.insert({
						UnresolvedFunctionCall(
							FunctionCallType::Relative,
							vmState.binder().functionSignature(function),
							generatedCode.size()),
						calledSignature
					});

					//Make the call
					Amd64Backend::call(generatedCode, 0);
				} else {
					//Unmanaged functions are located beyond one int, direct addressing must be used.
					//Check if the function entry point is defined yet
					if (funcToCall.entryPoint() != 0) {
						funcAddr = funcToCall.entryPoint();
					} else {
						//Mark that the function call needs to be patched with the entry point later
						functionData.unresolvedCalls.insert({
							UnresolvedFunctionCall(
								FunctionCallType::Absolute,
								vmState.binder().functionSignature(function),
								generatedCode.size()),
							calledSignature
						});
					}

					//Make the call
					generateCall(generatedCode, funcAddr);
				}

				//Push the result
				mCallingConvention.returnValue(functionData, funcToCall);

				//Call the popFunc runtime function
				Amd64Backend::pushReg(generatedCode, Registers::BP);
				generateCall(generatedCode, (long) &Runtime::popFunc);
				Amd64Backend::popReg(generatedCode, Registers::BP);
			} else {
				//Invoke the macro function
				MacroFunctionContext context(vmState, mCallingConvention, mExceptionHandling, functionData, inst, instIndex);
				funcToCall.macroFunction()(context);
			}
        }
        break;
    case OpCodes::RET:
        {
            //If debug is enabled, print the stack frame before return
            if (vmState.enableDebug && vmState.printStackFrame) {
                Amd64Backend::pushReg(generatedCode, Registers::BP);
                Amd64Backend::moveRegToReg(generatedCode, RegisterCallArguments::Arg0, Registers::BP); //BP as the first argument
                Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg1, (long)&function); //Address of the function as second argument
                generateCall(generatedCode, (long)&Runtime::printStackFrame);
                Amd64Backend::popReg(generatedCode, Registers::BP);
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
            Amd64Backend::moveIntToReg(generatedCode, Registers::AX, (inst.intValue + stackOffset) * -Amd64Backend::REG_SIZE); //mov rax, <int>

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
            functionData.unresolvedBranches.insert({
            	generatedCode.size() - 5,
            	BranchTarget(inst.intValue, 5)
            });
        }
        break;
    case OpCodes::BRANCH_EQUAL:
    case OpCodes::BRANCH_NOT_EQUAL:
    case OpCodes::BRANCH_GREATER_THAN:
    case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
    case OpCodes::BRANCH_LESS_THAN:
    case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
        {
            auto opType = inst.operandTypes()[0];
            bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
            bool boolType = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Bool);
            bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
            bool unsignedComparison = false;

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
                unsignedComparison = true;
            }

            switch (inst.opCode()) {
                case OpCodes::BRANCH_EQUAL:
                    Amd64Backend::jumpEqual(generatedCode, 0); //je <target>
                    break;
                case OpCodes::BRANCH_NOT_EQUAL:
                    Amd64Backend::jumpNotEqual(generatedCode, 0); //jne <target>
                    break;
                case OpCodes::BRANCH_GREATER_THAN:
                    if (unsignedComparison) {
                        Amd64Backend::jumpGreaterThanUnsigned(generatedCode, 0); //jg <target>
                    } else {
                        Amd64Backend::jumpGreaterThan(generatedCode, 0); //jg <target>
                    }
                    break;
                case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
                    if (unsignedComparison) {
                        Amd64Backend::jumpGreaterThanOrEqualUnsigned(generatedCode, 0); //jge <target>
                    } else {
                        Amd64Backend::jumpGreaterThanOrEqual(generatedCode, 0); //jge <target>
                    }
                    break;
                case OpCodes::BRANCH_LESS_THAN:
                    if (unsignedComparison){
                        Amd64Backend::jumpLessThanUnsigned(generatedCode, 0); //jl <target>
                    } else {
                        Amd64Backend::jumpLessThan(generatedCode, 0); //jl <target>
                    }
                    break;
                case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
                    if (unsignedComparison) {
                        Amd64Backend::jumpLessThanOrEqualUnsigned(generatedCode, 0); //jle <target>
                    } else {
                        Amd64Backend::jumpLessThanOrEqual(generatedCode, 0); //jle <target>
                    }
                    break;
                default:
                    break;
            }

            //As the exact target in native instructions isn't known, defer to later.
            functionData.unresolvedBranches.insert({
            	generatedCode.size() - 6,
            	BranchTarget(inst.intValue, 6)
            });
        }
        break;
    case OpCodes::PUSH_NULL:
        Amd64Backend::pushInt(generatedCode, 0); //push 0
        break;
    case OpCodes::NEW_ARRAY:
        {
            auto elemType = vmState.typeProvider().getType(inst.strValue);

            if (!vmState.disableGC) {
                generateGCCall(generatedCode, function, instIndex, true);
            }

            //The pointer to the type as the first arg
            Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0, (long)elemType); //mov rdi, <addr of type pointer>

            //Pop the size as the second arg
            Amd64Backend::popReg(generatedCode, RegisterCallArguments::Arg1); //pop rsi

			//Check that the size >= 0
			mExceptionHandling.addArrayCreationCheck(functionData);

            //Call the newArray runtime function
            Amd64Backend::pushReg(generatedCode, Registers::BP);
            generateCall(generatedCode, (long)&Runtime::newArray);
            Amd64Backend::popReg(generatedCode, Registers::BP);

            //Push the returned pointer
            Amd64Backend::pushReg(generatedCode, Registers::AX);
        }
        break;
    case OpCodes::STORE_ELEMENT:
        {
            auto elemType = vmState.typeProvider().getType(inst.strValue);

            //Pop the operands
            Amd64Backend::popReg(generatedCode, Registers::DX); //The value to store
            Amd64Backend::popReg(generatedCode, Registers::CX); //The index of the element
            Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the array

            //Null check
			mExceptionHandling.addNullCheck(functionData);

            //Bounds check
			mExceptionHandling.addArrayBoundsCheck(functionData);

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
            auto elemType = vmState.typeProvider().getType(inst.strValue);

            //Pop the operands
            Amd64Backend::popReg(generatedCode, Registers::CX); //The index of the element
            Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the array

			//Null check
			mExceptionHandling.addNullCheck(functionData);

			//Bounds check
			mExceptionHandling.addArrayBoundsCheck(functionData);

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
        mExceptionHandling.addNullCheck(functionData);

        //Get the size of the array (an int)
        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX, true); //mov eax, [rax]

        //Push the size
        Amd64Backend::pushReg(generatedCode, Registers::AX); //push rax
        break;
    case OpCodes::NEW_OBJECT:
        {
            auto structType = inst.calledStructType;

            //Call the garbageCollect runtime function
            if (!vmState.disableGC) {
                generateGCCall(generatedCode, function, instIndex, true);
            }

            //Call the newObject runtime function
            Amd64Backend::pushReg(generatedCode, Registers::BP);
            Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0, (long)structType); //The pointer to the type as the first arg
            generateCall(generatedCode, (long)&Runtime::newObject);
            Amd64Backend::popReg(generatedCode, Registers::BP);

            //Call the constructor
            std::string calledSignature = vmState.binder().memberFunctionSignature(
                inst.calledStructType,
                inst.strValue,
                inst.parameters);

            auto funcToCall = vmState.binder().getFunction(calledSignature);
            int numArgs = (int)funcToCall.arguments().size() - 1;

            //Set the constructor arguments
            Amd64Backend::moveRegToReg(generatedCode, RegisterCallArguments::Arg0, Registers::AX);

            //Constructor arguments are not passed correctly of the stack, fix later.
            for (int i = numArgs - 1; i >= 0; i--) {
                mCallingConvention.callFunctionArgument(functionData, i + 1, inst.parameters.at(i), funcToCall);
            }

            //Push the reference to the created object
            Amd64Backend::pushReg(generatedCode, Registers::AX);

            //Mark that the constructor needs to be patched with the entry point later
            functionData.unresolvedCalls.insert({
                UnresolvedFunctionCall(
                    FunctionCallType::Relative,
                    vmState.binder().functionSignature(function),
                    generatedCode.size()),
                calledSignature
            });

            //Call the constructor
            Amd64Backend::call(generatedCode, 0);
        }
        break;
    case OpCodes::LOAD_FIELD:
    case OpCodes::STORE_FIELD:
        {
            //Get the field
            std::pair<std::string, std::string> structAndField;
            TypeSystem::getStructAndField(inst.strValue, structAndField);

            auto structMetadata = vmState.structProvider()[structAndField.first];
            auto& field = structMetadata.fields().at(structAndField.second);
            int fieldOffset = field.offset();

            //Get the size of the field
            auto elemSize = TypeSystem::sizeOfType(field.type());
            bool is32bits = elemSize == 4;
            bool is8bits = elemSize == 1;

            if (inst.opCode() == OpCodes::LOAD_FIELD) {
                //Pop the operand
                Amd64Backend::popReg(generatedCode, Registers::AX); //The address of the object

                //Null check
				mExceptionHandling.addNullCheck(functionData);

                //Compute the address of the field
                Amd64Backend::addByteToReg(generatedCode, Registers::AX, fieldOffset); //add rax, <field offset>

                //Load the field
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
				mExceptionHandling.addNullCheck(functionData);

                //Store the field
                if (!is8bits) {
                    Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, fieldOffset, Registers::DX, is32bits); //mov [rax+<fieldOffset>], r/edx
                } else {
                    pushArray(generatedCode, { 0x88, 0x50, (unsigned char)fieldOffset }); //mov [rax+<fieldOffset>], dl
                }
            }
        }
        break;
    case OpCodes::LOAD_STRING:
        {
            if (!vmState.disableGC) {
                generateGCCall(generatedCode, function, instIndex, true);
            }

            //The pointer to the string as the first arg
            Amd64Backend::moveLongToReg(generatedCode, Registers::DI, (long)inst.strValue.data()); //mov rdi, <addr of string>

            //The length of the string as the second arg
            Amd64Backend::moveIntToReg(generatedCode, Registers::SI, inst.strValue.length()); //mov rsi, <string length>

            //Call the newString runtime function
            Amd64Backend::pushReg(generatedCode, Registers::BP);
            generateCall(generatedCode, (long)&Runtime::newString);
            Amd64Backend::popReg(generatedCode, Registers::BP);

            //Push the returned pointer
            Amd64Backend::pushReg(generatedCode, Registers::AX);
        }
        break;
    }
}
