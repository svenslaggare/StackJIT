#include "compilationdata.h"
#include "../core/function.h"

BranchTarget::BranchTarget(unsigned int target, unsigned int instructionSize)
	: target(target), instructionSize(instructionSize) {

}

UnresolvedFunctionCall::UnresolvedFunctionCall(FunctionCallType type, std::size_t callOffset,
											   const FunctionDefinition& funcToCall)
	: type(type), callOffset(callOffset), funcToCall(funcToCall) {

}

FunctionCompilationData::FunctionCompilationData(ManagedFunction& function)
	: function(function), operandStack(function) {

}

namespace {
	void pushArray(std::vector<unsigned char>& dest, const std::vector<unsigned char>& values) {
		for (auto current : values) {
			dest.push_back(current);
		}
	}

	//Indicates if the given value fits in a char
	bool validCharValue(int value) {
		return value >= -128 && value < 128;
	}
}

OperandStack::OperandStack(ManagedFunction& function)
	: mFunction(function) {

}

void OperandStack::assertNotEmpty() {
	if (mTopIndex <= -1) {
		throw std::runtime_error("The operand stack is empty");
	}
}

int OperandStack::getStackOperandOffset(int operandIndex) {
	return -(int)(Amd64Backend::REG_SIZE *
				  (1 + mFunction.def().numParams() + mFunction.numLocals() + operandIndex));
}

void OperandStack::reserveSpace() {
	mTopIndex++;
}

void OperandStack::duplicate() {
	assertNotEmpty();

	int stackOffset1 = getStackOperandOffset(mTopIndex);
	int stackOffset2 = getStackOperandOffset(mTopIndex + 1);

	Amd64Backend::moveMemoryRegWithOffsetToReg(
		mFunction.generatedCode(),
		Registers::AX,
		Registers::BP,
		stackOffset1); //mov rax, [rbp+<operand1 offset>]

	Amd64Backend::moveRegToMemoryRegWithOffset(
		mFunction.generatedCode(),
		Registers::BP,
		stackOffset2,
		Registers::AX); //mov [rbp+<operand2 offset>], rax

	mTopIndex++;
}

void OperandStack::popReg(Registers reg) {
	assertNotEmpty();
	int stackOffset = getStackOperandOffset(mTopIndex);

	Amd64Backend::moveMemoryRegWithOffsetToReg(
		mFunction.generatedCode(),
		reg, Registers::BP, stackOffset); //mov <reg>, [rbp+<operand offset>]

	mTopIndex--;
}

void OperandStack::popReg(ExtendedRegisters reg) {
	assertNotEmpty();
	int stackOffset = getStackOperandOffset(mTopIndex);

	if (validCharValue(stackOffset)) {
		pushArray(
			mFunction.generatedCode(),
			{0x4C, 0x8B, (unsigned char)(0x45 | ((unsigned char)reg << 3)),
			 (unsigned char)stackOffset}); //mov <reg>, [rbp+<operand offset>]
	} else {
		pushArray(
			mFunction.generatedCode(),
			{0x4C, 0x8B, (unsigned char)(0x85 | ((unsigned char)reg << 3))});

		IntToBytes converter;
		converter.intValue = stackOffset;

		for (std::size_t i = 0; i < sizeof(int); i++) {
			mFunction.generatedCode().push_back(converter.byteValues[i]);
		}
	}

	mTopIndex--;
}

void OperandStack::popReg(FloatRegisters reg) {
	assertNotEmpty();
	int stackOffset = getStackOperandOffset(mTopIndex);

	if (validCharValue(stackOffset)) {
		pushArray(
			mFunction.generatedCode(),
			{0xF3, 0x0F, 0x10, (unsigned char)(0x45 | ((unsigned char)reg << 3)),
			 (unsigned char)stackOffset}); //movss <reg>, [rbp+<operand offset>]
	} else {
		pushArray(
			mFunction.generatedCode(),
			{0xF3, 0x0F, 0x10, (unsigned char)(0x85 | ((unsigned char)reg << 3))});

		IntToBytes converter;
		converter.intValue = stackOffset;

		for (std::size_t i = 0; i < sizeof(int); i++) {
			mFunction.generatedCode().push_back(converter.byteValues[i]);
		}
	}

	mTopIndex--;
}

void OperandStack::pushReg(Registers reg) {
	mTopIndex++;

	int stackOffset = getStackOperandOffset(mTopIndex);

	Amd64Backend::moveRegToMemoryRegWithOffset(
		mFunction.generatedCode(),
		Registers::BP, stackOffset, reg); //mov [rbp+<operand offset>], <reg>
}

void OperandStack::pushReg(FloatRegisters reg) {
	mTopIndex++;
	int stackOffset = getStackOperandOffset(mTopIndex);

	Amd64Backend::moveRegToMemoryRegWithOffset(
		mFunction.generatedCode(),
		Registers::BP,
		stackOffset, reg); //movss [rbp+<operand offset>], <float reg>
}

void OperandStack::pushInt(int value, bool increaseStack) {
	if (increaseStack) {
		mTopIndex++;
	}

	int stackOffset = getStackOperandOffset(mTopIndex);

	//mov [rbp+<operand offset>], value
	if (validCharValue(stackOffset)) {
		pushArray(
			mFunction.generatedCode(),
			{0x48, 0xC7, 0x45, (unsigned char)stackOffset});
	} else {
		pushArray(
			mFunction.generatedCode(),
			{0x48, 0xC7, 0x85});

		IntToBytes intToBytes;
		intToBytes.intValue = stackOffset;
		for (std::size_t i = 0; i < sizeof(int); i++) {
			mFunction.generatedCode().push_back(intToBytes.byteValues[i]);
		}
	}

	IntToBytes intToBytes;
	intToBytes.intValue = value;
	for (std::size_t i = 0; i < sizeof(int); i++) {
		mFunction.generatedCode().push_back(intToBytes.byteValues[i]);
	}
}