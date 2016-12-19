#pragma once
#include <vector>
#include <ostream>
#include "../stackjit.h"

namespace stackjit {
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

	//The 8-bit registers
	enum class Register8Bits : unsigned char {
		AL = 0b000,
		CL = 0b001,
		DL = 0b010,
		BL = 0b011,
		AH = 0b100,
		CH = 0b101,
		DH = 0b110,
		BH = 0b111
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

	std::ostream& operator<<(std::ostream& os, const Registers& reg);
	std::ostream& operator<<(std::ostream& os, const ExtendedRegisters& reg);
	std::ostream& operator<<(std::ostream& os, const Register8Bits& reg);
	std::ostream& operator<<(std::ostream& os, const FloatRegisters& reg);

	using CodeGen = std::vector<unsigned char>;

	//Backend for AMD64
	namespace Amd64Backend {
		//The size of a register
		const int REGISTER_SIZE = 8;

		//Pushes the given register to the stack
		void pushReg(CodeGen& codeGen, Registers reg);
		void pushReg(CodeGen& codeGen, ExtendedRegisters reg);

		//Pushes the given register to the stack
		void pushReg(CodeGen& codeGen, FloatRegisters reg);

		//Pushes the given integer to the stack
		void pushInt(CodeGen& codeGen, int value);

		//Pops from the stack to the given register
		void popReg(CodeGen& codeGen, Registers reg);

		//Pops from the stack to the given register
		void popReg(CodeGen& codeGen, ExtendedRegisters reg);

		//Pops from the stack to the given register
		void popReg(CodeGen& codeGen, FloatRegisters reg);

