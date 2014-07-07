#pragma once
#include <vector>

//The registers
enum Registers {
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
	//Pushes the given register to the stack
	void pushReg(CodeGen&, Registers);

	//Pops from the stack to the given register
	void popReg(CodeGen&, Registers);

	//Moves the content from the second register to the first register
	void moveRegToReg(CodeGen&, Registers, Registers);

	//Moves the content from the register to the memory address
	void moveRegToMemory(CodeGen&, long, Registers);

	//Moves the content from given memory address to the register
	void moveMemoryToReg(CodeGen&, Registers, long);

	//Moves the content from memory where the address is in the second registet to the first register
	void moveMemoryByRegToReg(CodeGen&, Registers, Registers);

	//Moves the given integer (32-bits) to the given register
	void moveIntToReg(CodeGen&, Registers, int);

	//Moves the given long (64-bits) to the given register
	void moveLongToReg(CodeGen&, Registers, long);
}