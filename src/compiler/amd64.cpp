#include "amd64.h"
#include "../helpers.h"
#include <vector>
#include <assert.h>

namespace {
	using Byte = unsigned char;
}

using Helpers::validCharValue;

std::ostream& operator<<(std::ostream& os, const Registers& reg) {
	switch (reg) {
		case Registers::AX:
			os << "ax";
			break;
		case Registers::CX:
			os << "cx";
			break;
		case Registers::DX:
			os << "dx";
			break;
		case Registers::BX:
			os << "bx";
			break;
		case Registers::SP:
			os << "sp";
			break;
		case Registers::BP:
			os << "bp";
			break;
		case Registers::SI:
			os << "si";
			break;
		case Registers::DI:
			os << "di";
			break;
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const ExtendedRegisters& reg) {
	switch (reg) {
		case ExtendedRegisters::R8:
			os << "r8";
			break;
		case ExtendedRegisters::R9:
			os << "r9";
			break;
		case ExtendedRegisters::R10:
			os << "r10";
			break;
		case ExtendedRegisters::R11:
			os << "r11";
			break;
		case ExtendedRegisters::R12:
			os << "r12";
			break;
		case ExtendedRegisters::R13:
			os << "r13";
			break;
		case ExtendedRegisters::R14:
			os << "r14";
			break;
		case ExtendedRegisters::R15:
			os << "r15";
			break;
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const Register8Bits& reg) {
	switch (reg) {
		case Register8Bits::AL:
			os << "al";
			break;
		case Register8Bits::CL:
			os << "cl";
			break;
		case Register8Bits::DL:
			os << "dl";
			break;
		case Register8Bits::BL:
			os << "bl";
			break;
		case Register8Bits::AH:
			os << "ah";
			break;
		case Register8Bits::CH:
			os << "ch";
			break;
		case Register8Bits::DH:
			os << "dh";
			break;
		case Register8Bits::BH:
			os << "bh";
			break;
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const FloatRegisters& reg) {
	switch (reg) {
		case FloatRegisters::XMM0:
			os << "xmm0";
			break;
		case FloatRegisters::XMM1:
			os << "xmm1";
			break;
		case FloatRegisters::XMM2:
			os << "xmm2";
			break;
		case FloatRegisters::XMM3:
			os << "xmm3";
			break;
		case FloatRegisters::XMM4:
			os << "xmm4";
			break;
		case FloatRegisters::XMM5:
			os << "xmm5";
			break;
		case FloatRegisters::XMM6:
			os << "xmm6";
			break;
		case FloatRegisters::XMM7:
			os << "xmm7";
			break;
	}

	return os;
}

void Amd64Backend::pushReg(CodeGen& codeGen, Registers reg) {
	codeGen.push_back(0x50 | (Byte)reg);
}

void Amd64Backend::pushReg(CodeGen& codeGen, ExtendedRegisters reg) {
	codeGen.push_back(0x41);
	codeGen.push_back(0x50 | (Byte)reg);
}

void Amd64Backend::pushReg(CodeGen& codeGen, FloatRegisters reg) {
	Amd64Backend::subByteFromReg(codeGen, Registers::SP, Amd64Backend::REGISTER_SIZE);   //sub rsp, <reg size>
	Amd64Backend::moveRegToMemoryRegWithCharOffset(codeGen, Registers::SP, 0, reg);     //movss [rsp+0], <float reg>
}

void Amd64Backend::pushInt(CodeGen& codeGen, int value) {
	codeGen.push_back(0x68);

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::popReg(CodeGen& codeGen, Registers reg) {
	codeGen.push_back(0x58 | (Byte)reg);
}

void Amd64Backend::popReg(CodeGen& codeGen, ExtendedRegisters reg) {
	codeGen.push_back(0x41);
	codeGen.push_back(0x58 | (Byte)reg);
}

void Amd64Backend::popReg(CodeGen& codeGen, FloatRegisters reg) {
    Amd64Backend::moveMemoryByRegToReg(codeGen, reg, Registers::SP); 			   //movss <reg>, [rsp]
	Amd64Backend::addByteToReg(codeGen, Registers::SP, Amd64Backend::REGISTER_SIZE);    //add rsp, <reg size>
}

void Amd64Backend::moveRegToReg(CodeGen& codeGen, Registers dest, Registers src) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::moveRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::moveRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}


void Amd64Backend::moveRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::moveRegToMemory(CodeGen& codeGen, unsigned char* destAddr, Registers srcReg) {
	assert(srcReg == Registers::AX && "Only the AX register is supported.");
	codeGen.push_back(0x48);
	codeGen.push_back(0xa3);

	PtrToBytes converter;
	converter.ptrValue = destAddr;

	for (std::size_t i = 0; i < sizeof(unsigned char*); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryToReg(CodeGen& codeGen, Registers destReg, unsigned char* srcAddr) {
	assert(destReg == Registers::AX && "Only the AX register is supported.");
	codeGen.push_back(0x48);
	codeGen.push_back(0xa1);

	PtrToBytes converter;
	converter.ptrValue = srcAddr;

	for (std::size_t i = 0; i < sizeof(unsigned char*); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	codeGen.push_back(0x8b);
	codeGen.push_back((Byte)srcMemReg | ((Byte)dest << 3));
}

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters srcMemReg) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x8b);
	codeGen.push_back((Byte)srcMemReg | ((Byte)dest << 3));
}

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters srcMemReg, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x49);
	} else {
		codeGen.push_back(0x41);
	}

	codeGen.push_back(0x8b);
	codeGen.push_back((Byte)srcMemReg | ((Byte)dest << 3));
}

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers srcMemReg) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x8b);
	codeGen.push_back((Byte)srcMemReg | ((Byte)dest << 3));
}

