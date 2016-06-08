#include "codegenerator.h"
#include "../type/type.h"
#include "../vmstate.h"
#include "../runtime/runtime.h"
#include "../core/instruction.h"
#include "exceptions.h"
#include "../stackjit.h"
#include "../helpers.h"
#include "callingconvention.h"
#include "../core/functionsignature.h"
#include "amd64assembler.h"
#include <string.h>
#include <iostream>

MacroFunctionContext::MacroFunctionContext(
	const VMState& vmState,
	const CallingConvention& callingConvention,
	const ExceptionHandling& exceptionHandling,
	FunctionCompilationData& functionData,
	const Instruction& inst,
	const int instIndex)
	: vmState(vmState),
	  callingConvention(callingConvention),
	  exceptionHandling(exceptionHandling),
	  functionData(functionData),
	  inst(inst),
	  instIndex(instIndex) {

}

CodeGenerator::CodeGenerator(const CallingConvention& callingConvention, const ExceptionHandling& exceptionHandling)
	: mCallingConvention(callingConvention), mExceptionHandling(exceptionHandling) {

}

void CodeGenerator::defineMacro(const FunctionDefinition& function, MacroFunction macroFunction) {
	mMacros.insert({ FunctionSignature::from(function).str(), macroFunction });
}

bool CodeGenerator::compileAtRuntime(const VMState& vmState,
									 const FunctionDefinition& funcToCall,
									 std::string funcSignature) {
	return vmState.lazyJIT
		   && funcToCall.isManaged()
		   && !vmState.engine().jitCompiler().hasCompiled(funcSignature);
}

std::size_t CodeGenerator::generateCompileCall(CodeGen& generatedCode,
											   ManagedFunction& function,
											   const FunctionDefinition& funcToCall) {
	Amd64Assembler assembler(generatedCode);
#if defined(_WIN64) || defined(__MINGW32__)
	char shadowStackSize = (char)mCallingConvention.calculateShadowStackSize();
	std::size_t callIndex;
	std::size_t checkEndIndex;

	assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)&function); //The current function
	assembler.moveInt(RegisterCallArguments::Arg1, 0); //Offset of the call
	callIndex = generatedCode.size() - sizeof(int);
	assembler.moveInt(RegisterCallArguments::Arg2, (int)generatedCode.size()); //The offset for this check
	assembler.moveInt(RegisterCallArguments::Arg3, 0); //The end of the this check
	checkEndIndex = generatedCode.size() - sizeof(int);

	//The function to compile
	assembler.sub(Registers::SP, 8); //Alignment
	assembler.moveLong(ExtendedRegisters::R10, (PtrValue)(&funcToCall));
	assembler.push(ExtendedRegisters::R10);
	assembler.sub(Registers::SP, shadowStackSize); //Shadow space

	assembler.moveLong(Registers::AX, (PtrValue)&Runtime::compileFunction);
	Amd64Backend::callInReg(generatedCode, Registers::AX);
	assembler.add(Registers::SP, 16 + shadowStackSize); //Used stack

	Helpers::setValue(generatedCode, checkEndIndex, (int)generatedCode.size());
	return callIndex;
#else
	std::size_t callIndex;
	std::size_t checkEndIndex;

	assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)&function);  //The current function
	assembler.moveInt(RegisterCallArguments::Arg1, 0); //Offset of the call
	callIndex = generatedCode.size() - sizeof(int);
	assembler.moveInt(RegisterCallArguments::Arg2, (int)generatedCode.size()); //The offset for this check
	assembler.moveInt(RegisterCallArguments::Arg3, 0); //The end of the this check
	checkEndIndex = generatedCode.size() - sizeof(int);
	assembler.moveLong(RegisterCallArguments::Arg4,	(PtrValue)(&funcToCall)); //The function to compile

	assembler.moveLong(Registers::AX, (PtrValue)&Runtime::compileFunction);
	Amd64Backend::callInReg(generatedCode, Registers::AX);

	Helpers::setValue(generatedCode, checkEndIndex, (int)generatedCode.size());
	return callIndex;
#endif
}

