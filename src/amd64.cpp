#include "amd64.h"
#include <vector>
#include <assert.h>

namespace {
	//Indicates if the given value fits in a char
	bool validCharValue(int value) {
		return value >= -128 && value < 128;
	}
}

void Amd64Backend::pushReg(CodeGen& codeGen, Registers reg) {
	codeGen.push_back(0x50 | reg);
}

void Amd64Backend::pushReg(CodeGen& codeGen, FloatRegisters reg) {
	Amd64Backend::subByteFromReg(codeGen, Registers::SP, Amd64Backend::REG_SIZE);   //sub rsp, <reg size>
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
	codeGen.push_back(0x58 | reg);
}

void Amd64Backend::popReg(CodeGen& codeGen, NumberedRegisters reg) {
	codeGen.push_back(0x41);
	codeGen.push_back(0x58 | reg);
}

void Amd64Backend::popReg(CodeGen& codeGen, FloatRegisters reg) {
    Amd64Backend::moveMemoryByRegToReg(codeGen, reg, Registers::SP); 			   //movss <reg>, [rsp]
	Amd64Backend::addByteToReg(codeGen, Registers::SP, Amd64Backend::REG_SIZE);    //add rsp, <reg size>
}

void Amd64Backend::moveRegToReg(CodeGen& codeGen, Registers dest, Registers src) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::moveRegToReg(CodeGen& codeGen, NumberedRegisters dest, Registers src) {
	codeGen.push_back(0x49);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | dest | (src << 3));
}


void Amd64Backend::moveRegToReg(CodeGen& codeGen, Registers dest, NumberedRegisters src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x89);
	codeGen.push_back(0xc0 | dest | (src << 3));
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
	codeGen.push_back(srcMemReg | (dest << 3));
}

void Amd64Backend::moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, Registers src, bool is32bits) {
	if (validCharValue(offset)) {
		moveRegToMemoryRegWithCharOffset(codeGen, destMemReg, (char)offset, src, is32bits);
	} else {
		moveRegToMemoryRegWithIntOffset(codeGen, destMemReg, offset, src, is32bits);
	}
}

void Amd64Backend::moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, NumberedRegisters src) {
	if (validCharValue(offset)) {
		moveRegToMemoryRegWithCharOffset(codeGen, destMemReg, (char)offset, src);
	} else {
		moveRegToMemoryRegWithIntOffset(codeGen, destMemReg, offset, src);
	}
}

void Amd64Backend::moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset, Registers src,
													bool is32bits) {
	if (destMemReg != Registers::SP) {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x40 | destMemReg | (src << 3));
		codeGen.push_back(offset);
	} else {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x44 | (src << 3));
		codeGen.push_back(0x24);
		codeGen.push_back(offset);
	}
}