void Amd64Backend::moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, Registers src, bool is32bits) {
	if (validCharValue(offset)) {
		moveRegToMemoryRegWithCharOffset(codeGen, destMemReg, (char)offset, src, is32bits);
	} else {
		moveRegToMemoryRegWithIntOffset(codeGen, destMemReg, offset, src, is32bits);
	}
}

void Amd64Backend::moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, ExtendedRegisters src) {
	if (validCharValue(offset)) {
		moveRegToMemoryRegWithCharOffset(codeGen, destMemReg, (char)offset, src);
	} else {
		moveRegToMemoryRegWithIntOffset(codeGen, destMemReg, offset, src);
	}
}

void Amd64Backend::moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset, Registers src,	bool is32bits) {
	if (destMemReg != Registers::SP) {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x40 | (Byte)destMemReg | ((Byte)src << 3));
		codeGen.push_back(offset);
	} else {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x44 | ((Byte)src << 3));
		codeGen.push_back(0x24);
		codeGen.push_back(offset);
	}
}

void Amd64Backend::moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset, ExtendedRegisters src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x89);
	codeGen.push_back(0x40 | (Byte)destMemReg | ((Byte)src << 3));
	codeGen.push_back(offset);
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, Registers src, bool is32bits) {
	if (destMemReg != Registers::SP) {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));
	} else {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x84 | ((Byte)src << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x89);
	codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, ExtendedRegisters src) {
	if (destMemReg != Registers::SP) {
		codeGen.push_back(0x4c);
		codeGen.push_back(0x89);
		codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));
	} else {
		codeGen.push_back(0x4c);
		codeGen.push_back(0x89);
		codeGen.push_back(0x84 | ((Byte)src << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, Registers src, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x49);
	} else {
		codeGen.push_back(0x41);
	}

	codeGen.push_back(0x89);
	codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x41);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x11);
	codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, Register8Bits src) {
	codeGen.push_back(0x88);

	if (destMemReg != Registers::SP) {
		codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));
	} else {
		codeGen.push_back(0x84 | (Byte)destMemReg | ((Byte)src << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, Register8Bits src) {
	codeGen.push_back(0x41);
	codeGen.push_back(0x88);
	codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveIntToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, int value) {
	codeGen.push_back(0x48);
	codeGen.push_back(0xc7);

	if (destMemReg != Registers::SP)
	{
		codeGen.push_back((0x80 | (Byte)destMemReg));
	} else {
		codeGen.push_back(0x84);
		codeGen.push_back(0x24);
	}

	IntToBytes converter;

	converter.intValue = offset;
	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}

	converter.intValue = value;
	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveIntToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, int value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0xc7);
	codeGen.push_back((0x80 | (Byte)destMemReg));

	IntToBytes converter;

	converter.intValue = offset;
	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}

	converter.intValue = value;
	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithOffsetToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, int offset) {
	if (validCharValue(offset)) {
		moveMemoryRegWithCharOffsetToReg(codeGen, dest, srcMemReg, (char)offset);
	} else {
		moveMemoryRegWithIntOffsetToReg(codeGen, dest, srcMemReg, offset);
	}
}

