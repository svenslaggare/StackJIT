#include "amd64.h"
#include <vector>
#include <assert.h>

void Amd64Backend::pushReg(CodeGen& codeGen, Registers reg) {
	codeGen.push_back(0x50 | reg);
}

void Amd64Backend::pushInt(CodeGen& codeGen, int value) {
	codeGen.push_back(0x68);

	IntToBytes converter;
	converter.IntValue = value;

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

void Amd64Backend::popReg(CodeGen& codeGen, Registers reg) {
	codeGen.push_back(0x58 | reg);
}

void Amd64Backend::moveRegToReg(CodeGen& codeGen, Registers dest, Registers src) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::moveRegToMemory(CodeGen& codeGen, long destAddr, Registers srcReg) {
	assert(srcReg == Registers::AX && "Only the AX register is supported.");
	codeGen.push_back(0x48);
	codeGen.push_back(0xa3);

	LongToBytes converter;
	converter.LongValue = destAddr;

	for (int i = 0; i < sizeof(long); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

void Amd64Backend::moveMemoryToReg(CodeGen& codeGen, Registers destReg, long srcAddr) {
	assert(destReg == Registers::AX && "Only the AX register is supported.");
	codeGen.push_back(0x48);
	codeGen.push_back(0xa1);

	LongToBytes converter;
	converter.LongValue = srcAddr;

	for (int i = 0; i < sizeof(long); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	codeGen.push_back(0x8b);
	codeGen.push_back(srcMemReg | (dest << 3));
}

void Amd64Backend::moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, char offset, Registers src) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x89);
	codeGen.push_back(0x40 | destMemReg | (src << 3));
	codeGen.push_back(offset);
}

void Amd64Backend::moveIntToReg(CodeGen& codeGen, Registers dest, int value) {
	codeGen.push_back(0x48);
	codeGen.push_back(0xc7);
	codeGen.push_back(0xc0 | dest);

	IntToBytes converter;
	converter.IntValue = value;

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

void Amd64Backend::moveLongToReg(CodeGen& codeGen, Registers dest, long value) {
	codeGen.push_back(0x48);
	codeGen.push_back(0xb8 | dest);

	LongToBytes converter;
	converter.LongValue = value;

	for (int i = 0; i < sizeof(long); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

void Amd64Backend::callInReg(CodeGen& codeGen, Registers func) {
	codeGen.push_back(0xff);
    codeGen.push_back(0xd0 | func);
}

void Amd64Backend::call(CodeGen& codeGen, int funcAddr) {
	codeGen.push_back(0xff);
	codeGen.push_back(0x14);
	codeGen.push_back(0x25);

	IntToBytes converter;
	converter.IntValue = funcAddr;

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
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
    codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::addByteToReg(CodeGen& codeGen, Registers destReg, char srcValue, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x83);
    codeGen.push_back(0xc0 | destReg);
    codeGen.push_back(srcValue);
}

void Amd64Backend::subRegFromReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x29);
    codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::subByteFromReg(CodeGen& codeGen, Registers destReg, char value, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x83);
    codeGen.push_back(0xe8 | destReg);
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
    	codeGen.push_back(0xe8 | destReg);
    }

    IntToBytes converter;
	converter.IntValue = value;

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

void Amd64Backend::multRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x0f);
    codeGen.push_back(0xaf);
    codeGen.push_back(0xc0 | src | (dest << 3));
}

void Amd64Backend::divRegFromReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    assert(dest == Registers::AX && "Only the AX register is supported as dest.");

    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0xf7);
    codeGen.push_back(0xf8 | src | (dest << 3));
}

void Amd64Backend::compareRegToReg(CodeGen& codeGen, Registers reg1, Registers reg2) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x39);
	codeGen.push_back(0xc0 | reg1 | (reg2 << 3));
}

//Jumps to the target
void Amd64Backend::jump(CodeGen& codeGen, int target)
{
	IntToBytes converter;
	converter.IntValue = target;

	codeGen.push_back(0xE9);

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

//Jumps if equal to the target
void Amd64Backend::jumpEqual(CodeGen& codeGen, int target)
{
	IntToBytes converter;
	converter.IntValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x84);

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

//Jumps if not equal to the target
void Amd64Backend::jumpNotEqual(CodeGen& codeGen, int target)
{
	IntToBytes converter;
	converter.IntValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x85);

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

//Jumps if > to the target
void Amd64Backend::jumpGreaterThan(CodeGen& codeGen, int target)
{
	IntToBytes converter;
	converter.IntValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8F);

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

//Jumps if >= to the target
void Amd64Backend::jumpGreaterThanOrEqual(CodeGen& codeGen, int target)
{
	IntToBytes converter;
	converter.IntValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8D);

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

//Jumps if < to the target
void Amd64Backend::jumpLessThan(CodeGen& codeGen, int target)
{
	IntToBytes converter;
	converter.IntValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8C);

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}

//Jumps if <= to the target
void Amd64Backend::jumpLessThanOrEqual(CodeGen& codeGen, int target)
{
	IntToBytes converter;
	converter.IntValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8E);

	for (int i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.ByteValues[i]);
	}
}