void Amd64Backend::moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset,
													NumberedRegisters src) {
	codeGen.push_back(0x4c);
	codeGen.push_back(0x89);
	codeGen.push_back(0x40 | destMemReg | (src << 3));
	codeGen.push_back(offset);
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, Registers src, bool is32bits) {
	if (destMemReg != Registers::SP) {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x80 | destMemReg | (src << 3));
	} else {
		if (!is32bits) {
			codeGen.push_back(0x48);
		}

		codeGen.push_back(0x89);
		codeGen.push_back(0x84 | (src << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, NumberedRegisters src) {
	if (destMemReg != Registers::SP) {
		codeGen.push_back(0x4c);
		codeGen.push_back(0x89);
		codeGen.push_back(0x80 | destMemReg | (src << 3));
	} else {
		codeGen.push_back(0x4c);
		codeGen.push_back(0x89);
		codeGen.push_back(0x84 | (src << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

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
		codeGen.push_back(0x40 | srcMemReg | (dest << 3));
		codeGen.push_back(offset);
	} else {
		codeGen.push_back(0x48);
		codeGen.push_back(0x8B);
		codeGen.push_back(0x44 | (dest << 3));
		codeGen.push_back(0x24);
		codeGen.push_back(offset);
	}
}

void Amd64Backend::moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, int offset) {
	if (srcMemReg != Registers::SP) {
		codeGen.push_back(0x48);
		codeGen.push_back(0x8b);
		codeGen.push_back(0x80 | srcMemReg | (dest << 3));
	} else {
		codeGen.push_back(0x48);
		codeGen.push_back(0x8b);
		codeGen.push_back(0x84 | (dest << 3));
		codeGen.push_back(0x24);
	}

	IntToBytes converter;
	converter.intValue = offset;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveIntToReg(CodeGen& codeGen, Registers dest, int value) {
	codeGen.push_back(0x48);
	codeGen.push_back(0xc7);
	codeGen.push_back(0xc0 | dest);

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveIntToReg(CodeGen& codeGen, NumberedRegisters dest, int value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0xc7);
	codeGen.push_back(0xc0 | dest);

	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveLongToReg(CodeGen& codeGen, Registers dest, Int64 value) {
	codeGen.push_back(0x48);
	codeGen.push_back(0xb8 | dest);

	LongToBytes converter;
	converter.longValue = value;

	for (std::size_t i = 0; i < sizeof(Int64); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveLongToReg(CodeGen& codeGen, NumberedRegisters dest, Int64 value) {
	codeGen.push_back(0x49);
	codeGen.push_back(0xb8 | dest);

	LongToBytes converter;
	converter.longValue = value;

	for (std::size_t i = 0; i < sizeof(Int64); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

void Amd64Backend::moveMemoryByRegToReg(CodeGen& codeGen, FloatRegisters dest, Registers srcMemReg) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x10);

	switch (srcMemReg) {
	case Registers::SP:
		codeGen.push_back(0x04 | (dest << 3));
		codeGen.push_back(0x24);
		break;
	case Registers::BP:
		codeGen.push_back(0x45 | (dest << 3));
		codeGen.push_back(0x00);
		break;
	default:
		codeGen.push_back(srcMemReg | (dest << 3));
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
		codeGen.push_back(0x40 | destMemReg | (src << 3));
		codeGen.push_back(offset);
	} else {
		codeGen.push_back(0x44 | (src << 3));
		codeGen.push_back(0x24);
		codeGen.push_back(offset);
	}
}

void Amd64Backend::moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, FloatRegisters src) {
	codeGen.push_back(0xf3);
	codeGen.push_back(0x0f);
	codeGen.push_back(0x11);

	if (destMemReg != Registers::SP) {
		codeGen.push_back(0x80 | destMemReg | (src << 3));
	} else {
		codeGen.push_back(0x84 | (src << 3));
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
    codeGen.push_back(0xd0 | func);
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
    codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::addConstantToReg(CodeGen& codeGen, Registers destReg, int srcValue, bool is32bits) {
	if (validCharValue(srcValue)) {
		addByteToReg(codeGen, destReg, (char)srcValue, is32bits);
	} else {
		addIntToReg(codeGen, destReg, srcValue, is32bits);
	}
}

void Amd64Backend::addByteToReg(CodeGen& codeGen, Registers destReg, char srcValue, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x83);
    codeGen.push_back(0xc0 | destReg);
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
		codeGen.push_back(0xc0 | destReg);
	}

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

void Amd64Backend::andRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
    if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x21);
    codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::orRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
	if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0x09);
    codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::xorRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits) {
	if (!is32bits) {
		codeGen.push_back(0x48);
	}

	codeGen.push_back(0x31);
	codeGen.push_back(0xc0 | dest | (src << 3));
}

void Amd64Backend::notReg(CodeGen& codeGen, Registers reg, bool is32bits) {
	if (!is32bits) {
        codeGen.push_back(0x48);
    }

    codeGen.push_back(0xf7);
    codeGen.push_back(0xd0 | reg);
}

void Amd64Backend::compareRegToReg(CodeGen& codeGen, Registers reg1, Registers reg2) {
	codeGen.push_back(0x48);
	codeGen.push_back(0x39);
	codeGen.push_back(0xc0 | reg1 | (reg2 << 3));
}

//Jumps to the target
void Amd64Backend::jump(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0xE9);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if equal to the target
void Amd64Backend::jumpEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x84);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if not equal to the target
void Amd64Backend::jumpNotEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x85);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if > to the target
void Amd64Backend::jumpGreaterThan(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8F);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if > to the target (unsigned)
void Amd64Backend::jumpGreaterThanUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x87);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if >= to the target
void Amd64Backend::jumpGreaterThanOrEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8D);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if >= to the target (unsigned)
void Amd64Backend::jumpGreaterThanOrEqualUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x83);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if < to the target
void Amd64Backend::jumpLessThan(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8C);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if < to the target (unsigned)
void Amd64Backend::jumpLessThanUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x82);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if <= to the target
void Amd64Backend::jumpLessThanOrEqual(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x8E);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}

//Jumps if <= to the target (unsigned)
void Amd64Backend::jumpLessThanOrEqualUnsigned(CodeGen& codeGen, int target) {
	IntToBytes converter;
	converter.intValue = target;

	codeGen.push_back(0x0F);
	codeGen.push_back(0x86);

	for (std::size_t i = 0; i < sizeof(int); i++) {
		codeGen.push_back(converter.byteValues[i]);
	}
}
