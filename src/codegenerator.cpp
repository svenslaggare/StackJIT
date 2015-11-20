#include "codegenerator.h"
#include "verifier.h"
#include "type.h"
#include "vmstate.h"
#include "rtlibrary.h"
#include "function.h"
#include "instructions.h"
#include "exceptions.h"
#include "stackjit.h"
#include "helpers.h"
#include "callingconvention.h"
#include "functionsignature.h"
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

namespace {
	void pushArray(std::vector<unsigned char>& dest, const std::vector<unsigned char>& values) {
		for (auto current : values) {
			dest.push_back(current);
		}
	}

	//Returns the offset for a stack operand
	int getStackOperandOffset(ManagedFunction& function, int operandStackIndex) {
		return -(int)(Amd64Backend::REG_SIZE *
					  (1 + function.numLocals() + function.def().numParams() + operandStackIndex));
	}

	//Indicates if the given value fits in a char
	bool validCharValue(int value) {
		return value >= -128 && value < 128;
	}
}

void OperandStack::duplicate(ManagedFunction& function, int operandStackIndex) {
	int stackOffset1 = getStackOperandOffset(function, operandStackIndex);
	int stackOffset2 = getStackOperandOffset(function, operandStackIndex + 1);

	Amd64Backend::moveMemoryRegWithOffsetToReg(
		function.generatedCode(),
		Registers::AX, Registers::BP, stackOffset1); //mov rax, [rbp+<operand1 offset>]

	Amd64Backend::moveRegToMemoryRegWithOffset(
		function.generatedCode(),
		Registers::BP, stackOffset2, Registers::AX); //mov [rbp+<operand2 offset>], rax
}

void OperandStack::popReg(ManagedFunction& function, int operandStackIndex, Registers reg) {
	int stackOffset = getStackOperandOffset(function, operandStackIndex);

	Amd64Backend::moveMemoryRegWithOffsetToReg(
		function.generatedCode(),
		reg, Registers::BP, stackOffset); //mov <reg>, [rbp+<operand offset>]
}

void OperandStack::popReg(ManagedFunction& function, int operandStackIndex, NumberedRegisters reg) {
	int stackOffset = getStackOperandOffset(function, operandStackIndex);

	if (validCharValue(stackOffset)) {
		pushArray(
			function.generatedCode(),
			{0x4C, 0x8B, (unsigned char)(0x45 | (reg << 3)),
			 (unsigned char)stackOffset}); //mov <reg>, [rbp+<operand offset>]
	} else {
		pushArray(
			function.generatedCode(),
			{0x4C, 0x8B, (unsigned char)(0x85 | (reg << 3))});

		IntToBytes converter;
		converter.intValue = stackOffset;

		for (std::size_t i = 0; i < sizeof(int); i++) {
			function.generatedCode().push_back(converter.byteValues[i]);
		}
	}
}

void OperandStack::popReg(ManagedFunction& function, int operandStackIndex, FloatRegisters reg) {
	int stackOffset = getStackOperandOffset(function, operandStackIndex);

	if (validCharValue(stackOffset)) {
		pushArray(
			function.generatedCode(),
			{0xF3, 0x0F, 0x10, (unsigned char)(0x45 | (reg << 3)),
			 (unsigned char)getStackOperandOffset(function, operandStackIndex)}); //movss <reg>, [rbp+<operand offset>]
	} else {
		pushArray(
			function.generatedCode(),
			{0xF3, 0x0F, 0x10, (unsigned char)(0x85 | (reg << 3))});

		IntToBytes converter;
		converter.intValue = stackOffset;

		for (std::size_t i = 0; i < sizeof(int); i++) {
			function.generatedCode().push_back(converter.byteValues[i]);
		}
	}
}

void OperandStack::pushReg(ManagedFunction& function, int operandStackIndex, Registers reg) {
	int stackOffset = getStackOperandOffset(function, operandStackIndex);

	Amd64Backend::moveRegToMemoryRegWithOffset(
		function.generatedCode(),
		Registers::BP, stackOffset, reg); //mov [rbp+<operand offset>], <reg>
}

void OperandStack::pushReg(ManagedFunction& function, int operandStackIndex, FloatRegisters reg) {
	int stackOffset = getStackOperandOffset(function, operandStackIndex);

	Amd64Backend::moveRegToMemoryRegWithOffset(
		function.generatedCode(),
		Registers::BP,
		stackOffset, reg); //movss [rbp+<operand offset>], <float reg>
}

