#pragma once
#include <vector>

union IntToBytes {
    int IntValue;
    unsigned char ByteValues[sizeof(int)];
};

union LongToBytes {
    long LongValue;
    unsigned char ByteValues[sizeof(long)];
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
	DI = 0b111
};

typedef std::vector<unsigned char> CodeGen;

//Backend for AMD64
namespace Amd64Backend {
	//The size of a register
	const int REG_SIZE = 8;

	//Pushes the given register to the stack
	void pushReg(CodeGen&, Registers);

	//Pushes the given integer to the stack
	void pushInt(CodeGen&, int);

	//Pops from the stack to the given register
	void popReg(CodeGen&, Registers);

	//Moves the content from the second register to the first register
	void moveRegToReg(CodeGen&, Registers, Registers);

	//Moves the content from the register to the memory address
	void moveRegToMemory(CodeGen&, long, Registers);

	//Moves the content from given memory address to the register
	void moveMemoryToReg(CodeGen&, Registers, long);

	//Moves the content from memory where the address is in the second register to the first register
	void moveMemoryByRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//Moves the content from a register to memory where the address is in a register + offset
	void moveRegToMemoryRegWithOffset(CodeGen&, Registers, char, Registers);

	//Moves the given integer (32-bits) to the given register
	void moveIntToReg(CodeGen&, Registers, int);

	//Moves the given long (64-bits) to the given register
	void moveLongToReg(CodeGen&, Registers, long);

	//Calls the given function where the entry points is in a register
	void callInReg(CodeGen&, Registers);

	//Calls the given function
	void call(CodeGen&, int);

	//The return instructiom
	void ret(CodeGen&);

	//Adds the second register to the first
	void addRegToReg(CodeGen&, Registers, Registers, bool is32bits = false);

	//Adds the given byte to the given register
	void addByteToReg(CodeGen&, Registers, char, bool is32bits = false);

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

	//Jumps if >= to the target relative the current instruction
	void jumpGreaterThanOrEqual(CodeGen&, int);

	//Jumps if < to the target relative the current instruction
	void jumpLessThan(CodeGen&, int);

	//Jumps if <= to the target relative the current instruction
	void jumpLessThanOrEqual(CodeGen&, int);
}
