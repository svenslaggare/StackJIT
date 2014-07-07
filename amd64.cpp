#include "amd64.h"
#include <vector>
#include <assert.h>

union IntToBytes {
    int IntValue;
    unsigned char ByteValues[sizeof(int)];
};

union LongToBytes {
    long LongValue;
    unsigned char ByteValues[sizeof(long)];
};

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

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg) {
	codeGen.push_back(0x48);
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