void OperandStack::pushInt(ManagedFunction& function, int operandStackIndex, int value) {
	int stackOffset = getStackOperandOffset(function, operandStackIndex);

	//mov [rbp+<operand offset>], value
	if (validCharValue(stackOffset)) {
		pushArray(
			function.generatedCode(),
			{0x48, 0xC7, 0x45, (unsigned char)stackOffset});
	} else {
		pushArray(
			function.generatedCode(),
			{0x48, 0xC7, 0x85});

		IntToBytes intToBytes;
		intToBytes.intValue = stackOffset;
		for (std::size_t i = 0; i < sizeof(int); i++) {
			function.generatedCode().push_back(intToBytes.byteValues[i]);
		}
	}

	IntToBytes intToBytes;
	intToBytes.intValue = value;
	for (std::size_t i = 0; i < sizeof(int); i++) {
		function.generatedCode().push_back(intToBytes.byteValues[i]);
	}
}

CodeGenerator::CodeGenerator(const CallingConvention& callingConvention, const ExceptionHandling& exceptionHandling)
	: mCallingConvention(callingConvention), mExceptionHandling(exceptionHandling) {

}

void CodeGenerator::defineMacro(const FunctionDefinition& function, MacroFunction macroFunction) {
	mMacros.insert({FunctionSignature::from(function).str(), macroFunction});
}

bool CodeGenerator::compileAtRuntime(const VMState& vmState, const FunctionDefinition& funcToCall,
									 std::string funcSignature) {
	return vmState.lazyJIT
		   && funcToCall.isManaged()
		   && !vmState.engine().jitCompiler().hasCompiled(funcSignature);
}

std::size_t CodeGenerator::generateCompileCall(CodeGen& generatedCode, ManagedFunction& function,
											   const FunctionDefinition& funcToCall) {
#if defined(_WIN64) || defined(__MINGW32__)
	char shadowStackSize = (char)mCallingConvention.calculateShadowStackSize();
	std::size_t callIndex;
	std::size_t checkEndIndex;

	Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0, (PtrValue)&function); //The current function
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg1, 0); //Offset of the call
	callIndex = generatedCode.size() - sizeof(int);
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg2, (int)generatedCode.size()); //The offset for this check
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg3, 0); //The end of the this check
	checkEndIndex = generatedCode.size() - sizeof(int);

	//The function to compile
	Amd64Backend::subByteFromReg(generatedCode, Registers::SP, 8); //Alignment
	Amd64Backend::moveLongToReg(generatedCode, NumberedRegisters::R10, (PtrValue)(&funcToCall));
	Amd64Backend::pushReg(generatedCode, NumberedRegisters::R10);
	Amd64Backend::subByteFromReg(generatedCode, Registers::SP, shadowStackSize); //Shadow space

	Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (PtrValue)&Runtime::compileFunction);
	Amd64Backend::callInReg(generatedCode, Registers::AX);
	Amd64Backend::addByteToReg(generatedCode, Registers::SP, 16 + shadowStackSize); //Used stack

	Helpers::setInt(generatedCode, checkEndIndex, (int)generatedCode.size());

	return callIndex;
#else
	std::size_t callIndex;
	std::size_t checkEndIndex;

	Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0, (PtrValue)&function); //The current function
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg1, 0); //Offset of the call
	callIndex = generatedCode.size() - sizeof(int);
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg2,
							   (int)generatedCode.size()); //The offset for this check
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg3, 0); //The end of the this check
	checkEndIndex = generatedCode.size() - sizeof(int);
	Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg4,
								(PtrValue)(&funcToCall)); //The function to compile

	Amd64Backend::moveLongToReg(generatedCode, Registers::AX, (PtrValue)&Runtime::compileFunction);
	Amd64Backend::callInReg(generatedCode, Registers::AX);

	Helpers::setInt(generatedCode, checkEndIndex, (int)generatedCode.size());

	return callIndex;
#endif
}

