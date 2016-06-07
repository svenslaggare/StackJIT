#pragma once
#include <vector>
#include <functional>
#include "amd64.h"

/**
 * Represents an int register
 */
class IntRegister {
private:
	bool mIsBase;
	Registers mBaseRegister;
	ExtendedRegisters mExtendedRegister;
public:
	IntRegister();

	//Creates a new base register
	IntRegister(Registers baseRegister);

	//Creates a new extended register
	IntRegister(ExtendedRegisters extendedRegister);

	//Indicates if the current register is base
	bool isBase() const;

	//Returns the base register
	Registers baseRegister() const;

	//Returns the extended register
	ExtendedRegisters extendedRegister() const;

	//Comparison operators
	bool operator==(const IntRegister& rhs) const;
	bool operator!=(const IntRegister& rhs) const;
};

/**
 * The hardware register types
 */
enum class HardwareRegisterTypes {
	Int,
	Float
};

/**
 * Represents a hardware register
 */
class HardwareRegister {
private:
	HardwareRegisterTypes mType;
	IntRegister mIntRegister;
	FloatRegisters mFloatRegister;
public:
	HardwareRegister();

	//Creates a new int register
	HardwareRegister(IntRegister intRegister);

	//Creates a new float register
	HardwareRegister(FloatRegisters floatRegister);

	//Returns the type of the register
	HardwareRegisterTypes type() const;

	//Returns the int register
	IntRegister intRegister() const;

	//Returns the float register
	FloatRegisters floatRegister() const;

	//Comparison operators
	bool operator==(const HardwareRegister& rhs) const;
	bool operator!=(const HardwareRegister& rhs) const;
};

/**
 * Represents a memory operand
 */
class MemoryOperand {
private:
	IntRegister mMemoryRegister;
	bool mHasOffset;
	int mOffset;
public:
	MemoryOperand();

	//Creates a new memory operand
	MemoryOperand(IntRegister memoryRegister);

	//Creates a new memory operand with an offset
	MemoryOperand(IntRegister memoryRegister, int offset);

	//Returns the register where the address is stored
	IntRegister memoryRegister() const;

	//Indicates if the operand has an offset
	bool hasOffset() const;

	//Returns the offset
	int offset() const;
};


/**
 * Represents an assembler for Amd64
 */
class Amd64Assembler {
private:
	const static bool DEFAULT_IS_32_BITS = false;

	std::vector<unsigned char>& mData;

	//Generates an instruction that takes two int registers
	void generateTwoRegistersInstruction(
		IntRegister op1,
		IntRegister op2,
		std::function<void (CodeGen&, Registers, Registers)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, ExtendedRegisters)> inst2,
		std::function<void (CodeGen&, Registers, ExtendedRegisters)> inst3,
		std::function<void (CodeGen&, ExtendedRegisters, Registers)> inst4);

	//Generates an instruction that takes one int register
	void generateOneRegisterInstruction(
		IntRegister op,
		std::function<void (CodeGen&, Registers)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters)> inst2);

	//Generates an instruction with one register and int constant
	template<typename T>
	void generateOneRegisterWithValueInstruction(
		IntRegister op,
		T value,
		std::function<void (CodeGen&, Registers, T)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, T)> inst2);

	//Generates an instruction with a register destination and memory source
	void generateSourceMemoryInstruction(
		IntRegister op1,
		MemoryOperand op2,
		std::function<void (CodeGen&, Registers, Registers, int)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, ExtendedRegisters, int)> inst2,
		std::function<void (CodeGen&, Registers, ExtendedRegisters, int)> inst3,
		std::function<void (CodeGen&, ExtendedRegisters, Registers, int)> inst4);
public:
	//Creates a new assembler using the underlying vector
	Amd64Assembler(std::vector<unsigned char>& data);

	//Adds the second register to the first
	void add(IntRegister destination, IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);
	void add(FloatRegisters destination, FloatRegisters source);

	//Adds the given constant to the given register
	void add(IntRegister destination, int value, bool is32Bits = DEFAULT_IS_32_BITS);

	//Subtracts the second register from the first
	void sub(IntRegister destination, IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);
	void sub(FloatRegisters destination, FloatRegisters source);

	//Subtracts the given constant from the given register
	void sub(IntRegister destination, int value, bool is32Bits = DEFAULT_IS_32_BITS);

	//Multiplies the second register to the first
	void mult(IntRegister destination, IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);
	void mult(FloatRegisters destination, FloatRegisters source);

	//Multiplies the given register by the given the given constant
	void mult(IntRegister destination, int value, bool is32Bits = DEFAULT_IS_32_BITS);

	//Multiplies the AX register by the first. This instruction also modifies the rdx register.
	void div(IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);
	void div(FloatRegisters destination, FloatRegisters source);

	//Moves the second register to the first
	void move(IntRegister destination, IntRegister source);

	//Moves the given constant to the given register
//	template<typename T>
//	void moveConstant(IntRegister destination, T value);

	//Moves the given 32-bits integer to the given register
	void moveInt(IntRegister destination, std::int32_t value);

	//Moves the given 64-bits integer to the given register
	void moveLong(IntRegister destination, std::int64_t value);

	//Moves the memory operand to the register
//	void move(IntRegister destination, MemoryOperand source);

	//Pushes the given int register
	void push(IntRegister intRegister);

	//Pushes the given float register
	void push(FloatRegisters floatRegister);

	//Pops the given int register
	void pop(IntRegister intRegister);

	//Pops the given float register
	void pop(FloatRegisters floatRegister);

	//Pops the top operand
	void pop();
};

template<typename T>
void Amd64Assembler::generateOneRegisterWithValueInstruction(
	IntRegister op,
	T value,
	std::function<void (CodeGen&, Registers, T)> inst1,
	std::function<void (CodeGen&, ExtendedRegisters, T)> inst2) {
	if (op.isBase()) {
		inst1(mData, op.baseRegister(), value);
	} else {
		inst2(mData, op.extendedRegister(), value);
	}
}

//template<>
//void Amd64Assembler::moveConstant<std::int32_t>(IntRegister destination, std::int32_t value) {
//	generateOneRegisterWithValueInstruction<std::int32_t>(
//		destination,
//		value,
//		[&](CodeGen& codeGen, Registers x, std::int32_t y) { Amd64Backend::moveIntToReg(codeGen, x, y); },
//		[&](CodeGen& codeGen, ExtendedRegisters x, std::int32_t y) { Amd64Backend::moveIntToReg(codeGen, x, y); });
//}
//
//template<>
//void Amd64Assembler::moveConstant<std::int64_t>(IntRegister destination, std::int64_t value) {
//	generateOneRegisterWithValueInstruction<std::int64_t >(
//		destination,
//		value,
//		[&](CodeGen& codeGen, Registers x, std::int64_t  y) { Amd64Backend::moveLongToReg(codeGen, x, y); },
//		[&](CodeGen& codeGen, ExtendedRegisters x, std::int64_t  y) { Amd64Backend::moveLongToReg(codeGen, x, y); });
//}