void Amd64Backend::moveMemoryRegWithCharOffsetToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, char offset) {
	if (srcMemReg != Registers::SP) {
		codeGen.push_back(0x48);
		codeGen.push_back(0x8b);
		codeGen.push_back(0x40 | (Byte)srcMemReg | ((Byte)dest << 3));
		codeGen.push_back(offset);
	} else {
		codeGen.push_back(0x48);
		codeGen.push_back(0x8B);
		codeGen.push_back(0x44 | ((Byte)dest << 3));
		codeGen.push_back(0x24);
		codeGen.push_back(offset);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, int offset, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	if (srcMemReg != Registers::SP) {
		codeGen.push_back(0x8b);
		codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));
	} else {
		codeGen.push_back(0x8b);
		codeGen.push_back(0x84 | ((Byte)dest << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters srcMemReg, int offset) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x8b);
	codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters srcMemReg, int offset, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x49);
	} else {
		codeGen.push_back(0x41);
	}

	codeGen.push_back(0x8b);
	codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers srcMemReg, int offset) {
	if (srcMemReg != Registers::SP) {
		codeGen.push_back(0x4c);
		codeGen.push_back(0x8b);
		codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));
	} else {
		codeGen.push_back(0x4c);
		codeGen.push_back(0x8b);
		codeGen.push_back(0x84 | ((Byte)dest << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, FloatRegisters dest, Registers srcMemReg, int offset) {
	if (srcMemReg != Registers::SP) {
		codeGen.push_back(0xf3);
		codeGen.push_back(0x0f);
		codeGen.push_back(0x10);
		codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));
	} else {
		codeGen.push_back(0xf3);
		codeGen.push_back(0x0f);
		codeGen.push_back(0x10);
		codeGen.push_back(0x84 | ((Byte)dest << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, FloatRegisters dest, ExtendedRegisters srcMemReg, int offset) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x41);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x10);
	codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Register8Bits dest, Registers srcMemReg, int offset) {
	codeGen.push_back(0x8a);

	if (srcMemReg != Registers::SP) {
		codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));
	} else {
		codeGen.push_back(0x84 | ((Byte)dest << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Register8Bits dest, ExtendedRegisters srcMemReg, int offset) {
	codeGen.push_back(0x41);
	codeGen.push_back(0x8a);
	codeGen.push_back(0x80 | (Byte)srcMemReg | ((Byte)dest << 3));

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveIntToReg(CodeGen& codeGen, Registers dest, int value) {
	codeGen.push_back(0x48);
	codeGen.push_back(0xc7);
	codeGen.push_back(0xc0 | (Byte)dest);

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveIntToReg(CodeGen& codeGen, ExtendedRegisters dest, int value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0xc7);
	codeGen.push_back(0xc0 | (Byte)dest);

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveLongToReg(CodeGen& codeGen, Registers dest, std::int64_t value) {
	codeGen.push_back(0x48);
	codeGen.push_back(0xb8 | (Byte)dest);

	LongToBytes converter;
	converter.longValue = value;

	for (std::size_t i = 0; i < sizeof(std::int64_t); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveLongToReg(CodeGen& codeGen, ExtendedRegisters dest, std::int64_t value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0xb8 | (Byte)dest);

	LongToBytes converter;
	converter.longValue = value;

	for (std::size_t i = 0; i < sizeof(std::int64_t); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, FloatRegisters dest, Registers srcMemReg) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x10);

	switch (srcMemReg) {
	case Registers::SP:
		codeGen.push_back(0x04 | ((Byte)dest << 3));
		codeGen.push_back(0x24);
		break;
	case Registers::BP:
		codeGen.push_back(0x45 | ((Byte)dest << 3));
		codeGen.push_back(0x00);
		break;
	default:
		codeGen.push_back((Byte)srcMemReg | ((Byte)dest << 3));
		break;
	}
}

void Amd64Backend::moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, FloatRegisters src) {
	if (validCharValue(offset)) {
		moveRegToMemoryRegWithCharOffset(codeGen, destMemReg, (char)offset, src);
	} else {
		moveRegToMemoryRegWithIntOffset(codeGen, destMemReg, offset, src);
	}
}

void Amd64Backend::moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x11);

	if (destMemReg != Registers::SP) {
		codeGen.push_back(0x40 | (Byte)destMemReg | ((Byte)src << 3));
		codeGen.push_back(offset);
	} else {
		codeGen.push_back(0x44 | ((Byte)src << 3));
		codeGen.push_back(0x24);
		codeGen.push_back(offset);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x11);

	if (destMemReg != Registers::SP) {
		codeGen.push_back(0x80 | (Byte)destMemReg | ((Byte)src << 3));
	} else {
		codeGen.push_back(0x84 | ((Byte)src << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::callInReg(CodeGen& codeGen, Registers func) {
	codeGen.push_back(0xff);
    codeGen.push_back(0xd0 | (Byte)func);
}

void Amd64Backend::callInReg(CodeGen& codeGen, ExtendedRegisters func) {
	codeGen.push_back(0x41);
	codeGen.push_back(0xff);
	codeGen.push_back(0xd0 | (Byte)func);
}

void Amd64Backend::call(CodeGen& codeGen, int funcAddr) {
	codeGen.push_back(0xe8);

	IntToBytes converter;
	converter.intValue = funcAddr;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::ret(CodeGen& codeGen) {
	codeGen.push_back(0xc3);
}

void Amd64Backend::addRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x01);
    codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::addRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x01);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::addRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x01);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::addRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x01);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::addRegToReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x58);
	codeGen.push_back(0xc0 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::addConstantToReg(CodeGen& codeGen, Registers destReg, int srcValue, bool is32bits) {
	if (validCharValue(srcValue)) {
		addByteToReg(codeGen, destReg, (char)srcValue, is32bits);
	} else {
		addIntToReg(codeGen, destReg, srcValue, is32bits);
	}
}

void Amd64Backend::addConstantToReg(CodeGen& codeGen, ExtendedRegisters destReg, int srcValue) {
	if (validCharValue(srcValue)) {
		addByteToReg(codeGen, destReg, (char)srcValue);
	} else {
		addIntToReg(codeGen, destReg, srcValue);
	}
}

void Amd64Backend::addByteToReg(CodeGen& codeGen, Registers destReg, char srcValue, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x83);
    codeGen.push_back(0xc0 | (Byte)destReg);
    codeGen.push_back(srcValue);
}

void Amd64Backend::addByteToReg(CodeGen& codeGen, ExtendedRegisters destReg, char srcValue) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x83);
	codeGen.push_back(0xc0 | (Byte)destReg);
	codeGen.push_back(srcValue);
}