void CodeGenerator::generateCall(CodeGen& codeGen, unsigned char* funcPtr, Registers addrReg, bool shadowSpaceNeeded) {
	if (shadowSpaceNeeded) {
		Amd64Backend::subConstantFromReg(codeGen, Registers::SP, mCallingConvention.calculateShadowStackSize());
	}

	Amd64Backend::moveLongToReg(codeGen, addrReg, (PtrValue)funcPtr);
	Amd64Backend::callInReg(codeGen, addrReg);

	if (shadowSpaceNeeded) {
		Amd64Backend::addConstantToReg(codeGen, Registers::SP, mCallingConvention.calculateShadowStackSize());
	}
}

void CodeGenerator::generateGCCall(CodeGen& generatedCode, ManagedFunction& function, int instIndex) {
	Amd64Backend::moveRegToReg(generatedCode, RegisterCallArguments::Arg0, Registers::BP); //BP as the first argument
	Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg1,
								(PtrValue)&function); //Address of the function as second argument
	Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg2,
							   instIndex); //Current inst index as third argument
	generateCall(generatedCode, (unsigned char*)&Runtime::garbageCollect);
}

void CodeGenerator::initializeFunction(FunctionCompilationData& functionData) {
	auto& function = functionData.function;

	//Calculate the size of the stack aligned to 16 bytes
	std::size_t neededStackSize =
		(function.def().numParams() + function.numLocals() + function.operandStackSize()) * Amd64Backend::REG_SIZE;
	std::size_t stackSize = ((neededStackSize + 15) / 16) * 16;

	//Save the base pointer
	Amd64Backend::pushReg(function.generatedCode(), Registers::BP); //push rbp
	Amd64Backend::moveRegToReg(function.generatedCode(), Registers::BP, Registers::SP); //mov rbp, rsp

	if (stackSize > 0) {
		//Make room for the variables on the stack
		if (validCharValue((int)stackSize)) {
			Amd64Backend::subByteFromReg(function.generatedCode(), Registers::SP,
										 (char)stackSize); //sub rsp, <size of stack>
		} else {
			Amd64Backend::subIntFromReg(function.generatedCode(), Registers::SP,
										(int)stackSize); //sub rsp, <size of stack>
		}
	}

	mCallingConvention.moveArgsToStack(functionData);
	zeroLocals(functionData);
}

void CodeGenerator::zeroLocals(FunctionCompilationData& functionData) {
	auto& function = functionData.function;

	//Zero the locals
	if (function.numLocals() > 0) {
		//Zero eax
		Amd64Backend::xorRegToReg(
			function.generatedCode(),
			Registers::AX, Registers::AX); //xor rax, rax

		for (int i = 0; i < function.numLocals(); i++) {
			int localOffset = (int)((i + function.def().numParams() + 1) * -Amd64Backend::REG_SIZE);
			Amd64Backend::moveRegToMemoryRegWithOffset(
				function.generatedCode(),
				Registers::BP, localOffset, Registers::AX); //mov [rbp-local], rax
		}
	}
}

void CodeGenerator::pushFunc(const VMState& vmState, FunctionCompilationData& functionData, int instIndex) {
	auto& generatedCode = functionData.function.generatedCode();
	auto& function = functionData.function;

	//Get the top pointer
	auto topPtr = (unsigned char*)vmState.engine().callStack().topPtr();
	Amd64Backend::moveMemoryToReg(
		generatedCode,
		Registers::AX,
		topPtr); //mov rax, [<address of top>]

	Amd64Backend::addByteToReg(
		generatedCode,
		Registers::AX, sizeof(CallStackEntry)); //add rax, <sizeof(CallStackEntry)>

	//Check if overflow
	mExceptionHandling.addStackOverflowCheck(
		functionData,
		(PtrValue)(vmState.engine().callStack().start() + vmState.engine().callStack().size()));

	//Store the entry
	Amd64Backend::moveLongToReg(generatedCode, Registers::CX, (PtrValue)&function); //mov rcx, <address of func>
	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, 0, Registers::CX); //mov [rax], rcx
	Amd64Backend::moveIntToReg(generatedCode, Registers::CX, instIndex); //mov rcx, <call point>
	Amd64Backend::moveRegToMemoryRegWithOffset(
		generatedCode,
		Registers::AX, sizeof(ManagedFunction*), Registers::CX); //mov [rax+<offset>], rcx

	//Update the top pointer
	Amd64Backend::moveRegToMemory(
		generatedCode,
		topPtr,
		Registers::AX); //mov [<address of top>], rax
}

