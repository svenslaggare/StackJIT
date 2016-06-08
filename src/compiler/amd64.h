#pragma once
#include <vector>
#include "../stackjit.h"

//Converts between primitive types and unsigned char arrays
union ShortToBytes {
    short shortValue;
    unsigned char byteValues[sizeof(short)];
};

union IntToBytes {
    int intValue;
    unsigned char byteValues[sizeof(int)];
};

union LongToBytes {
	std::int64_t longValue;
    unsigned char byteValues[sizeof(std::int64_t)];
};

union PtrToBytes {
	unsigned char* ptrValue;
    unsigned char byteValues[sizeof(unsigned char*)];
};

//The registers
enum class Registers : unsigned char {
	AX = 0b000,
	CX = 0b001,
	DX = 0b010,
	BX = 0b011,
	SP = 0b100,
	BP = 0b101,
	SI = 0b110,
	DI = 0b111,
};

//The extended registers
enum class ExtendedRegisters : unsigned char {
	R8 = 0b000,
	R9 = 0b001,
	R10 = 0b010,
	R11 = 0b011,
	R12 = 0b100,
	R13 = 0b101,
	R14 = 0b110,
	R15 = 0b111,
};

//The floating point registers
enum class FloatRegisters : unsigned char {
	XMM0 = 0b000,
	XMM1 = 0b001,
	XMM2 = 0b010,
	XMM3 = 0b011,
	XMM4 = 0b100,
	XMM5 = 0b101,
	XMM6 = 0b110,
	XMM7 = 0b111,
};

using CodeGen = std::vector<unsigned char>;

//Backend for AMD64
namespace Amd64Backend {
	//The size of a register
	const int REG_SIZE = 8;

	//Pushes the given register to the stack
	void pushReg(CodeGen&, Registers);
	void pushReg(CodeGen&, ExtendedRegisters);

	//Pushes the given register to the stack
	void pushReg(CodeGen&, FloatRegisters);

	//Pushes the given integer to the stack
	void pushInt(CodeGen&, int);

	//Pops from the stack to the given register
	void popReg(CodeGen&, Registers);

	//Pops from the stack to the given register
	void popReg(CodeGen&, ExtendedRegisters);

	//Pops from the stack to the given register
	void popReg(CodeGen&, FloatRegisters);

	//Moves the content from the second register to the first register
	void moveRegToReg(CodeGen&, Registers, Registers);
	void moveRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void moveRegToReg(CodeGen&, ExtendedRegisters, Registers);
	void moveRegToReg(CodeGen&, Registers, ExtendedRegisters);

	//Moves the content from the register to the memory address
	void moveRegToMemory(CodeGen&, unsigned char*, Registers);

	//Moves the content from given memory address to the register
	void moveMemoryToReg(CodeGen&, Registers, unsigned char*);

	//Moves the content from memory where the address is in the second register to the first register
	void moveMemoryByRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void moveMemoryByRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void moveMemoryByRegToReg(CodeGen&, Registers, ExtendedRegisters, bool is32bits = false);
	void moveMemoryByRegToReg(CodeGen&, ExtendedRegisters, Registers);

	//Moves the content from a register to memory where the address is in a register + offset
	void moveRegToMemoryRegWithOffset(CodeGen&, Registers, int, Registers, bool is32bits = false);
	void moveRegToMemoryRegWithOffset(CodeGen&, Registers, int, ExtendedRegisters);

	//Moves the content from a register to memory where the address is in a register + char offset
	void moveRegToMemoryRegWithCharOffset(CodeGen&, Registers, char, Registers, bool is32bits = false);
	void moveRegToMemoryRegWithCharOffset(CodeGen&, Registers, char, ExtendedRegisters);

	//Moves the content from a register to memory where the address is in a register + int offset
	void moveRegToMemoryRegWithIntOffset(CodeGen&, Registers, int, Registers, bool is32bits = false);
	void moveRegToMemoryRegWithIntOffset(CodeGen&, ExtendedRegisters, int, ExtendedRegisters);
	void moveRegToMemoryRegWithIntOffset(CodeGen&, Registers, int, ExtendedRegisters);
	void moveRegToMemoryRegWithIntOffset(CodeGen&, ExtendedRegisters, int, Registers);

