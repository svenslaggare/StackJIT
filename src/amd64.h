#pragma once
#include <vector>

//Converts between primitive types and char arrays
union ShortToBytes {
    short shortValue;
    unsigned char byteValues[sizeof(short)];
};

union IntToBytes {
    int intValue;
    unsigned char byteValues[sizeof(int)];
};

union LongToBytes {
    long longValue;
    unsigned char byteValues[sizeof(long)];
};

//The registers
enum Registers : unsigned char {
	AX = 0b000,
	CX = 0b001,
	DX = 0b010,
	BX = 0b011,
	SP = 0b100,
	BP = 0b101,
	SI = 0b110,
	DI = 0b111,
};

//The numbered registers
enum NumberedRegisters : unsigned char {
	R8 = 0b000,
	R9 = 0b001,
	R10 = 0b010,
	R11 = 0b011,
};

//The floating point registers
enum FloatRegisters : unsigned char {
	XMM0 = 0b000,
	XMM1 = 0b001,
	XMM2 = 0b010,
	XMM3 = 0b011,
	XMM4 = 0b100,
	XMM5 = 0b101,
	XMM6 = 0b110,
	XMM7 = 0b111,
};

//The register for function arguments
namespace RegisterCallArguments {
	const Registers Arg0 = Registers::DI;
	const Registers Arg1 = Registers::SI;
	const Registers Arg2 = Registers::DX;
	const Registers Arg3 = Registers::CX;
	const NumberedRegisters Arg4 = NumberedRegisters::R8;
	const NumberedRegisters Arg5 = NumberedRegisters::R9;
}

namespace FloatRegisterCallArguments {
	const FloatRegisters Arg0 = FloatRegisters::XMM0;
	const FloatRegisters Arg1 = FloatRegisters::XMM1;
	const FloatRegisters Arg2 = FloatRegisters::XMM2;
	const FloatRegisters Arg3 = FloatRegisters::XMM3;
	const FloatRegisters Arg4 = FloatRegisters::XMM4;
	const FloatRegisters Arg5 = FloatRegisters::XMM5;
	const FloatRegisters Arg6 = FloatRegisters::XMM6;
	const FloatRegisters Arg7 = FloatRegisters::XMM7;
}

typedef std::vector<unsigned char> CodeGen;

//Backend for AMD64
namespace Amd64Backend {
	//The size of a register
	const int REG_SIZE = 8;

	//Pushes the given register to the stack
	void pushReg(CodeGen&, Registers);

	//Pushes the given register to the stack
	void pushReg(CodeGen&, FloatRegisters);

	//Pushes the given integer to the stack
	void pushInt(CodeGen&, int);

	//Pops from the stack to the given register
	void popReg(CodeGen&, Registers);

	//Pops from the stack to the given register
	void popReg(CodeGen&, NumberedRegisters);

	//Pops from the stack to the given register
	void popReg(CodeGen&, FloatRegisters);

	//Moves the content from the second register to the first register
	void moveRegToReg(CodeGen&, Registers, Registers);
	void moveRegToReg(CodeGen&, NumberedRegisters, Registers);
	void moveRegToReg(CodeGen&, Registers, NumberedRegisters);

	//Moves the content from the register to the memory address
	void moveRegToMemory(CodeGen&, long, Registers);

	//Moves the content from given memory address to the register
	void moveMemoryToReg(CodeGen&, Registers, long);

	//Moves the content from memory where the address is in the second register to the first register
	void moveMemoryByRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//Moves the content from a register to memory where the address is in a register + offset
	void moveRegToMemoryRegWithOffset(CodeGen&, Registers, int, Registers, bool is32bits = false);
	void moveRegToMemoryRegWithOffset(CodeGen&, Registers, int, NumberedRegisters);

	//Moves the content from a register to memory where the address is in a register + char offset
	void moveRegToMemoryRegWithCharOffset(CodeGen&, Registers, char, Registers, bool is32bits = false);
	void moveRegToMemoryRegWithCharOffset(CodeGen&, Registers, char, NumberedRegisters);

	//Moves the content from a register to memory where the address is in a register + int offset
	void moveRegToMemoryRegWithIntOffset(CodeGen&, Registers, int, Registers, bool is32bits = false);
	void moveRegToMemoryRegWithIntOffset(CodeGen&, Registers, int, NumberedRegisters);

	//Moves the content from a memory where the address is a register + offset to a register
	void moveMemoryRegWithOffsetToReg(CodeGen&, Registers, Registers, int);

	//Moves the content from a memory where the address is a register + char offset to a register
	void moveMemoryRegWithCharOffsetToReg(CodeGen&, Registers, Registers, char);

	//Moves the content from a memory where the address is a register + int offset to a register
	void moveMemoryRegWithIntOffsetToReg(CodeGen&, Registers, Registers, int);

	//Moves the given integer (32-bits) to the given register
	void moveIntToReg(CodeGen&, Registers, int);

	//Moves the given long (64-bits) to the given register
	void moveLongToReg(CodeGen&, Registers, long);

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

	//Calls the given function
	void call(CodeGen&, int);

	//The return instruction
	void ret(CodeGen&);

	//Adds the second register to the first
	void addRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//Adds the given integer constant to the given register
	void addConstantToReg(CodeGen&, Registers, int, bool is32bits = false);

	//Adds the given byte to the given register
	void addByteToReg(CodeGen&, Registers, char, bool is32bits = false);

	//Adds the given int to the given register
	void addIntToReg(CodeGen&, Registers, int, bool is32bits = false);

	//Subtracts the second register from the first
	void subRegFromReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//Subtracts the given byte from the given register
	void subByteFromReg(CodeGen&, Registers, char, bool is32bits = false);

	//Subtracts the given int from the given register
	void subIntFromReg(CodeGen&, Registers, int, bool is32bits = false);

	//Multiplies the first register by the second
	void multRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//Divides the second register from the first
	void divRegFromReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//AND's the second register to the first
	void andRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//OR's the second register to the first
	void orRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//XOR's the second register to the first
	void xorRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//NOT's the register
	void notReg(CodeGen&, Registers, bool is32bits = false);

	//Compares the two registers
	void compareRegToReg(CodeGen&, Registers, Registers);

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
}