void CodeGenerator::popFunc(const VMState& vmState, CodeGen& generatedCode) {
	//Get the top pointer
	auto topPtr = (unsigned char*)vmState.engine().callStack().topPtr();
	Amd64Backend::moveMemoryToReg(
		generatedCode,
		Registers::AX,
		topPtr); //mov rax, [<address of top>]

	Amd64Backend::addByteToReg(
		generatedCode,
		Registers::AX, -(int)sizeof(CallStackEntry)); //add rax, -<sizeof(CallStackEntry)>

	//Update the top pointer
	Amd64Backend::moveRegToMemory(
		generatedCode,
		topPtr,
		Registers::AX); //mov [<address of top>], rax
}

void CodeGenerator::generateInstruction(FunctionCompilationData& functionData, const VMState& vmState,
										const Instruction& inst, int instIndex) {
	auto& function = functionData.function;
	auto& generatedCode = function.generatedCode();
	int stackOffset = 1; //The offset for variables allocated on the stack

	//Make the mapping
	functionData.instructionNumMapping.push_back((int)generatedCode.size());

	int topOperandIndex = (int)inst.operandTypes().size() - 1;

	switch (inst.opCode()) {
		case OpCodes::NOP:
			generatedCode.push_back(0x90); //nop
			break;
		case OpCodes::POP:
			OperandStack::popReg(function, topOperandIndex, Registers::AX);
			break;
		case OpCodes::DUPLICATE:
			OperandStack::duplicate(function, topOperandIndex);
			break;
		case OpCodes::LOAD_INT:
			OperandStack::pushInt(function, topOperandIndex + 1, inst.intValue);
			break;
		case OpCodes::LOAD_FLOAT: {
			//Extract the byte pattern for the float
			const int* floatData = reinterpret_cast<const int*>(&inst.floatValue);
			OperandStack::pushInt(function, topOperandIndex + 1, *floatData);
			break;
		}
		case OpCodes::LOAD_CHAR:
			OperandStack::pushInt(function, topOperandIndex + 1, inst.charValue);
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
				OperandStack::popReg(function, topOperandIndex, Registers::CX);
				OperandStack::popReg(function, topOperandIndex - 1, Registers::AX);
			} else if (floatOp) {
				OperandStack::popReg(function, topOperandIndex, FloatRegisters::XMM0);
				OperandStack::popReg(function, topOperandIndex - 1, FloatRegisters::XMM1);
			}

			//Apply the operator
			switch (inst.opCode()) {
				case OpCodes::ADD:
					if (intOp) {
						Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::CX, is32bits); //add eax, ecx
					} else if (floatOp) {
						pushArray(generatedCode, {0xF3, 0x0F, 0x58, 0xC1}); //addss xmm0, xmm1
					}
					break;
				case OpCodes::SUB:
					if (intOp) {
						Amd64Backend::subRegFromReg(
								generatedCode,
								Registers::AX,
								Registers::CX,
								is32bits); //sub eax, ecx
					} else if (floatOp) {
						pushArray(generatedCode, {0xF3, 0x0F, 0x5C, 0xC1}); //subss xmm0, xmm1
					}
					break;
				case OpCodes::MUL:
					if (intOp) {
						Amd64Backend::multRegToReg(
								generatedCode,
								Registers::AX,
								Registers::CX,
								is32bits); //imul eax, ecx
					} else if (floatOp) {
						pushArray(generatedCode, { 0xF3, 0x0F, 0x59, 0xC1 }); //mulss xmm0, xmm1
					}
					break;
				case OpCodes::DIV:
					if (intOp) {
						pushArray(generatedCode, {0x99}); //cdq
						Amd64Backend::divRegFromReg(
								generatedCode,
								Registers::AX,
								Registers::CX,
								is32bits); //idiv eax, ecx
					} else if (floatOp) {
						pushArray(generatedCode, {0xF3, 0x0F, 0x5E, 0xC1}); //divss xmm0, xmm1
					}
					break;
				default:
					break;
			}

			//Push the result
			if (intOp) {
				OperandStack::pushReg(function, topOperandIndex - 1, Registers::AX);
			} else if (floatOp) {
				OperandStack::pushReg(function, topOperandIndex - 1, FloatRegisters::XMM0);
			}
			break;
		}
		case OpCodes::LOAD_TRUE:
			OperandStack::pushInt(function, topOperandIndex + 1, 1);
			break;
		case OpCodes::LOAD_FALSE:
			OperandStack::pushInt(function, topOperandIndex + 1, 0);
			break;
		case OpCodes::AND:
		case OpCodes::OR: {
			//Pop 2 operands
			OperandStack::popReg(function, topOperandIndex, Registers::CX);
			OperandStack::popReg(function, topOperandIndex - 1, Registers::AX);
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
			OperandStack::pushReg(function, topOperandIndex - 1, Registers::AX);
			break;
		}
		case OpCodes::NOT:
			OperandStack::popReg(function, topOperandIndex, Registers::AX);
			Amd64Backend::notReg(generatedCode, Registers::AX); //not rax
			OperandStack::pushReg(function, topOperandIndex, Registers::AX);
			break;
		case OpCodes::CONVERT_INT_TO_FLOAT:
			OperandStack::popReg(function, topOperandIndex, Registers::AX);
			pushArray(generatedCode, {0xF3, 0x48, 0x0F, 0x2A, 0xC0}); //cvtsi2ss xmm0, rax
			OperandStack::pushReg(function, topOperandIndex, FloatRegisters::XMM0);
			break;
		case OpCodes::CONVERT_FLOAT_TO_INT:
			OperandStack::popReg(function, topOperandIndex, FloatRegisters::XMM0);
			pushArray(generatedCode, {0xF3, 0x48, 0x0F, 0x2C, 0xC0}); //cvttss2si rax, xmm0
			OperandStack::pushReg(function, topOperandIndex, Registers::AX);
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
				OperandStack::popReg(function, topOperandIndex, Registers::CX);
				OperandStack::popReg(function, topOperandIndex - 1, Registers::AX);
				Amd64Backend::compareRegToReg(generatedCode, Registers::AX, Registers::CX); //cmp rax, rcx
			} else if (floatOp) {
				OperandStack::popReg(function, topOperandIndex, FloatRegisters::XMM1);
				OperandStack::popReg(function, topOperandIndex - 1, FloatRegisters::XMM0);
				pushArray(generatedCode, {0x0F, 0x2E, 0xC1}); //ucomiss xmm0, xmm1
				unsignedComparison = true;
			}

			//Jump
			std::size_t compareJump = generatedCode.size();
			std::size_t jump = 0;
			std::size_t trueBranchStart = 0;
			std::size_t falseBranchStart = 0;

			int target = 0;

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

			//False branch
			falseBranchStart = generatedCode.size();
			OperandStack::pushInt(function, topOperandIndex - 1, 0);
			jump = generatedCode.size();
			Amd64Backend::jump(generatedCode, 0);

			//True branch
			trueBranchStart = generatedCode.size();
			OperandStack::pushInt(function, topOperandIndex - 1, 1);

			//Set the jump targets
			Helpers::setInt(generatedCode, jump + 1, (int)(generatedCode.size() - trueBranchStart));
			Helpers::setInt(generatedCode, compareJump + 2, (int)(trueBranchStart - falseBranchStart));
			break;
		}
		case OpCodes::LOAD_LOCAL: {
			//Load rax with the local
			int localOffset = (stackOffset + inst.intValue + (int)function.def().numParams())
							  * -Amd64Backend::REG_SIZE;

			Amd64Backend::moveMemoryRegWithOffsetToReg(
				generatedCode,
				Registers::AX,
				Registers::BP, localOffset);

			//Push the loaded value
			OperandStack::pushReg(function, topOperandIndex + 1, Registers::AX);
			break;
		}
		case OpCodes::STORE_LOCAL: {
			OperandStack::popReg(function, topOperandIndex, Registers::AX);

			int localOffset = (stackOffset + inst.intValue + (int)function.def().numParams())
							  * -Amd64Backend::REG_SIZE;

			//Store the operand at the given local
			Amd64Backend::moveRegToMemoryRegWithOffset(
				generatedCode,
				Registers::BP, localOffset, Registers::AX); //mov [rbp+<local offset>], rax
			break;
		}
		case OpCodes::CALL:
		case OpCodes::CALL_INSTANCE: {
			std::string calledSignature = "";

			if (inst.opCode() == OpCodes::CALL_INSTANCE) {
				calledSignature = FunctionSignature::memberFunction(inst.classType, inst.strValue,
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
				unsigned char* funcAddr = nullptr;
				int numArgs = (int)funcToCall.parameters().size();

				//Align the stack
				int stackAlignment = mCallingConvention.calculateStackAlignment(functionData, funcToCall);

				if (stackAlignment > 0) {
					Amd64Backend::addConstantToReg(
						generatedCode,
						Registers::SP,
						-stackAlignment);
				}

				//Set the function arguments
				mCallingConvention.callFunctionArguments(functionData, funcToCall, (int)inst.operandTypes().size());

				//Shadow stack size may be needed
				int shadowStack = mCallingConvention.calculateShadowStackSize();
				if (shadowStack > 0) {
					Amd64Backend::subConstantFromReg(generatedCode, Registers::SP, shadowStack);
				}

				if (inst.opCode() == OpCodes::CALL_INSTANCE) {
					//Null check
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
						Helpers::setInt(generatedCode, callIndex, (int)generatedCode.size());
					}

					//Make the call
					Amd64Backend::call(generatedCode, 0);
				} else {
					//Unmanaged functions are located beyond one int, direct addressing must be used.
					//Check if the function entry point is defined yet
					if (funcToCall.entryPoint() != 0) {
						funcAddr = funcToCall.entryPoint();
					} else {
						//Mark that the function call needs to be patched with the entry point later
						functionData.unresolvedCalls.push_back(
							UnresolvedFunctionCall(
								FunctionCallType::Absolute,
								generatedCode.size(),
								funcToCall));
					}

					//Make the call
					generateCall(generatedCode, funcAddr, Registers::AX, false);
				}

				//Unalign the stack
				if (stackAlignment + shadowStack > 0) {
					Amd64Backend::addConstantToReg(
						generatedCode,
						Registers::SP,
						stackAlignment + shadowStack);
				}

				//Push the result
				mCallingConvention.handleReturnValue(
					functionData, funcToCall,
					(int)inst.operandTypes().size() - numArgs);

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
				Amd64Backend::moveRegToReg(generatedCode, RegisterCallArguments::Arg0, Registers::BP);
				Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg1, (PtrValue)&function);
				generateCall(generatedCode, (unsigned char*)&Runtime::printStackFrame);
			}

			mCallingConvention.makeReturnValue(functionData, (int)inst.operandTypes().size());

			//Restore the base pointer
			Amd64Backend::moveRegToReg(generatedCode, Registers::SP, Registers::BP); //mov rsp, rbp
			Amd64Backend::popReg(generatedCode, Registers::BP); //pop rbp

			//Make the return
			Amd64Backend::ret(generatedCode);
			break;
		}
		case OpCodes::LOAD_ARG: {
			//Load rax with the argument
			int argOffset = (inst.intValue + stackOffset) * -Amd64Backend::REG_SIZE;

			Amd64Backend::moveMemoryRegWithOffsetToReg(
				generatedCode,
				Registers::AX, Registers::BP, argOffset); //mov rax [rbp+<arg offset>]

			//Push the loaded value
			OperandStack::pushReg(function, topOperandIndex + 1, Registers::AX);
			break;
		}
		case OpCodes::BRANCH: {
			Amd64Backend::jump(generatedCode, 0); //jmp <target>

			//As the exact target in native instructions isn't known, defer to later.
			functionData.unresolvedBranches.insert({
				generatedCode.size() - 5,
				BranchTarget(inst.intValue, 5)
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
				OperandStack::popReg(function, topOperandIndex, Registers::CX);
				OperandStack::popReg(function, topOperandIndex - 1, Registers::AX);
				Amd64Backend::compareRegToReg(generatedCode, Registers::AX, Registers::CX); //cmp rax, rcx
			} else if (floatOp) {
				OperandStack::popReg(function, topOperandIndex, FloatRegisters::XMM1);
				OperandStack::popReg(function, topOperandIndex - 1, FloatRegisters::XMM0);
				pushArray(generatedCode, {0x0F, 0x2E, 0xC1}); //ucomiss xmm0, xmm1
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
					if (unsignedComparison) {
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
			break;
		}
		case OpCodes::LOAD_NULL:
			OperandStack::pushInt(function, topOperandIndex + 1, 0);
			break;
		case OpCodes::NEW_ARRAY: {
			auto elemType = vmState.typeProvider().getType(inst.strValue);
			auto arrayType = static_cast<const ArrayType*>(vmState.typeProvider().getType(
				TypeSystem::arrayTypeName(elemType)));

			if (!vmState.disableGC) {
				generateGCCall(generatedCode, function, instIndex);
			}

			//The pointer to the type as the first arg
			Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0,
										(PtrValue)arrayType); //mov rdi, <addr of type pointer>

			//Pop the size as the second arg
			OperandStack::popReg(function, topOperandIndex, RegisterCallArguments::Arg1);

			//Check that the size >= 0
			mExceptionHandling.addArrayCreationCheck(functionData);

			//Call the newArray runtime function
			generateCall(generatedCode, (unsigned char*)&Runtime::newArray);

			//Push the returned pointer
			OperandStack::pushReg(function, topOperandIndex, Registers::AX);

			break;
		}
		case OpCodes::STORE_ELEMENT: {
			auto elemType = vmState.typeProvider().getType(inst.strValue);

			//Pop the operands
			OperandStack::popReg(function, topOperandIndex, Registers::DX); //The value to store
			OperandStack::popReg(function, topOperandIndex - 1, NumberedRegisters::R10); //The index of the element
			OperandStack::popReg(function, topOperandIndex - 2, Registers::AX); //The address of the array

			//Null check
			mExceptionHandling.addNullCheck(functionData);

			//Bounds check
			mExceptionHandling.addArrayBoundsCheck(functionData);

			//Compute the address of the element
			pushArray(generatedCode,
					  {0x4d, 0x6b, 0xd2, (unsigned char)TypeSystem::sizeOfType(elemType)}); //imul r10, <size of type>
			Amd64Backend::addRegToReg(generatedCode, Registers::AX, NumberedRegisters::R10); //add rax, r10

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
				pushArray(generatedCode,
						  {0x88, 0x50, (unsigned char)StackJIT::ARRAY_LENGTH_SIZE}); //mov [rax+<element offset>], dl
			}

			break;
		}
		case OpCodes::LOAD_ELEMENT: {
			auto elemType = vmState.typeProvider().getType(inst.strValue);

			//Pop the operands
			OperandStack::popReg(function, topOperandIndex, NumberedRegisters::R10); //The index of the element
			OperandStack::popReg(function, topOperandIndex - 1, Registers::AX); //The address of the ar

			//Null check
			mExceptionHandling.addNullCheck(functionData);

			//Bounds check
			mExceptionHandling.addArrayBoundsCheck(functionData);

			//Compute the address of the element
			pushArray(generatedCode,
					  {0x4d, 0x6b, 0xd2, (unsigned char)TypeSystem::sizeOfType(elemType)}); //imul r10, <size of type>
			Amd64Backend::addRegToReg(generatedCode, Registers::AX, NumberedRegisters::R10); //add rax, r10
			Amd64Backend::addByteToReg(generatedCode, Registers::AX,
									   StackJIT::ARRAY_LENGTH_SIZE); //add rax, <element offset>

			//Load the element
			auto elemSize = TypeSystem::sizeOfType(elemType);
			bool is32bits = elemSize == 4;
			bool is8bits = elemSize == 1;

			if (!is8bits) {
				Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX,
												   is32bits); //mov r/ecx, [rax]
			} else {
				pushArray(generatedCode, {0x8A, 0x08}); //mov cl, [rax]
			}

			OperandStack::pushReg(function, topOperandIndex - 1, Registers::CX);
			break;
		}
		case OpCodes::LOAD_ARRAY_LENGTH:
			//Pop the array ref
			OperandStack::popReg(function, topOperandIndex, Registers::AX);

			//Null check
			mExceptionHandling.addNullCheck(functionData);

			//Get the size of the array (an int)
			Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX, true); //mov eax, [rax]

			//Push the size
			OperandStack::pushReg(function, topOperandIndex, Registers::AX);
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
			Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0,
										(PtrValue)classType); //The pointer to the type
			generateCall(generatedCode, (unsigned char*)&Runtime::newObject);

			//Save the reference
			Amd64Backend::moveRegToReg(generatedCode, NumberedRegisters::R10, Registers::AX);

			int numArgs = (int)funcToCall.parameters().size() - 1;

			//Align the stack
			int stackAlignment = mCallingConvention.calculateStackAlignment(functionData, funcToCall);

			if (stackAlignment > 0) {
				Amd64Backend::addByteToReg(
					generatedCode,
					Registers::SP,
					-stackAlignment);
			}

			//Set the constructor arguments
			Amd64Backend::moveRegToReg(generatedCode, RegisterCallArguments::Arg0, Registers::AX);

			for (int i = numArgs - 1; i >= 0; i--) {
				mCallingConvention.callFunctionArgument(
					functionData,
					i + 1,
					inst.parameters.at(i),
					funcToCall,
					(int)inst.operandTypes().size());
			}

			//Push the reference to the created object
			Amd64Backend::moveRegToReg(generatedCode, Registers::AX, NumberedRegisters::R10);
			OperandStack::pushReg(function, topOperandIndex + 1 - numArgs, Registers::AX);

			//Shadow stack may be needed
			int shadowStack = mCallingConvention.calculateShadowStackSize();
			if (shadowStack > 0) {
				Amd64Backend::subByteFromReg(generatedCode, Registers::SP, shadowStack);
			}

			if (!needsToCompile) {
				//Mark that the constructor needs to be patched with the entry point later
				functionData.unresolvedCalls.push_back(
					UnresolvedFunctionCall(
						FunctionCallType::Relative,
						generatedCode.size(),
						funcToCall));
			} else {
				Helpers::setInt(generatedCode, callIndex, (int)generatedCode.size());
			}

			//Call the constructor
			Amd64Backend::call(generatedCode, 0);

			//Unalign the stack
			if (stackAlignment + shadowStack > 0) {
				Amd64Backend::addByteToReg(
					generatedCode,
					Registers::SP,
					stackAlignment + shadowStack);
			}

			//This is for clean up after a call, as the constructor returns nothing.
			mCallingConvention.handleReturnValue(functionData, funcToCall, (int)inst.operandTypes().size() - numArgs);

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
				OperandStack::popReg(function, topOperandIndex, Registers::AX); //The address of the object

				//Null check
				mExceptionHandling.addNullCheck(functionData);

				//Compute the address of the field
				Amd64Backend::addConstantToReg(generatedCode, Registers::AX, fieldOffset); //add rax, <field offset>

				//Load the field
				if (!is8bits) {
					Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX,
													   is32bits); //mov r/ecx, [rax]
				} else {
					pushArray(generatedCode, {0x8A, 0x08}); //mov cl, [rax]
				}

				OperandStack::pushReg(function, topOperandIndex, Registers::CX);
			} else {
				//Pop the operand
				OperandStack::popReg(function, topOperandIndex, Registers::DX); //The value to store
				OperandStack::popReg(function, topOperandIndex - 1, Registers::AX); //The address of the object

				//Null check
				mExceptionHandling.addNullCheck(functionData);

				//Store the field
				if (validCharValue(fieldOffset)) {
					if (!is8bits) {
						Amd64Backend::moveRegToMemoryRegWithCharOffset(
							generatedCode,
							Registers::AX, fieldOffset, Registers::DX, is32bits); //mov [rax+<fieldOffset>], r/edx
					} else {
						pushArray(
							generatedCode,
							{0x88, 0x50, (unsigned char)fieldOffset}); //mov [rax+<fieldOffset>], dl
					}
				} else {
					//Compute the address of the field
					Amd64Backend::addIntToReg(generatedCode, Registers::AX, fieldOffset); //add rax, <field offset>

					if (!is8bits) {
						Amd64Backend::moveRegToMemoryRegWithCharOffset(
							generatedCode,
							Registers::AX, 0, Registers::DX, is32bits); //mov [rax], r/edx
					} else {
						pushArray(generatedCode, {0x88, 0x50, 0}); //mov [rax], dl
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
			Amd64Backend::moveLongToReg(generatedCode, RegisterCallArguments::Arg0,
										(PtrValue)inst.strValue.data()); //mov <arg 0>, <addr of string>

			//The length of the string as the second arg
			Amd64Backend::moveIntToReg(generatedCode, RegisterCallArguments::Arg1,
									   (int)inst.strValue.length()); //mov <arg 1>, <string length>

			//Call the newString runtime function
			generateCall(generatedCode, (unsigned char*)&Runtime::newString);

			//Push the returned pointer
			OperandStack::pushReg(function, topOperandIndex + 1, Registers::AX);
			break;
		}
	}
}