void Amd64Backend::addIntToReg(CodeGen& codeGen, Registers destReg, int srcValue, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	if (destReg == Registers::AX) {
		codeGen.push_back(0x05);
	} else {
		codeGen.push_back(0x81);
		codeGen.push_back(0xc0 | (Byte)destReg);
	}

	IntToBytes converter;
	converter.intValue = srcValue;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::addIntToReg(CodeGen& codeGen, ExtendedRegisters destReg, int srcValue) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x81);
	codeGen.push_back(0xc0 | (Byte)destReg);

	IntToBytes converter;
	converter.intValue = srcValue;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::subRegFromReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x29);
    codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::subRegFromReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x29);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::subRegFromReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x29);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::subRegFromReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x29);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::subRegFromReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x5c);
	codeGen.push_back(0xc0 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::subConstantFromReg(CodeGen& codeGen, Registers destReg, int value, bool is32bits) {
	if (validCharValue(value)) {
		subByteFromReg(codeGen, destReg, (char)value, is32bits);
	} else {
		subIntFromReg(codeGen, destReg, value, is32bits);
	}
}

void Amd64Backend::subConstantFromReg(CodeGen& codeGen, ExtendedRegisters destReg, int value) {
	if (validCharValue(value)) {
		subByteFromReg(codeGen, destReg, (char)value);
	} else {
		subIntFromReg(codeGen, destReg, value);
	}
}

void Amd64Backend::subByteFromReg(CodeGen& codeGen, Registers destReg, char value, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x83);
    codeGen.push_back(0xe8 | (Byte)destReg);
    codeGen.push_back(value);
}