void CodeGenerator::generateCall(CodeGen& generatedCode, unsigned char* funcPtr, Registers addrReg, bool shadowSpaceNeeded) {
	Amd64Assembler assembler(generatedCode);

	if (shadowSpaceNeeded) {
		assembler.sub(Registers::SP, mCallingConvention.calculateShadowStackSize());
	}

	assembler.moveLong(addrReg, (PtrValue)funcPtr);
	Amd64Backend::callInReg(generatedCode, addrReg);

	if (shadowSpaceNeeded) {
		assembler.add(Registers::SP, mCallingConvention.calculateShadowStackSize());
	}
}

void CodeGenerator::generateGCCall(CodeGen& generatedCode, ManagedFunction& function, int instIndex) {
	Amd64Assembler assembler(generatedCode);
	assembler.move(RegisterCallArguments::Arg0, Registers::BP); //BP as the first argument
	assembler.moveLong(RegisterCallArguments::Arg1,	(PtrValue)&function); //Address of the function as second argument
	assembler.moveInt(RegisterCallArguments::Arg2, instIndex); //Current inst index as third argument
	generateCall(generatedCode, (unsigned char*)&Runtime::garbageCollect);
}

void CodeGenerator::initializeFunction(FunctionCompilationData& functionData) {
	auto& function = functionData.function;
	Amd64Assembler assembler(functionData.function.generatedCode());

	//Calculate the size of the stack aligned to 16 bytes
	std::size_t neededStackSize = (function.def().numParams() + function.numLocals() + function.operandStackSize())
								  * Amd64Backend::REG_SIZE;
	std::size_t stackSize = ((neededStackSize + 15) / 16) * 16;

	//Save the base pointer
	assembler.push(Registers::BP);
	assembler.move(Registers::BP, Registers::SP);

	//Make room for the variables on the stack
	if (stackSize > 0) {
		assembler.sub(Registers::SP, (int)stackSize);
	}

	mCallingConvention.moveArgsToStack(functionData);
	zeroLocals(functionData);
}

void CodeGenerator::zeroLocals(FunctionCompilationData& functionData) {
	auto& function = functionData.function;
	Amd64Assembler assembler(functionData.function.generatedCode());

	//Zero the locals
	if (function.numLocals() > 0) {
		//Zero rax
		assembler.bitwiseXor(Registers::AX, Registers::AX); //xor rax, rax

		for (int i = 0; i < function.numLocals(); i++) {
			int localOffset = (int)((i + function.def().numParams() + 1) * -Amd64Backend::REG_SIZE);
			assembler.move({ Registers::BP, localOffset }, Registers::AX); //mov [rbp-local], rax
		}
	}
}

void CodeGenerator::pushFunc(const VMState& vmState, FunctionCompilationData& functionData, int instIndex) {
	auto& generatedCode = functionData.function.generatedCode();
	auto& function = functionData.function;
	Amd64Assembler assembler(generatedCode);

	//Get the top pointer
	auto topPtr = (unsigned char*)vmState.engine().callStack().topPtr();
	assembler.move(Registers::AX, topPtr); //mov rax, [<address of top>]
	assembler.add(Registers::AX, sizeof(CallStackEntry)); //add rax, <sizeof(CallStackEntry)>

	//Check if overflow
	mExceptionHandling.addStackOverflowCheck(
		functionData,
		(PtrValue)(vmState.engine().callStack().start() + vmState.engine().callStack().size()));

	//Store the entry
	assembler.moveLong(Registers::CX, (PtrValue)&function); //mov rcx, <address of func>
	assembler.move({ Registers::AX, 0 }, Registers::CX); //mov [rax], rcx
	assembler.moveInt(Registers::CX, instIndex); //mov rcx, <call point>
	assembler.move({ Registers::AX, sizeof(ManagedFunction*) }, Registers::CX); //mov [rax+<offset>], rcx

	//Update the top pointer
	assembler.move(topPtr, Registers::AX); //mov [<address of top>], rax
}

void CodeGenerator::popFunc(const VMState& vmState, CodeGen& generatedCode) {
	Amd64Assembler assembler(generatedCode);

	//Get the top pointer
	auto topPtr = (unsigned char*)vmState.engine().callStack().topPtr();
	assembler.move(Registers::AX, topPtr); //mov rax, [<address of top>]
	assembler.add(Registers::AX, -(int)sizeof(CallStackEntry)); //add rax, -<sizeof(CallStackEntry)>

	//Update the top pointer
	assembler.move(topPtr, Registers::AX); //mov [<address of top>], rax
}