		//Moves the content from the second register to the first register
		void moveRegToReg(CodeGen& codeGen, Registers dest, Registers src);
		void moveRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src);
		void moveRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src);
		void moveRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);

		//Moves the content from the register to the memory address
		void moveRegToMemory(CodeGen& codeGen, unsigned char* destAddr, Registers srcReg);

		//Moves the content from given memory address to the register
		void moveMemoryToReg(CodeGen& codeGen, Registers destReg, unsigned char* srcAddr);

		//Moves the content from memory where the address is in the second register to the first register
		void moveMemoryByRegToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, bool is32bits = false);
		void moveMemoryByRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters srcMemReg);
		void moveMemoryByRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters srcMemReg, bool is32bits = false);
		void moveMemoryByRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers srcMemReg);

		//Moves the content from a register to memory where the address is in a register + offset
		void moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, Registers src, bool is32bits = false);
		void moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, ExtendedRegisters src);

		//Moves the content from a register to memory where the address is in a register + char offset
		void moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset, Registers src, bool is32bits = false);
		void moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset, ExtendedRegisters src);

		//Moves the content from a register to memory where the address is in a register + int offset
		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, Registers src, bool is32bits = false);
		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, ExtendedRegisters src);
		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, ExtendedRegisters src);
		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, Registers src, bool is32bits = false);
		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, FloatRegisters src);

		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, Register8Bits src);
		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, Register8Bits src);

		//Moves a 32-bits integer to the memory where the address is in a register + int offset
		void moveIntToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, int value);
		void moveIntToMemoryRegWithIntOffset(CodeGen& codeGen, ExtendedRegisters destMemReg, int offset, int value);

		//Moves the content from a memory where the address is a register + offset to a register
		void moveMemoryRegWithOffsetToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, int offset);

		//Moves the content from a memory where the address is a register + char offset to a register
		void moveMemoryRegWithCharOffsetToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, char offset);

		//Moves the content from a memory where the address is a register + int offset to a register
		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Registers dest, Registers srcMemReg, int offset, bool is32bits = false);
		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters srcMemReg, int offset);
		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters srcMemReg, int offset, bool is32bits = false);
		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers srcMemReg, int offset);
		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, FloatRegisters dest, Registers srcMemReg, int offset);
		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, FloatRegisters dest, ExtendedRegisters srcMemReg, int offset);

		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Register8Bits dest, Registers srcMemReg, int offset);
		void moveMemoryRegWithIntOffsetToReg(CodeGen& codeGen, Register8Bits dest, ExtendedRegisters srcMemReg, int offset);

		//Moves the given integer (32-bits) to the given register
		void moveIntToReg(CodeGen& codeGen, Registers dest, int value);
		void moveIntToReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//Moves the given long (64-bits) to the given register
		void moveLongToReg(CodeGen& codeGen, Registers dest, std::int64_t value);
		void moveLongToReg(CodeGen& codeGen, ExtendedRegisters dest, std::int64_t value);

		//Moves the content from memory where the address is in the second register to the first register
		void moveMemoryByRegToReg(CodeGen& codeGen, FloatRegisters dest, Registers srcMemReg);

		//Moves the content from a register to memory where the address is in a register + offset
		void moveRegToMemoryRegWithOffset(CodeGen& codeGen, Registers destMemReg, int offset, FloatRegisters src);

		//Moves the content from a register to memory where the address is in a register + char offset
		void moveRegToMemoryRegWithCharOffset(CodeGen& codeGen, Registers destMemReg, char offset, FloatRegisters src);

		//Moves the content from a register to memory where the address is in a register + int offset
		void moveRegToMemoryRegWithIntOffset(CodeGen& codeGen, Registers destMemReg, int offset, FloatRegisters src);

		//Calls the given function where the entry points is in a register
		void callInReg(CodeGen& codeGen, Registers func);
		void callInReg(CodeGen& codeGen, ExtendedRegisters func);

		//Calls the given function
		void call(CodeGen& codeGen, int funcAddr);

		//The return instruction
		void ret(CodeGen& codeGen);

		//Adds the second register to the first
		void addRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits = false);
		void addRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src);
		void addRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);
		void addRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src);
		void addRegToReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src);

		//Adds the given integer constant to the given register
		void addConstantToReg(CodeGen& codeGen, Registers dest, int value, bool is32bits = false);
		void addConstantToReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//Adds the given byte to the given register
		void addByteToReg(CodeGen& codeGen, Registers dest, char value, bool is32bits = false);
		void addByteToReg(CodeGen& codeGen, ExtendedRegisters dest, char value);

		//Adds the given int to the given register
		void addIntToReg(CodeGen& codeGen, Registers dest, int value, bool is32bits = false);
		void addIntToReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//Subtracts the second register from the first
		void subRegFromReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits = false);
		void subRegFromReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src);
		void subRegFromReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);
		void subRegFromReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src);
		void subRegFromReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src);

		//Subtracts the given constant from  the given register
		void subConstantFromReg(CodeGen& codeGen, Registers dest, int value, bool is32bits = false);
		void subConstantFromReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//Subtracts the given byte from the given register
		void subByteFromReg(CodeGen& codeGen, Registers dest, char value, bool is32bits = false);
		void subByteFromReg(CodeGen& codeGen, ExtendedRegisters dest, char value);

		//Subtracts the given int from the given register
		void subIntFromReg(CodeGen& codeGen, Registers dest, int value, bool is32bits = false);
		void subIntFromReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//Multiplies the first register by the second
		void multRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits = false);
		void multRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src);
		void multRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);
		void multRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src);
		void multRegToReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src);

		//Multiplies the given integer constant to the given register
		void multConstantToReg(CodeGen& codeGen, Registers dest, int value, bool is32bits = false);
		void multConstantToReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//Multiplies the given byte to the given register
		void multByteToReg(CodeGen& codeGen, Registers dest, char value, bool is32bits = false);
		void multByteToReg(CodeGen& codeGen, ExtendedRegisters dest, char value);

		//Multiplies the given int to the given register
		void multIntToReg(CodeGen& codeGen, Registers dest, int value, bool is32bits = false);
		void multIntToReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//Divides the second register from the first
		void divRegFromReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits = false);
		void divRegFromReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);
		void divRegFromReg(CodeGen& codeGen, FloatRegisters dest, FloatRegisters src);

		//AND's the second register to the first
		void andRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits = false);
		void andRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src);
		void andRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);
		void andRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src);

		//AND's the given 32-bit int constant to the first register
		void andIntToReg(CodeGen& codeGen, Registers dest, int value, bool is32bits = false);
		void andIntToReg(CodeGen& codeGen, ExtendedRegisters dest, int value);

		//OR's the second register to the first
		void orRegToReg(CodeGen& codeGen, Registers dest, Registers, bool is32bits = false);
		void orRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src);
		void orRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);
		void orRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src);

		//XOR's the second register to the first
		void xorRegToReg(CodeGen& codeGen, Registers dest, Registers src, bool is32bits = false);
		void xorRegToReg(CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src);
		void xorRegToReg(CodeGen& codeGen, Registers dest, ExtendedRegisters src);
		void xorRegToReg(CodeGen& codeGen, ExtendedRegisters dest, Registers src);

		//NOT's the register
		void notReg(CodeGen& codeGen, Registers reg, bool is32bits = false);
		void notReg(CodeGen& codeGen, ExtendedRegisters reg);

		//Compares the two registers
		void compareRegToReg(CodeGen& codeGen, Registers reg1, Registers reg2);
		void compareRegToReg(CodeGen& codeGen, ExtendedRegisters reg1, ExtendedRegisters reg2);
		void compareRegToReg(CodeGen& codeGen, Registers reg1, ExtendedRegisters reg2);
		void compareRegToReg(CodeGen& codeGen, ExtendedRegisters reg1, Registers reg2);
		void compareRegToReg(CodeGen& codeGen, FloatRegisters reg1, FloatRegisters reg2);

		//Jumps to the target relative the current instruction
		void jump(CodeGen& codeGen, int target);

		//Jumps if equal to the target relative the current instruction
		void jumpEqual(CodeGen& codeGen, int target);

		//Jumps if not equal to the target relative the current instruction
		void jumpNotEqual(CodeGen& codeGen, int target);

		//Jumps if > to the target relative the current instruction
		void jumpGreaterThan(CodeGen& codeGen, int target);

		//Jumps if > to the target relative the current instruction. Uses unsigned comparison.
		void jumpGreaterThanUnsigned(CodeGen& codeGen, int target);

		//Jumps if >= to the target relative the current instruction
		void jumpGreaterThanOrEqual(CodeGen& codeGen, int target);

		//Jumps if >= to the target relative the current instruction. Uses unsigned comparison.
		void jumpGreaterThanOrEqualUnsigned(CodeGen& codeGen, int target);

		//Jumps if < to the target relative the current instruction
		void jumpLessThan(CodeGen& codeGen, int target);

		//Jumps if < to the target relative the current instruction. Uses unsigned comparison.
		void jumpLessThanUnsigned(CodeGen& codeGen, int target);

		//Jumps if <= to the target relative the current instruction
		void jumpLessThanOrEqual(CodeGen& codeGen, int target);

		//Jumps if <= to the target relative the current instruction. Uses unsigned comparison.
		void jumpLessThanOrEqualUnsigned(CodeGen& codeGen, int target);

		//Sign extends the RAX register
		void signExtend64(CodeGen& codeGen);

		//Sign extends the EAX register
		void signExtend32(CodeGen& codeGen);

		//Sign extends the AX register
		void signExtend16(CodeGen& codeGen);

		//Converts the second register to a float
		void convertIntToFloat(CodeGen& codeGen, FloatRegisters dest, Registers src);
		void convertIntToFloat(CodeGen& codeGen, FloatRegisters dest, ExtendedRegisters src);

		//Converts the second register to an int
		void convertFloatToInt(CodeGen& codeGen, Registers dest, FloatRegisters src);
		void convertFloatToInt(CodeGen& codeGen, ExtendedRegisters dest, FloatRegisters src);
	}
}