void Amd64Backend::subByteFromReg(CodeGen& codeGen, ExtendedRegisters destReg, char value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x83);
	codeGen.push_back(0xe8 | (Byte)destReg);
	codeGen.push_back(value);
}

void Amd64Backend::subIntFromReg(CodeGen& codeGen, Registers destReg, int value, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    if (destReg == Registers::AX) {
    	 codeGen.push_back(0x2d);
    } else {
    	codeGen.push_back(0x81);
    	codeGen.push_back(0xe8 | (Byte)destReg);
    }

    IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::subIntFromReg(CodeGen& codeGen, ExtendedRegisters destReg, int value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x81);
	codeGen.push_back(0xe8 | (Byte)destReg);

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::multRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x0f);
    codeGen.push_back(0xaf);
    codeGen.push_back(0xc0 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::multRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x0f);
	codeGen.push_back(0xaf);
	codeGen.push_back(0xc0 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::multRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x0f);
	codeGen.push_back(0xaf);
	codeGen.push_back(0xc0 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::multRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x0f);
	codeGen.push_back(0xaf);
	codeGen.push_back(0xc0 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::multRegToReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x59);
	codeGen.push_back(0xc0 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::multConstantToReg(CodeGen& codeGen, Registers destReg, int srcValue, bool is32bits) {
	if (validCharValue(srcValue)) {
		multByteToReg(codeGen, destReg, (char)srcValue, is32bits);
	} else {
		multIntToReg(codeGen, destReg, srcValue, is32bits);
	}
}

void Amd64Backend::multConstantToReg(CodeGen& codeGen, ExtendedRegisters destReg, int srcValue) {
	if (validCharValue(srcValue)) {
		multByteToReg(codeGen, destReg, (char)srcValue);
	} else {
		multIntToReg(codeGen, destReg, srcValue);
	}
}

void Amd64Backend::multByteToReg(CodeGen& codeGen, Registers destReg, char srcValue, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	codeGen.push_back(0x6b);
	codeGen.push_back(0xc0 | (Byte)destReg | ((Byte)destReg << 3));
	codeGen.push_back(srcValue);
}

void Amd64Backend::multByteToReg(CodeGen& codeGen, ExtendedRegisters destReg, char srcValue) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x6b);
	codeGen.push_back(0xc0 | (Byte)destReg | ((Byte)destReg << 3));
	codeGen.push_back(srcValue);
}

void Amd64Backend::multIntToReg(CodeGen& codeGen, Registers destReg, int srcValue, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	codeGen.push_back(0x69);
	codeGen.push_back(0xc0 | (Byte)destReg | ((Byte)destReg << 3));

	IntToBytes converter;
	converter.intValue = srcValue;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::multIntToReg(CodeGen& codeGen, ExtendedRegisters destReg, int srcValue) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x69);
	codeGen.push_back(0xc0 | (Byte)destReg | ((Byte)destReg << 3));

	IntToBytes converter;
	converter.intValue = srcValue;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::divRegFromReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    assert(dest == Registers::AX && "Only the AX register is supported as dest.");

    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0xf7);
    codeGen.push_back(0xf8 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::divRegFromReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	assert(dest == Registers::AX && "Only the AX register is supported as dest.");

	codeGen.push_back(0x49);
	codeGen.push_back(0xf7);
	codeGen.push_back(0xf8 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::divRegFromReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x5e);
	codeGen.push_back(0xf8 | (Byte)src | ((Byte)dest << 3));
}