void CodeGenerator::generateInstruction(FunctionCompilationData& functionData, const VMState& vmState,
										const Instruction& inst, int instIndex) {
	auto& function = functionData.function;
	auto& operandStack = functionData.operandStack;
	auto& generatedCode = function.generatedCode();
	Amd64Assembler assembler(generatedCode);
	int stackOffset = 1; //The offset for variables allocated on the stack

	//Make the mapping
	functionData.instructionNumMapping.push_back((int)generatedCode.size());

	switch (inst.opCode()) {
		case OpCodes::NOP:
			generatedCode.push_back(0x90); //nop
			break;
		case OpCodes::POP:
			operandStack.popReg(Registers::AX);
			break;
		case OpCodes::DUPLICATE:
			operandStack.duplicate();
			break;
		case OpCodes::LOAD_INT:
			operandStack.pushInt(inst.intValue);
			break;
		case OpCodes::LOAD_FLOAT: {
			//Extract the byte pattern for the float
			const int* floatData = reinterpret_cast<const int*>(&inst.floatValue);
			operandStack.pushInt(*floatData);
			break;
		}
		case OpCodes::LOAD_CHAR:
			operandStack.pushInt(inst.charValue);
			break;
		case OpCodes::ADD:
		case OpCodes::SUB:
		case OpCodes::MUL:
		case OpCodes::DIV: {
			auto opType = inst.operandTypes()[0];
			bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
			bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
			bool is32bits = true;

			//Pop 2 operands
			if (intOp) {
				operandStack.popReg(Registers::CX);
				operandStack.popReg(Registers::AX);
			} else if (floatOp) {
				operandStack.popReg(FloatRegisters::XMM0);
				operandStack.popReg(FloatRegisters::XMM1);
			}

			//Apply the operator
			switch (inst.opCode()) {
				case OpCodes::ADD:
					if (intOp) {
						assembler.add(Registers::AX, Registers::CX, is32bits); //add eax, ecx
					} else if (floatOp) {
						assembler.add(FloatRegisters::XMM0, FloatRegisters::XMM1); //addss xmm0, xmm1
					}
					break;
				case OpCodes::SUB:
					if (intOp) {
						assembler.sub(Registers::AX, Registers::CX, is32bits); //sub eax, ecx
					} else if (floatOp) {
						assembler.sub(FloatRegisters::XMM0, FloatRegisters::XMM1); //subss xmm0, xmm1
					}
					break;
				case OpCodes::MUL:
					if (intOp) {
						assembler.mult(Registers::AX, Registers::CX, is32bits); //imul eax, ecx
					} else if (floatOp) {
						assembler.mult(FloatRegisters::XMM0, FloatRegisters::XMM1); //mulss xmm0, xmm1
					}
					break;
				case OpCodes::DIV:
					if (intOp) {
						assembler.signExtend(Registers::AX, DataSize::Size32); //cdq
						assembler.div(Registers::CX, is32bits); //idiv eax, ecx
					} else if (floatOp) {
						assembler.div(FloatRegisters::XMM0, FloatRegisters::XMM1); //divss xmm0, xmm1
					}
					break;
				default:
					break;
			}

			//Push the result
			if (intOp) {
				operandStack.pushReg(Registers::AX);
			} else if (floatOp) {
				operandStack.pushReg( FloatRegisters::XMM0);
			}
			break;
		}
		case OpCodes::LOAD_TRUE:
			operandStack.pushInt(1);
			break;
		case OpCodes::LOAD_FALSE:
			operandStack.pushInt(0);
			break;
		case OpCodes::AND:
		case OpCodes::OR: {
			//Pop 2 operands
			operandStack.popReg(Registers::CX);
			operandStack.popReg(Registers::AX);
			bool is32bits = false;

			//Apply the operator
			switch (inst.opCode()) {
				case OpCodes::AND:
					assembler.bitwiseAnd(Registers::AX, Registers::CX, is32bits); //and rax, rcx
					break;
				case OpCodes::OR:
					assembler.bitwiseOr(Registers::AX, Registers::CX, is32bits); //or rax, rcx
					break;
				default:
					break;
			}

			//Push the result
			operandStack.pushReg(Registers::AX);
			break;
		}
		case OpCodes::NOT:
			operandStack.popReg(Registers::AX);
			assembler.bitwiseNor(Registers::AX);
			Helpers::pushArray(generatedCode, { 0x48, 0x83, 0xE0, 0x01 }); //Skip all the other bits.
			operandStack.pushReg(Registers::AX);
			break;
		case OpCodes::CONVERT_INT_TO_FLOAT:
			operandStack.popReg(Registers::AX);
			assembler.convert(FloatRegisters::XMM0, Registers::AX); //cvtsi2ss xmm0, rax
			operandStack.pushReg(FloatRegisters::XMM0);
			break;
		case OpCodes::CONVERT_FLOAT_TO_INT:
			operandStack.popReg(FloatRegisters::XMM0);
			assembler.convert(Registers::AX, FloatRegisters::XMM0); //cvttss2si rax, xmm0
			operandStack.pushReg(Registers::AX);
			break;
		case OpCodes::COMPARE_EQUAL:
		case OpCodes::COMPARE_NOT_EQUAL:
		case OpCodes::COMPARE_GREATER_THAN:
		case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
		case OpCodes::COMPARE_LESS_THAN:
		case OpCodes::COMPARE_LESS_THAN_OR_EQUAL: {
			auto opType = inst.operandTypes()[0];
			bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
			bool intBasedType = !floatOp;
			bool unsignedComparison = false;

			//Compare
			if (intBasedType) {
				operandStack.popReg(Registers::CX);
				operandStack.popReg(Registers::AX);
				assembler.compare(Registers::AX, Registers::CX); //cmp rax, rcx
			} else if (floatOp) {
				operandStack.popReg(FloatRegisters::XMM1);
				operandStack.popReg(FloatRegisters::XMM0);
				assembler.compare(FloatRegisters::XMM0, FloatRegisters::XMM1); //ucomiss xmm0, xmm1
				unsignedComparison = true;
			}

			//Jump
			std::size_t compareJump = generatedCode.size();
			std::size_t jump = 0;
			std::size_t trueBranchStart = 0;
			std::size_t falseBranchStart = 0;

			int target = 0;
			JumpCondition condition = JumpCondition::Always;
			switch (inst.opCode()) {
				case OpCodes::COMPARE_EQUAL:
					condition = JumpCondition::Equal;
					break;
				case OpCodes::COMPARE_NOT_EQUAL:
					condition = JumpCondition::NotEqual;
					break;
				case OpCodes::COMPARE_GREATER_THAN:
					condition = JumpCondition::GreaterThan;
					break;
				case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
					condition = JumpCondition::GreaterThanOrEqual;
					break;
				case OpCodes::COMPARE_LESS_THAN:
					condition = JumpCondition::LessThan;
					break;
				case OpCodes::COMPARE_LESS_THAN_OR_EQUAL:
					condition = JumpCondition::LessThanOrEqual;
					break;
				default:
					break;
			}

			assembler.jump(condition, target, unsignedComparison);

			//Both branches will have the same operand entry, reserve space
			operandStack.reserveSpace();

			//False branch
			falseBranchStart = generatedCode.size();
			operandStack.pushInt(0, false);
			jump = generatedCode.size();
			Amd64Backend::jump(generatedCode, 0);

			//True branch
			trueBranchStart = generatedCode.size();
			operandStack.pushInt(1, false);

			//Set the jump targets
			Helpers::setValue(generatedCode, jump + 1, (int)(generatedCode.size() - trueBranchStart));
			Helpers::setValue(generatedCode, compareJump + 2, (int)(trueBranchStart - falseBranchStart));
			break;
		}
		case OpCodes::LOAD_LOCAL: {
			//Load rax with the local
			int localOffset = (stackOffset + inst.intValue + (int)function.def().numParams())
							  * -Amd64Backend::REG_SIZE;

			assembler.move(Registers::AX, { Registers::BP, localOffset }); //mov rax, [rbp+<local offset>],

			//Push the loaded value
			operandStack.pushReg(Registers::AX);
			break;
		}
		case OpCodes::STORE_LOCAL: {
			operandStack.popReg(Registers::AX);

			int localOffset = (stackOffset + inst.intValue + (int)function.def().numParams())
							  * -Amd64Backend::REG_SIZE;

			//Store the operand at the given local
			assembler.move({ Registers::BP, localOffset }, Registers::AX); //mov [rbp+<local offset>], rax
			break;
		}
		case OpCodes::CALL:
		case OpCodes::CALL_INSTANCE: {
			std::string calledSignature = "";

			if (inst.opCode() == OpCodes::CALL_INSTANCE) {
				calledSignature = FunctionSignature::memberFunction(
					inst.classType,
					inst.strValue,
					inst.parameters).str();
			} else {
				calledSignature = FunctionSignature::function(inst.strValue, inst.parameters).str();
			}

			const auto& funcToCall = vmState.binder().getFunction(calledSignature);

			if (mMacros.count(calledSignature) == 0) {
				bool needsToCompile = compileAtRuntime(vmState, funcToCall, calledSignature);
				std::size_t callIndex = 0;

				//Check if the called function needs to be compiled compiled
				if (needsToCompile) {
					callIndex = generateCompileCall(generatedCode, function, funcToCall);
				}

				//Push the call
				pushFunc(vmState, functionData, instIndex);

				//Get the address of the function to call
				unsigned char* funcAddress = nullptr;

				//Align the stack
				int stackAlignment = mCallingConvention.calculateStackAlignment(functionData, funcToCall);

				if (stackAlignment > 0) {
					assembler.add(Registers::SP, -stackAlignment);
				}

				//Set the function arguments
				mCallingConvention.callFunctionArguments(functionData, funcToCall);

				//Shadow stack size may be needed
				int shadowStack = mCallingConvention.calculateShadowStackSize();
				if (shadowStack > 0) {
					assembler.sub(Registers::SP, shadowStack);
				}

				if (inst.opCode() == OpCodes::CALL_INSTANCE) {
					mExceptionHandling.addNullCheck(functionData, RegisterCallArguments::Arg0);
				}

				if (funcToCall.isManaged()) {
					if (!needsToCompile) {
						//Mark that the function call needs to be patched with the entry point later
						functionData.unresolvedCalls.push_back(
							UnresolvedFunctionCall(
								FunctionCallType::Relative,
								generatedCode.size(),
								funcToCall));
					} else {
						Helpers::setValue(generatedCode, callIndex, (int)generatedCode.size());
					}

					//Make the call
					Amd64Backend::call(generatedCode, 0);
				} else {
					//Unmanaged functions are located beyond one int, direct addressing must be used.
					//Check if the function entry point is defined yet
					if (funcToCall.entryPoint() != 0) {
						funcAddress = funcToCall.entryPoint();
					} else {
						//Mark that the function call needs to be patched with the entry point later
						functionData.unresolvedCalls.push_back(
							UnresolvedFunctionCall(
								FunctionCallType::Absolute,
								generatedCode.size(),
								funcToCall));
					}

					//Make the call
					generateCall(generatedCode, funcAddress, Registers::AX, false);
				}

				//Unalign the stack
				if (stackAlignment + shadowStack > 0) {
					assembler.add(Registers::SP, stackAlignment + shadowStack);
				}

				//Push the result
				mCallingConvention.handleReturnValue(functionData, funcToCall);

				//Pop the call
				popFunc(vmState, generatedCode);
			} else {
				//Invoke the macro function
				mMacros[calledSignature]({
					vmState,
					mCallingConvention,
					mExceptionHandling,
					functionData,
					inst,
					instIndex
				});
			}

			break;
		}
		case OpCodes::RET: {
			//If debug is enabled, print the stack frame before return
			if (vmState.enableDebug && vmState.printStackFrame) {
				assembler.move(RegisterCallArguments::Arg0, Registers::BP);
				assembler.moveLong(RegisterCallArguments::Arg1, (PtrValue)&function);
				generateCall(generatedCode, (unsigned char*)&Runtime::printStackFrame);
			}

			mCallingConvention.makeReturnValue(functionData);

			//Restore the base pointer
			assembler.move(Registers::SP, Registers::BP); //mov rsp, rbp
			assembler.pop(Registers::BP); //pop rbp

			//Make the return
			Amd64Backend::ret(generatedCode);
			break;
		}
		case OpCodes::LOAD_ARG: {
			//Load rax with the argument
			int argOffset = (inst.intValue + stackOffset) * -Amd64Backend::REG_SIZE;
			assembler.move(Registers::AX, { Registers::BP, argOffset }); //mov rax [rbp+<arg offset>]

			//Push the loaded value
			operandStack.pushReg(Registers::AX);
			break;
		}
		case OpCodes::BRANCH: {
			Amd64Backend::jump(generatedCode, 0); //jmp <target>

			//As the exact target in native instructions isn't known, defer to later.
			functionData.unresolvedBranches.insert({
				generatedCode.size() - 5,
				BranchTarget((unsigned int)inst.intValue, 5)
			 });
			break;
		}
		case OpCodes::BRANCH_EQUAL:
		case OpCodes::BRANCH_NOT_EQUAL:
		case OpCodes::BRANCH_GREATER_THAN:
		case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
		case OpCodes::BRANCH_LESS_THAN:
		case OpCodes::BRANCH_LESS_THAN_OR_EQUAL: {
			auto opType = inst.operandTypes()[0];
			bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
			bool intBasedType = !floatOp;
			bool unsignedComparison = false;

			//Compare
			if (intBasedType) {
				operandStack.popReg(Registers::CX);
				operandStack.popReg(Registers::AX);
				assembler.compare(Registers::AX, Registers::CX); //cmp rax, rcx
			} else if (floatOp) {
				operandStack.popReg(FloatRegisters::XMM1);
				operandStack.popReg(FloatRegisters::XMM0);
				assembler.compare(FloatRegisters::XMM0, FloatRegisters::XMM1); //ucomiss xmm0, xmm1
				unsignedComparison = true;
			}

			JumpCondition condition = JumpCondition::Always;
			switch (inst.opCode()) {
				case OpCodes::BRANCH_EQUAL:
					condition = JumpCondition::Equal;
					break;
				case OpCodes::BRANCH_NOT_EQUAL:
					condition = JumpCondition::NotEqual;
					break;
				case OpCodes::BRANCH_GREATER_THAN:
					condition = JumpCondition::GreaterThan;
					break;
				case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
					condition = JumpCondition::GreaterThanOrEqual;
					break;
				case OpCodes::BRANCH_LESS_THAN:
					condition = JumpCondition::LessThan;
					break;
				case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
					condition = JumpCondition::LessThanOrEqual;
					break;
				default:
					break;
			}

			assembler.jump(condition, 0, unsignedComparison);

			//As the exact target in native instructions isn't known, defer to later.
			functionData.unresolvedBranches.insert({
				generatedCode.size() - 6,
				BranchTarget((unsigned int)inst.intValue, 6)
			});
			break;
		}
		case OpCodes::LOAD_NULL:
			operandStack.pushInt(0);
			break;
		case OpCodes::NEW_ARRAY: {
			auto elemType = vmState.typeProvider().getType(inst.strValue);
			auto arrayType = static_cast<const ArrayType*>(
					vmState.typeProvider().getType(TypeSystem::arrayTypeName(elemType)));

			if (!vmState.disableGC) {
				generateGCCall(generatedCode, function, instIndex);
			}

			//The pointer to the type as the first arg
			assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)arrayType);

			//Pop the size as the second arg
			operandStack.popReg(RegisterCallArguments::Arg1);

			//Check that the size >= 0
			mExceptionHandling.addArrayCreationCheck(functionData);

			//Call the newArray runtime function
			generateCall(generatedCode, (unsigned char*)&Runtime::newArray);

			//Push the returned pointer
			operandStack.pushReg(Registers::AX);
			break;
		}
		case OpCodes::STORE_ELEMENT: {
			auto elemType = vmState.typeProvider().getType(inst.strValue);

			//Pop the operands
			operandStack.popReg(Registers::DX); //The value to store
			operandStack.popReg(ExtendedRegisters::R10); //The index of the element
			operandStack.popReg( Registers::AX); //The address of the array

			//Error checks
			mExceptionHandling.addNullCheck(functionData);
			mExceptionHandling.addArrayBoundsCheck(functionData);

			//Compute the address of the element
			assembler.mult(ExtendedRegisters::R10, (int)TypeSystem::sizeOfType(elemType)); //imul r10, <size of type>
			assembler.add(Registers::AX, ExtendedRegisters::R10); //add rax, r10

			//Store the element
			auto elemSize = TypeSystem::sizeOfType(elemType);
			bool is32bits = elemSize == 4;
			bool is8bits = elemSize == 1;

			if (!is8bits) {
				Amd64Backend::moveRegToMemoryRegWithCharOffset(
					generatedCode,
					Registers::AX, StackJIT::ARRAY_LENGTH_SIZE, Registers::DX,
					is32bits); //mov [rax+<element offset>], r/edx
			} else {
				Helpers::pushArray(generatedCode,
						  { 0x88, 0x50, (unsigned char)StackJIT::ARRAY_LENGTH_SIZE }); //mov [rax+<element offset>], dl
			}

			break;
		}
		case OpCodes::LOAD_ELEMENT: {
			auto elemType = vmState.typeProvider().getType(inst.strValue);

			//Pop the operands
			operandStack.popReg(ExtendedRegisters::R10); //The index of the element
			operandStack.popReg(Registers::AX); //The address of the ar

			//Error checks
			mExceptionHandling.addNullCheck(functionData);
			mExceptionHandling.addArrayBoundsCheck(functionData);

			//Compute the address of the element
			assembler.mult(ExtendedRegisters::R10, (int)TypeSystem::sizeOfType(elemType)); //imul r10, <size of type>
			assembler.add(Registers::AX, ExtendedRegisters::R10); //add rax, r10
			assembler.add(Registers::AX, StackJIT::ARRAY_LENGTH_SIZE); //add rax, <element offset>

			//Load the element
			auto elemSize = TypeSystem::sizeOfType(elemType);
			bool is32bits = elemSize == 4;
			bool is8bits = elemSize == 1;

			if (!is8bits) {
				Amd64Backend::moveMemoryByRegToReg(
					generatedCode,
					Registers::CX,
					Registers::AX,
					is32bits); //mov r/ecx, [rax]
			} else {
				Helpers::pushArray(generatedCode, {0x8A, 0x08}); //mov cl, [rax]
			}

			operandStack.pushReg(Registers::CX);
			break;
		}
		case OpCodes::LOAD_ARRAY_LENGTH:
			//Pop the array ref
			operandStack.popReg( Registers::AX);

			//Null check
			mExceptionHandling.addNullCheck(functionData);

			//Get the size of the array (an int)
			Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX, true); //mov eax, [rax]

			//Push the size
			operandStack.pushReg(Registers::AX);
			break;
		case OpCodes::NEW_OBJECT: {
			auto classType = inst.classType;

			//Call the garbageCollect runtime function
			if (!vmState.disableGC) {
				generateGCCall(generatedCode, function, instIndex);
			}

			//Push the call
			pushFunc(vmState, functionData, instIndex);

			//Call the constructor
			auto calledSignature = FunctionSignature::memberFunction(
				inst.classType,
				inst.strValue,
				inst.parameters).str();

			const auto& funcToCall = vmState.binder().getFunction(calledSignature);

			//Check if the constructor needs to be compiled
			bool needsToCompile = compileAtRuntime(vmState, funcToCall, calledSignature);
			std::size_t callIndex = 0;

			//Check if the called function needs to be compiled compiled
			if (needsToCompile) {
				callIndex = generateCompileCall(generatedCode, function, funcToCall);
			}

			//Call the newObject runtime function
			assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)classType); //The pointer to the type
			generateCall(generatedCode, (unsigned char*)&Runtime::newObject);

			//Save the reference
			assembler.move(ExtendedRegisters::R10, Registers::AX);

			int numArgs = (int)funcToCall.parameters().size() - 1;

			//Align the stack
			int stackAlignment = mCallingConvention.calculateStackAlignment(functionData, funcToCall);

			if (stackAlignment > 0) {
				assembler.add(Registers::SP, -stackAlignment);
			}

			//Set the constructor arguments
			assembler.move(RegisterCallArguments::Arg0, Registers::AX);

			for (int i = numArgs - 1; i >= 0; i--) {
				mCallingConvention.callFunctionArgument(
					functionData,
					i + 1,
					inst.parameters.at((std::size_t)i),
					funcToCall);
			}

			//Push the reference to the created object
			assembler.move(Registers::AX, ExtendedRegisters::R10);
			operandStack.pushReg(Registers::AX);

			//Shadow stack may be needed
			int shadowStack = mCallingConvention.calculateShadowStackSize();
			if (shadowStack > 0) {
				assembler.sub(Registers::SP, shadowStack);
			}

			if (!needsToCompile) {
				//Mark that the constructor needs to be patched with the entry point later
				functionData.unresolvedCalls.push_back(
					UnresolvedFunctionCall(
						FunctionCallType::Relative,
						generatedCode.size(),
						funcToCall));
			} else {
				Helpers::setValue(generatedCode, callIndex, (int)generatedCode.size());
			}

			//Call the constructor
			Amd64Backend::call(generatedCode, 0);

			//Unalign the stack
			if (stackAlignment + shadowStack > 0) {
				assembler.add(Registers::SP, stackAlignment + shadowStack);
			}

			//This is for clean up after a call, as the constructor returns nothing.
			mCallingConvention.handleReturnValue(functionData, funcToCall);

			//Pop the call
			popFunc(vmState, generatedCode);
			break;
		}
		case OpCodes::LOAD_FIELD:
		case OpCodes::STORE_FIELD: {
			//Get the field
			std::string className;
			std::string fieldName;
			TypeSystem::getClassAndFieldName(inst.strValue, className, fieldName);

			auto classMetadata = vmState.classProvider().getMetadata(className);
			auto& field = classMetadata.fields().at(fieldName);
			int fieldOffset = (int)field.offset();

			//Get the size of the field
			auto elemSize = TypeSystem::sizeOfType(field.type());
			bool is32bits = elemSize == 4;
			bool is8bits = elemSize == 1;

			if (inst.opCode() == OpCodes::LOAD_FIELD) {
				//Pop the operand
				operandStack.popReg(Registers::AX); //The address of the object

				//Null check
				mExceptionHandling.addNullCheck(functionData);

				//Compute the address of the field
				assembler.add(Registers::AX, fieldOffset); //add rax, <field offset>

				//Load the field
				if (!is8bits) {
					Amd64Backend::moveMemoryByRegToReg(
						generatedCode,
						Registers::CX,
						Registers::AX,
						is32bits); //mov r/ecx, [rax]
				} else {
					Helpers::pushArray(generatedCode, { 0x8A, 0x08 }); //mov cl, [rax]
				}

				operandStack.pushReg(Registers::CX);
			} else {
				//Pop the operand
				operandStack.popReg(Registers::DX); //The value to store
				operandStack.popReg(Registers::AX); //The address of the object

				//Null check
				mExceptionHandling.addNullCheck(functionData);

				//Store the field
				if (Helpers::validCharValue(fieldOffset)) {
					if (!is8bits) {
						Amd64Backend::moveRegToMemoryRegWithCharOffset(
							generatedCode,
							Registers::AX, (char)fieldOffset, Registers::DX, is32bits); //mov [rax+<fieldOffset>], r/edx
					} else {
						Helpers::pushArray(
							generatedCode,
							{0x88, 0x50, (unsigned char)fieldOffset}); //mov [rax+<fieldOffset>], dl
					}
				} else {
					//Compute the address of the field
					assembler.add(Registers::AX, fieldOffset); //add rax, <field offset>

					if (!is8bits) {
						Amd64Backend::moveRegToMemoryRegWithCharOffset(
							generatedCode,
							Registers::AX, 0, Registers::DX, is32bits); //mov [rax], r/edx
					} else {
						Helpers::pushArray(generatedCode, {0x88, 0x50, 0}); //mov [rax], dl
					}
				}
			}
			break;
		}
		case OpCodes::LOAD_STRING: {
			if (!vmState.disableGC) {
				generateGCCall(generatedCode, function, instIndex);
			}

			//The pointer to the string as the first arg
			assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)inst.strValue.data()); //mov <arg 0>, <addr of string>

			//The length of the string as the second arg
			assembler.moveInt(RegisterCallArguments::Arg1, (int)inst.strValue.length()); //mov <arg 1>, <string length>>

			//Call the newString runtime function
			generateCall(generatedCode, (unsigned char*)&Runtime::newString);

			//Push the returned pointer
			operandStack.pushReg(Registers::AX);
			break;
		}
	}
}