	//Moves the content from a memory where the address is a register + offset to a register
	void moveMemoryRegWithOffsetToReg(CodeGen&, Registers, Registers, int);

	//Moves the content from a memory where the address is a register + char offset to a register
	void moveMemoryRegWithCharOffsetToReg(CodeGen&, Registers, Registers, char);

	//Moves the content from a memory where the address is a register + int offset to a register
	void moveMemoryRegWithIntOffsetToReg(CodeGen&, Registers, Registers, int);
	void moveMemoryRegWithIntOffsetToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters, int);
	void moveMemoryRegWithIntOffsetToReg(CodeGen&, Registers, ExtendedRegisters, int);
	void moveMemoryRegWithIntOffsetToReg(CodeGen&, ExtendedRegisters, Registers, int);

	//Moves the given integer (32-bits) to the given register
	void moveIntToReg(CodeGen&, Registers, int);
	void moveIntToReg(CodeGen&, ExtendedRegisters, int);

	//Moves the given long (64-bits) to the given register
	void moveLongToReg(CodeGen&, Registers, std::int64_t);
	void moveLongToReg(CodeGen&, ExtendedRegisters, std::int64_t);

	//Moves the content from memory where the address is in the second register to the first register
	void moveMemoryByRegToReg(CodeGen&, FloatRegisters, Registers);

	//Moves the content from a register to memory where the address is in a register + offset
	void moveRegToMemoryRegWithOffset(CodeGen&, Registers, int, FloatRegisters);

	//Moves the content from a register to memory where the address is in a register + char offset
	void moveRegToMemoryRegWithCharOffset(CodeGen&, Registers, char, FloatRegisters);

	//Moves the content from a register to memory where the address is in a register + int offset
	void moveRegToMemoryRegWithIntOffset(CodeGen&, Registers, int, FloatRegisters);

	//Calls the given function where the entry points is in a register
	void callInReg(CodeGen&, Registers);
	void callInReg(CodeGen&, ExtendedRegisters);

	//Calls the given function
	void call(CodeGen&, int);

	//The return instruction
	void ret(CodeGen&);

	//Adds the second register to the first
	void addRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void addRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void addRegToReg(CodeGen&, Registers, ExtendedRegisters);
	void addRegToReg(CodeGen&, ExtendedRegisters, Registers);
	void addRegToReg(CodeGen&, FloatRegisters, FloatRegisters);

	//Adds the given integer constant to the given register
	void addConstantToReg(CodeGen&, Registers, int, bool is32bits = false);
	void addConstantToReg(CodeGen&, ExtendedRegisters, int);

	//Adds the given byte to the given register
	void addByteToReg(CodeGen&, Registers, char, bool is32bits = false);
	void addByteToReg(CodeGen&, ExtendedRegisters, char);

	//Adds the given int to the given register
	void addIntToReg(CodeGen&, Registers, int, bool is32bits = false);
	void addIntToReg(CodeGen&, ExtendedRegisters, int);

	//Subtracts the second register from the first
	void subRegFromReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void subRegFromReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void subRegFromReg(CodeGen&, Registers, ExtendedRegisters);
	void subRegFromReg(CodeGen&, ExtendedRegisters, Registers);
	void subRegFromReg(CodeGen&, FloatRegisters, FloatRegisters);

	//Subtracts the given constant from  the given register
	void subConstantFromReg(CodeGen&, Registers, int, bool is32bits = false);
	void subConstantFromReg(CodeGen&, ExtendedRegisters, int);

	//Subtracts the given byte from the given register
	void subByteFromReg(CodeGen&, Registers, char, bool is32bits = false);
	void subByteFromReg(CodeGen&, ExtendedRegisters, char);

	//Subtracts the given int from the given register
	void subIntFromReg(CodeGen&, Registers, int, bool is32bits = false);
	void subIntFromReg(CodeGen&, ExtendedRegisters, int);

	//Multiplies the first register by the second
	void multRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void multRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void multRegToReg(CodeGen&, Registers, ExtendedRegisters);
	void multRegToReg(CodeGen&, ExtendedRegisters, Registers);
	void multRegToReg(CodeGen&, FloatRegisters, FloatRegisters);

	//Multiplies the given integer constant to the given register
	void multConstantToReg(CodeGen&, Registers, int, bool is32bits = false);
	void multConstantToReg(CodeGen&, ExtendedRegisters, int);

	//Multiplies the given byte to the given register
	void multByteToReg(CodeGen&, Registers, char, bool is32bits = false);
	void multByteToReg(CodeGen&, ExtendedRegisters, char);

	//Multiplies the given int to the given register
	void multIntToReg(CodeGen&, Registers, int, bool is32bits = false);
	void multIntToReg(CodeGen&, ExtendedRegisters, int);

	//Divides the second register from the first
	void divRegFromReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void divRegFromReg(CodeGen&, Registers, ExtendedRegisters);
	void divRegFromReg(CodeGen&, FloatRegisters, FloatRegisters);

	//AND's the second register to the first
	void andRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void andRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void andRegToReg(CodeGen&, Registers, ExtendedRegisters);
	void andRegToReg(CodeGen&, ExtendedRegisters, Registers);

	//OR's the second register to the first
	void orRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void orRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void orRegToReg(CodeGen&, Registers, ExtendedRegisters);
	void orRegToReg(CodeGen&, ExtendedRegisters, Registers);

	//XOR's the second register to the first
	void xorRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);
	void xorRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void xorRegToReg(CodeGen&, Registers, ExtendedRegisters);
	void xorRegToReg(CodeGen&, ExtendedRegisters, Registers);

	//NOT's the register
	void notReg(CodeGen&, Registers, bool is32bits = false);
	void notReg(CodeGen&, ExtendedRegisters);

	//Compares the two registers
	void compareRegToReg(CodeGen&, Registers, Registers);
	void compareRegToReg(CodeGen&, ExtendedRegisters, ExtendedRegisters);
	void compareRegToReg(CodeGen&, Registers, ExtendedRegisters);
	void compareRegToReg(CodeGen&, ExtendedRegisters, Registers);
	void compareRegToReg(CodeGen&, FloatRegisters, FloatRegisters);

	//Jumps to the target relative the current instruction
	void jump(CodeGen&, int);

	//Jumps if equal to the target relative the current instruction
	void jumpEqual(CodeGen&, int);

	//Jumps if not equal to the target relative the current instruction
	void jumpNotEqual(CodeGen&, int);

	//Jumps if > to the target relative the current instruction
	void jumpGreaterThan(CodeGen&, int);

	//Jumps if > to the target relative the current instruction. Uses unsigned comparison.
	void jumpGreaterThanUnsigned(CodeGen&, int);

	//Jumps if >= to the target relative the current instruction
	void jumpGreaterThanOrEqual(CodeGen&, int);

	//Jumps if >= to the target relative the current instruction. Uses unsigned comparison.
	void jumpGreaterThanOrEqualUnsigned(CodeGen&, int);

	//Jumps if < to the target relative the current instruction
	void jumpLessThan(CodeGen&, int);

	//Jumps if < to the target relative the current instruction. Uses unsigned comparison.
	void jumpLessThanUnsigned(CodeGen&, int);

	//Jumps if <= to the target relative the current instruction
	void jumpLessThanOrEqual(CodeGen&, int);

	//Jumps if <= to the target relative the current instruction. Uses unsigned comparison.
	void jumpLessThanOrEqualUnsigned(CodeGen&, int);

	//Sign extends the RAX register
	void signExtend64(CodeGen&);

	//Sign extends the EAX register
	void signExtend32(CodeGen&);

	//Sign extends the AX register
	void signExtend16(CodeGen&);

	//Converts the second register to a float
	void convertIntToFloat(CodeGen&, FloatRegisters, Registers);
	void convertIntToFloat(CodeGen&, FloatRegisters, ExtendedRegisters);

	//Converts the second register to an int
	void convertFloatToInt(CodeGen&, Registers, FloatRegisters);
	void convertFloatToInt(CodeGen&, ExtendedRegisters, FloatRegisters);
}