void Amd64Backend::andRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x21);
    codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::andRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x21);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::andRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x21);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::andRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x21);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::andIntToReg(CodeGen& codeGen, Registers dest, int value, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	if (dest == Registers::AX) {
		codeGen.push_back(0x25);
	} else {
		codeGen.push_back(0x81);
		codeGen.push_back(0xe0 | (Byte)dest);
	}

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::andIntToReg(CodeGen& codeGen, ExtendedRegisters dest, int value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x81);
	codeGen.push_back(0xe0 | (Byte)dest);

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::orRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
	if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x09);
    codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::orRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x09);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::orRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x09);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::orRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x09);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::xorRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	codeGen.push_back(0x31);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::xorRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x31);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::xorRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x31);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::xorRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x31);
	codeGen.push_back(0xc0 | (Byte)dest | ((Byte)src << 3));
}

void Amd64Backend::notReg(CodeGen& codeGen, Registers reg, bool is32bits) {
	if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0xf7);
    codeGen.push_back(0xd0 | (Byte)reg);
}

void Amd64Backend::notReg(CodeGen& codeGen, ExtendedRegisters reg) {
	codeGen.push_back(0x49);
	codeGen.push_back(0xf7);
	codeGen.push_back(0xd0 | (Byte)reg);
}

void Amd64Backend::compareRegToReg(CodeGen& codeGen, Registers reg1, Registers reg2) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x39);
	codeGen.push_back(0xc0 | (Byte)reg1 | ((Byte)reg2 << 3));
}

void Amd64Backend::compareRegToReg(CodeGen& codeGen, ExtendedRegisters reg1, ExtendedRegisters reg2) {
	codeGen.push_back(0x4d);
	codeGen.push_back(0x39);
	codeGen.push_back(0xc0 | (Byte)reg1 | ((Byte)reg2 << 3));
}

void Amd64Backend::compareRegToReg(CodeGen& codeGen, Registers reg1, ExtendedRegisters reg2) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x39);
	codeGen.push_back(0xc0 | (Byte)reg1 | ((Byte)reg2 << 3));
}

void Amd64Backend::compareRegToReg(CodeGen& codeGen, ExtendedRegisters reg1, Registers reg2) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x39);
	codeGen.push_back(0xc0 | (Byte)reg1 | ((Byte)reg2 << 3));
}

void Amd64Backend::compareRegToReg(CodeGen& codeGen, FloatRegisters reg1, FloatRegisters reg2) {
	codeGen.push_back(0x0f);
	codeGen.push_back(0x2e);
	codeGen.push_back(0xc0 | (Byte)reg2 | ((Byte)reg1 << 3));
}

void Amd64Backend::jump(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0xE9);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x84);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpNotEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x85);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpGreaterThan(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8F);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpGreaterThanUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x87);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpGreaterThanOrEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8D);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpGreaterThanOrEqualUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x83);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpLessThan(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8C);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpLessThanUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x82);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpLessThanOrEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8E);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::jumpLessThanOrEqualUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x86);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::signExtend64(CodeGen& codeGen) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x99);
}

void Amd64Backend::signExtend32(CodeGen& codeGen) {
	codeGen.push_back(0x99);
}

void Amd64Backend::signExtend16(CodeGen& codeGen) {
	codeGen.push_back(0x66);
	codeGen.push_back(0x99);
}

void Amd64Backend::convertIntToFloat(CodeGen& codeGen, FloatRegisters destination, Registers source) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x48);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x2a);
	codeGen.push_back((0xc0 | (Byte)source | (Byte)destination << 3));
}

void Amd64Backend::convertIntToFloat(CodeGen& codeGen, FloatRegisters destination, ExtendedRegisters source) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x49);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x2a);
	codeGen.push_back((0xc0 | (Byte)source | (Byte)destination << 3));
}

void Amd64Backend::convertFloatToInt(CodeGen& codeGen, Registers destination, FloatRegisters source) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x48);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x2c);
	codeGen.push_back((0xc0 | (Byte)source | (Byte)destination << 3));
}

void Amd64Backend::convertFloatToInt(CodeGen& codeGen, ExtendedRegisters destination, FloatRegisters source) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x4c);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x2c);
	codeGen.push_back((0xc0 | (Byte)source | (Byte)destination << 3));
}