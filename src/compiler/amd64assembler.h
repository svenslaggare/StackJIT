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
 * The data sizes for the memory instructions
 */
enum class DataSize {
	Size8,
	Size16,
	Size32,
	Size64,
};

/**
 * The jump condition
 */
enum class JumpCondition{
	Always,
	Equal,
	NotEqual,
	LessThan,
	LessThanOrEqual,
	GreaterThan,
	GreaterThanOrEqual
};

/**
 * Represents an assembler for Amd64
 */
class Amd64Assembler {
private:
	const static bool DEFAULT_IS_32_BITS = false;
	const static DataSize DEFAULT_MEMORY_DATA_SIZE = DataSize::Size64;

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

	//Generates an instruction with one memory operand and int constant
	template<typename T>
	void generateOneMemoryOperandWithValueInstruction(
		MemoryOperand op,
		T value,
		std::function<void (CodeGen&, Registers, int, T)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, int, T)> inst2);

	//Generates an instruction with a register destination and memory source
	void generateSourceMemoryInstruction(
		IntRegister op1,
		MemoryOperand op2,
		std::function<void (CodeGen&, Registers, Registers, int)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, ExtendedRegisters, int)> inst2,
		std::function<void (CodeGen&, Registers, ExtendedRegisters, int)> inst3,
		std::function<void (CodeGen&, ExtendedRegisters, Registers, int)> inst4);

	//Generates an instruction with a memory destination and register source
	void generateDestinationMemoryInstruction(
		MemoryOperand op1,
		IntRegister op2,
		std::function<void (CodeGen&, Registers, int, Registers)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, int, ExtendedRegisters)> inst2,
		std::function<void (CodeGen&, Registers, int, ExtendedRegisters)> inst3,
		std::function<void (CodeGen&, ExtendedRegisters, int, Registers)> inst4);
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

	//Divides the AX register by the first. This instruction also modifies the rdx register.
	void div(IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);

	//Divides the first register by the second
	void div(FloatRegisters destination, FloatRegisters source);

	//Applies bitwise AND between the given registers
	void bitwiseAnd(IntRegister destination, IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);

	//Applies bitwise AND between the given register and constant
	void bitwiseAnd(IntRegister destination, int value, bool is32Bits = DEFAULT_IS_32_BITS);

	//Applies bitwise OR between the given registers
	void bitwiseOr(IntRegister destination, IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);

	//Applies bitwise XOR between the given registers
	void bitwiseXor(IntRegister destination, IntRegister source, bool is32Bits = DEFAULT_IS_32_BITS);

	//Applies bitwise NOR to the given register
	void bitwiseNor(IntRegister intRegister, bool is32Bits = DEFAULT_IS_32_BITS);

	//Moves the second register to the first
	void move(IntRegister destination, IntRegister source);

	//Moves the given 32-bits integer to the given register
	void moveInt(IntRegister destination, std::int32_t value);

	//Moves the given 64-bits integer to the given register
	void moveLong(IntRegister destination, std::int64_t value);

	//Moves the memory operand to the register
	void move(IntRegister destination, MemoryOperand source, DataSize dataSize = DEFAULT_MEMORY_DATA_SIZE);
	void move(FloatRegisters destination, MemoryOperand source);

	//Moves the memory at the given address to the register. Only the RAX register is supported.
	void move(IntRegister destination, unsigned char* source);

	//Moves the register to the memory operand
	void move(MemoryOperand destination, IntRegister source, DataSize dataSize = DEFAULT_MEMORY_DATA_SIZE);
	void move(MemoryOperand destination, FloatRegisters source);

	//Moves the given into the memory operand
	void move(MemoryOperand destination, std::int32_t value);

	//Moves the given register to the given address. Only the RAX register is supported.
	void move(unsigned char* destination, IntRegister source);

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

	//Sign extends the given register of the given size. Only RAX register supported.
	void signExtend(IntRegister intRegister, DataSize dataSize);

	//Converts the source to an int
	void convert(IntRegister destination, FloatRegisters source);

	//Converts the source to a float
	void convert(FloatRegisters destination, IntRegister source);

	//Compares two registers
	void compare(IntRegister destination, IntRegister source);
	void compare(FloatRegisters destination, FloatRegisters source);

	//Jumps to the given target
	void jump(JumpCondition condition, int target, bool unsignedComparison = false);
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

template<typename T>
void Amd64Assembler::generateOneMemoryOperandWithValueInstruction(
	MemoryOperand op,
	T value,
	std::function<void (CodeGen&, Registers, int, T)> inst1,
	std::function<void (CodeGen&, ExtendedRegisters, int, T)> inst2) {
	if (op.memoryRegister().isBase()) {
		inst1(mData, op.memoryRegister().baseRegister(), op.offset(), value);
	} else {
		inst2(mData, op.memoryRegister().extendedRegister(), op.offset(), value);
	}
}