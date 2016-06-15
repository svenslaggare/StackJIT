#include "amd64assembler.h"

namespace stackjit {
	//Int register
	IntRegister::IntRegister()
		:	mIsBase(true),
			mBaseRegister(Registers::AX),
			mExtendedRegister(ExtendedRegisters::R8){

	}

	IntRegister::IntRegister(Registers baseRegister)
		: mIsBase(true),
		  mBaseRegister(baseRegister),
	      mExtendedRegister(ExtendedRegisters::R8) {

	}

	IntRegister::IntRegister(ExtendedRegisters extendedRegister)
		: mIsBase(false),
		  mBaseRegister(Registers::AX),
		  mExtendedRegister(extendedRegister) {

	}

	bool IntRegister::isBase() const {
		return mIsBase;
	}

	Registers IntRegister::baseRegister() const {
		return mBaseRegister;
	}

	ExtendedRegisters IntRegister::extendedRegister() const {
		return mExtendedRegister;
	}

	bool IntRegister::operator==(const IntRegister& rhs) const {
		if (mIsBase != rhs.mIsBase) {
			return false;
		}

		if (mIsBase) {
			return mBaseRegister == rhs.mBaseRegister;
		} else {
			return mExtendedRegister == rhs.mExtendedRegister;
		}
	}

	bool IntRegister::operator!=(const IntRegister& rhs) const {
		return !(*this == rhs);
	}

	HardwareRegister::HardwareRegister()
		: mType(HardwareRegisterTypes::Int),
	      mIntRegister(IntRegister()),
	      mFloatRegister(FloatRegisters::XMM0) {

	}

	HardwareRegister::HardwareRegister(IntRegister intRegister)
		: mType(HardwareRegisterTypes::Int),
		  mIntRegister(intRegister),
		  mFloatRegister(FloatRegisters::XMM0){

	}

	HardwareRegister::HardwareRegister(FloatRegisters floatRegister)
		: mType(HardwareRegisterTypes::Float),
		  mIntRegister(IntRegister()),
		  mFloatRegister(floatRegister) {

	}

	HardwareRegisterTypes HardwareRegister::type() const {
		return mType;
	}

	IntRegister HardwareRegister::intRegister() const {
		return mIntRegister;
	}

	FloatRegisters HardwareRegister::floatRegister() const {
		return mFloatRegister;
	}

	bool HardwareRegister::operator==(const HardwareRegister& rhs) const {
		if (mType != rhs.mType) {
			return false;
		}

		if (mType == HardwareRegisterTypes::Int) {
			return mIntRegister == rhs.mIntRegister;
		} else {
			return mFloatRegister == rhs.mFloatRegister;
		}
	}

	bool HardwareRegister::operator!=(const HardwareRegister& rhs) const {
		return !(*this == rhs);
	}

	//Memory operand
	MemoryOperand::MemoryOperand()
		: mMemoryRegister(IntRegister()),
		  mHasOffset(false),
		  mOffset(0) {

	}

	MemoryOperand::MemoryOperand(IntRegister memoryRegister)
		: mMemoryRegister(memoryRegister),
		  mHasOffset(false),
		  mOffset(0){

	}

	MemoryOperand::MemoryOperand(IntRegister memoryRegister, int offset)
		: mMemoryRegister(memoryRegister),
		  mHasOffset(true),
		  mOffset(offset){

	}

	IntRegister MemoryOperand::memoryRegister() const {
		return mMemoryRegister;
	}

	bool MemoryOperand::hasOffset() const {
		return mHasOffset;
	}

	int MemoryOperand::offset() const {
		return mOffset;
	}

	//Amd64 assembler
	Amd64Assembler::Amd64Assembler(std::vector<unsigned char>& data)
		: mData(data) {

	}

	void Amd64Assembler::generateTwoRegistersInstruction(
		IntRegister op1,
		IntRegister op2,
		std::function<void (CodeGen&, Registers, Registers)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, ExtendedRegisters)> inst2,
		std::function<void (CodeGen&, Registers, ExtendedRegisters)> inst3,
		std::function<void (CodeGen&, ExtendedRegisters, Registers)> inst4) {
		if (op1.isBase() && op2.isBase()) {
			inst1(mData, op1.baseRegister(), op2.baseRegister());
		} else if (!op1.isBase() && !op2.isBase()){
			inst2(mData, op1.extendedRegister(), op2.extendedRegister());
		} else if (op1.isBase() && !op2.isBase()) {
			inst3(mData, op1.baseRegister(), op2.extendedRegister());
		} else {
			inst4(mData, op1.extendedRegister(), op2.baseRegister());
		}
	}

	void Amd64Assembler::generateOneRegisterInstruction(
		IntRegister op,
		std::function<void (CodeGen&, Registers)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters)> inst2) {
		if (op.isBase()) {
			inst1(mData, op.baseRegister());
		} else {
			inst2(mData, op.extendedRegister());
		}
	}

	void Amd64Assembler::generateSourceMemoryInstruction(
		IntRegister op1,
		MemoryOperand op2,
		std::function<void (CodeGen&, Registers, Registers, int)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, ExtendedRegisters, int)> inst2,
		std::function<void (CodeGen&, Registers, ExtendedRegisters, int)> inst3,
		std::function<void (CodeGen&, ExtendedRegisters, Registers, int)> inst4)	{
		if (op1.isBase() && op2.memoryRegister().isBase()) {
			inst1(mData, op1.baseRegister(), op2.memoryRegister().baseRegister(), op2.offset());
		} else if (!op1.isBase() && !op2.memoryRegister().isBase()) {
			inst2(mData, op1.extendedRegister(), op2.memoryRegister().extendedRegister(), op2.offset());
		} else if(op1.isBase() && !op2.memoryRegister().isBase())		{
			inst3(mData, op1.baseRegister(), op2.memoryRegister().extendedRegister(), op2.offset());
		} else {
			inst4(mData, op1.extendedRegister(), op2.memoryRegister().baseRegister(), op2.offset());
		}
	}

	void Amd64Assembler::generateDestinationMemoryInstruction(
		MemoryOperand op1,
		IntRegister op2,
		std::function<void (CodeGen&, Registers, int, Registers)> inst1,
		std::function<void (CodeGen&, ExtendedRegisters, int, ExtendedRegisters)> inst2,
		std::function<void (CodeGen&, Registers, int, ExtendedRegisters)> inst3,
		std::function<void (CodeGen&, ExtendedRegisters, int, Registers)> inst4) {
		if (op1.memoryRegister().isBase() && op2.isBase()) {
			inst1(mData, op1.memoryRegister().baseRegister(), op1.offset(), op2.baseRegister());
		} else if (!op1.memoryRegister().isBase() && !op2.isBase()) {
			inst2(mData, op1.memoryRegister().extendedRegister(), op1.offset(), op2.extendedRegister());
		} else if (op1.memoryRegister().isBase() && !op2.isBase()) {
			inst3(mData, op1.memoryRegister().baseRegister(), op1.offset(), op2.extendedRegister());
		} else {
			inst4(mData, op1.memoryRegister().extendedRegister(), op1.offset(), op2.baseRegister());
		}
	}

	void Amd64Assembler::add(IntRegister destination, IntRegister source, bool is32Bits) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::addRegToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::addRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::addRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::addRegToReg(codeGen, x, y); });
	}

	void Amd64Assembler::add(FloatRegisters destination, FloatRegisters source) {
		Amd64Backend::addRegToReg(mData, destination, source);
	}

	void Amd64Assembler::add(IntRegister destination, int value, bool is32Bits) {
		generateOneRegisterWithValueInstruction<int>(
			destination,
			value,
			[&](CodeGen& codeGen, Registers x, int y) { Amd64Backend::addConstantToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, int y) { Amd64Backend::addConstantToReg(codeGen, x, y); });
	}

	void Amd64Assembler::sub(IntRegister destination, IntRegister source, bool is32Bits) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::subRegFromReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::subRegFromReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::subRegFromReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::subRegFromReg(codeGen, x, y); });
	}

	void Amd64Assembler::sub(FloatRegisters destination, FloatRegisters source) {
		Amd64Backend::subRegFromReg(mData, destination, source);
	}

	void Amd64Assembler::sub(IntRegister destination, int value, bool is32Bits) {
		generateOneRegisterWithValueInstruction<int>(
			destination,
			value,
			[&](CodeGen& codeGen, Registers x, int y) { Amd64Backend::subConstantFromReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, int y) { Amd64Backend::subConstantFromReg(codeGen, x, y); });
	}

	void Amd64Assembler::mult(IntRegister destination, IntRegister source, bool is32Bits) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::multRegToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::multRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::multRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::multRegToReg(codeGen, x, y); });
	}

	void Amd64Assembler::mult(FloatRegisters destination, FloatRegisters source) {
		Amd64Backend::multRegToReg(mData, destination, source);
	}

	void Amd64Assembler::mult(IntRegister destination, int value, bool is32Bits) {
		generateOneRegisterWithValueInstruction<int>(
			destination,
			value,
			[&](CodeGen& codeGen, Registers x, int y) { Amd64Backend::multConstantToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, int y) { Amd64Backend::multConstantToReg(codeGen, x, y); });
	}

	void Amd64Assembler::div(IntRegister source, bool is32Bits) {
		if (source.isBase()) {
			Amd64Backend::divRegFromReg(mData, Registers::AX, source.baseRegister(), is32Bits);
		} else {
			Amd64Backend::divRegFromReg(mData, Registers::AX, source.extendedRegister());
		}
	}

	void Amd64Assembler::div(FloatRegisters destination, FloatRegisters source) {
		Amd64Backend::divRegFromReg(mData, destination, source);
	}

	void Amd64Assembler::bitwiseAnd(IntRegister destination, IntRegister source, bool is32Bits) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::andRegToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::andRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::andRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::andRegToReg(codeGen, x, y); });
	}

	void Amd64Assembler::bitwiseAnd(IntRegister destination, int value, bool is32Bits) {
		generateOneRegisterWithValueInstruction<std::int32_t>(
			destination,
			value,
			[&](CodeGen& codeGen, Registers x, std::int32_t y) { Amd64Backend::andIntToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, std::int32_t y) { Amd64Backend::andIntToReg(codeGen, x, y); });
	}

	void Amd64Assembler::bitwiseOr(IntRegister destination, IntRegister source, bool is32Bits) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::orRegToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::orRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::orRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::orRegToReg(codeGen, x, y); });
	}

	void Amd64Assembler::bitwiseXor(IntRegister destination, IntRegister source, bool is32Bits) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::xorRegToReg(codeGen, x, y, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::xorRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::xorRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::xorRegToReg(codeGen, x, y); });
	}

	void Amd64Assembler::bitwiseNor(IntRegister intRegister, bool is32Bits) {
		generateOneRegisterInstruction(
			intRegister,
			[&](CodeGen& codeGen, Registers x) { Amd64Backend::notReg(codeGen, x, is32Bits); },
			[&](CodeGen& codeGen, ExtendedRegisters x) { Amd64Backend::notReg(codeGen, x); });
	}

	void Amd64Assembler::move(IntRegister destination, IntRegister source) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::moveRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::moveRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::moveRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::moveRegToReg(codeGen, x, y); });
	}

	void Amd64Assembler::moveInt(IntRegister destination, std::int32_t value) {
		generateOneRegisterWithValueInstruction<std::int32_t>(
			destination,
			value,
			[&](CodeGen& codeGen, Registers x, std::int32_t y) { Amd64Backend::moveIntToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, std::int32_t y) { Amd64Backend::moveIntToReg(codeGen, x, y); });
	}

	void Amd64Assembler::moveLong(IntRegister destination, std::int64_t value) {
		generateOneRegisterWithValueInstruction<std::int64_t >(
			destination,
			value,
			[&](CodeGen& codeGen, Registers x, std::int64_t  y) { Amd64Backend::moveLongToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, std::int64_t  y) { Amd64Backend::moveLongToReg(codeGen, x, y); });
	}

	void Amd64Assembler::move(IntRegister destination, MemoryOperand source, DataSize dataSize) {
		switch (dataSize) {
			case DataSize::Size8:
				throw std::runtime_error("Not supported");
			case DataSize::Size16:
				throw std::runtime_error("Not implemented");
			case DataSize::Size32:
				if (source.hasOffset()) {
					generateSourceMemoryInstruction(
						destination,
						source,
						[&](CodeGen& codeGen, Registers dest, Registers src, int offset) {
							Amd64Backend::moveMemoryRegWithIntOffsetToReg(codeGen, dest, src, offset, true);
						},
						[&](CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src, int offset) {
							throw std::runtime_error("Not supported");
						},
						[&](CodeGen& codeGen, Registers dest, ExtendedRegisters src, int offset) {
							Amd64Backend::moveMemoryRegWithIntOffsetToReg(codeGen, dest, src, offset, true);
						},
						[&](CodeGen& codeGen, ExtendedRegisters dest, Registers src, int offset) {
							throw std::runtime_error("Not supported");
						});
				} else {
					generateTwoRegistersInstruction(
						destination,
						source.memoryRegister(),
						[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::moveMemoryByRegToReg(codeGen, x, y, true); },
						[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) {
							throw std::runtime_error("Not supported");
						},
						[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::moveMemoryByRegToReg(codeGen, x, y, true); },
						[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) {
							throw std::runtime_error("Not supported");
						});
				}
				break;
			case DataSize::Size64:
				if (source.hasOffset()) {
					generateSourceMemoryInstruction(
						destination,
						source,
						[&](CodeGen& codeGen, Registers dest, Registers src, int offset) {
							Amd64Backend::moveMemoryRegWithOffsetToReg(codeGen, dest, src, offset);
						},
						[&](CodeGen& codeGen, ExtendedRegisters dest, ExtendedRegisters src, int offset) {
							Amd64Backend::moveMemoryRegWithIntOffsetToReg(codeGen, dest, src, offset);
						},
						[&](CodeGen& codeGen, Registers dest, ExtendedRegisters src, int offset) {
							Amd64Backend::moveMemoryRegWithIntOffsetToReg(codeGen, dest, src, offset);
						},
						[&](CodeGen& codeGen, ExtendedRegisters dest, Registers src, int offset) {
							Amd64Backend::moveMemoryRegWithIntOffsetToReg(codeGen, dest, src, offset);
						});
				} else {
					generateTwoRegistersInstruction(
						destination,
						source.memoryRegister(),
						[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::moveMemoryByRegToReg(codeGen, x, y); },
						[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::moveMemoryByRegToReg(codeGen, x, y); },
						[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::moveMemoryByRegToReg(codeGen, x, y); },
						[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::moveMemoryByRegToReg(codeGen, x, y); });
				}
				break;
		}
	}

	void Amd64Assembler::move(Register8Bits destination, MemoryOperand source) {
		generateSourceMemoryInstruction<Register8Bits>(
			destination,
			source,
			[&](CodeGen& codeGen, Register8Bits dest, Registers src, int offset) {
				Amd64Backend::moveMemoryRegWithIntOffsetToReg(mData, dest, src, offset);
			},
			[&](CodeGen& codeGen, Register8Bits dest, ExtendedRegisters src, int offset) {
				Amd64Backend::moveMemoryRegWithIntOffsetToReg(mData, dest, src, offset);
			});
	}

	void Amd64Assembler::move(FloatRegisters destination, MemoryOperand source) {
		generateSourceMemoryInstruction<FloatRegisters>(
			destination,
			source,
			[&](CodeGen& codeGen, FloatRegisters dest, Registers src, int offset) {
				Amd64Backend::moveMemoryRegWithIntOffsetToReg(mData, dest, src, offset);
			},
			[&](CodeGen& codeGen, FloatRegisters dest, ExtendedRegisters src, int offset) {
				Amd64Backend::moveMemoryRegWithIntOffsetToReg(mData, dest, src, offset);
			});
	}

	void Amd64Assembler::move(IntRegister destination, unsigned char* source) {
		if (!destination.isBase()) {
			throw std::runtime_error("Extended registers not supported");
		}

		Amd64Backend::moveMemoryToReg(
			mData,
			destination.baseRegister(),
			source);
	}

	void Amd64Assembler::move(MemoryOperand destination, IntRegister source, DataSize dataSize) {
		switch (dataSize) {
			case DataSize::Size8:
				throw std::runtime_error("Not supported");
			case DataSize::Size16:
				throw std::runtime_error("Not implemented");
			case DataSize::Size32:
				generateDestinationMemoryInstruction(
					destination,
					source,
					[&](CodeGen& codeGen, Registers dest, int offset, Registers src) {
						Amd64Backend::moveRegToMemoryRegWithOffset(codeGen, dest, offset, src, true);
					},
					[&](CodeGen& codeGen, ExtendedRegisters dest, int offset, ExtendedRegisters src) {
						throw std::runtime_error("Not supported");
					},
					[&](CodeGen& codeGen, Registers dest, int offset, ExtendedRegisters src) {
						throw std::runtime_error("Not supported");
					},
					[&](CodeGen& codeGen, ExtendedRegisters dest, int offset, Registers src) {
						Amd64Backend::moveRegToMemoryRegWithIntOffset(codeGen, dest, offset, src, true);
					});
				break;
			case DataSize::Size64:
				generateDestinationMemoryInstruction(
					destination,
					source,
					[&](CodeGen& codeGen, Registers dest, int offset, Registers src) {
						Amd64Backend::moveRegToMemoryRegWithOffset(codeGen, dest, offset, src);
					},
					[&](CodeGen& codeGen, ExtendedRegisters dest, int offset, ExtendedRegisters src) {
						Amd64Backend::moveRegToMemoryRegWithIntOffset(codeGen, dest, offset, src);
					},
					[&](CodeGen& codeGen, Registers dest, int offset, ExtendedRegisters src) {
						Amd64Backend::moveRegToMemoryRegWithOffset(codeGen, dest, offset, src);
					},
					[&](CodeGen& codeGen, ExtendedRegisters dest, int offset, Registers src) {
						Amd64Backend::moveRegToMemoryRegWithIntOffset(codeGen, dest, offset, src);
					});
				break;
		}
	}

	void Amd64Assembler::move(MemoryOperand destination, Register8Bits source) {
		generateDestinationMemoryInstruction<Register8Bits>(
			destination,
			source,
			[&](CodeGen& codeGen, Registers dest, int offset, Register8Bits src) {
				Amd64Backend::moveRegToMemoryRegWithIntOffset(codeGen, dest, offset, src);
			},
			[&](CodeGen& codeGen, ExtendedRegisters dest, int offset, Register8Bits src) {
				Amd64Backend::moveRegToMemoryRegWithIntOffset(codeGen, dest, offset, src);
			});
	}

	void Amd64Assembler::move(MemoryOperand destination, FloatRegisters source) {
		generateDestinationMemoryInstruction<FloatRegisters>(
			destination,
			source,
			[&](CodeGen& codeGen, Registers dest, int offset, FloatRegisters src) {
				Amd64Backend::moveRegToMemoryRegWithIntOffset(codeGen, dest, offset, src);
			},
			[&](CodeGen& codeGen, ExtendedRegisters dest, int offset, FloatRegisters src) {
				Amd64Backend::moveRegToMemoryRegWithIntOffset(codeGen, dest, offset, src);
			});
	}

	void Amd64Assembler::move(MemoryOperand destination, std::int32_t value) {
		generateOneMemoryOperandWithValueInstruction<std::int32_t>(
			destination,
			value,
			[&](CodeGen& codeGen, Registers dest, int offset, std::int32_t x) { Amd64Backend::moveIntToMemoryRegWithIntOffset(codeGen, dest, offset, x); },
			[&](CodeGen& codeGen, ExtendedRegisters dest, int offset, std::int32_t x) { Amd64Backend::moveIntToMemoryRegWithIntOffset(codeGen, dest, offset, x); });
	}

	void Amd64Assembler::move(unsigned char* destination, IntRegister source) {
		if (!source.isBase()) {
			throw std::runtime_error("Extended registers not supported");
		}

		Amd64Backend::moveRegToMemory(
			mData,
			destination,
			source.baseRegister());
	}

	void Amd64Assembler::push(IntRegister intRegister) {
		generateOneRegisterInstruction(
			intRegister,
			[&](CodeGen& codeGen, Registers x) { Amd64Backend::pushReg(codeGen, x); },
			[&](CodeGen& codeGen, ExtendedRegisters x) { Amd64Backend::pushReg(codeGen, x); });
	}

	void Amd64Assembler::push(FloatRegisters floatRegister) {
		Amd64Backend::pushReg(mData, floatRegister);
	}

	void Amd64Assembler::pop(IntRegister intRegister) {
		generateOneRegisterInstruction(
			intRegister,
			[&](CodeGen& codeGen, Registers x) { Amd64Backend::popReg(codeGen, x); },
			[&](CodeGen& codeGen, ExtendedRegisters x) { Amd64Backend::popReg(codeGen, x); });
	}

	void Amd64Assembler::pop(FloatRegisters floatRegister) {
		Amd64Backend::popReg(mData, floatRegister);
	}

	void Amd64Assembler::pop() {
		Amd64Backend::addByteToReg(mData, Registers::SP, Amd64Backend::REGISTER_SIZE);
	}

	void Amd64Assembler::signExtend(IntRegister intRegister, DataSize dataSize) {
		if (!intRegister.isBase()) {
			throw std::runtime_error("Extended registers not supported");
		}

		switch (dataSize) {
			case DataSize::Size8:
				throw std::runtime_error("Not supported");
			case DataSize::Size16:
				Amd64Backend::signExtend16(mData);
				break;
			case DataSize::Size32:
				Amd64Backend::signExtend32(mData);
				break;
			case DataSize::Size64:
				Amd64Backend::signExtend64(mData);
				break;
		}
	}

	void Amd64Assembler::convert(IntRegister destination, FloatRegisters source) {
		//cvttss2si rax, xmm0
		if (destination.isBase()) {
			Amd64Backend::convertFloatToInt(mData, destination.baseRegister(), source);
		} else {
			Amd64Backend::convertFloatToInt(mData, destination.extendedRegister(), source);
		}
	}

	void Amd64Assembler::convert(FloatRegisters destination, IntRegister source) {
		//cvtsi2ss xmm0, rax
		if (source.isBase()) {
			Amd64Backend::convertIntToFloat(mData, destination, source.baseRegister());
		} else {
			Amd64Backend::convertIntToFloat(mData, destination, source.extendedRegister());
		}
	}

	void Amd64Assembler::compare(IntRegister destination, IntRegister source) {
		generateTwoRegistersInstruction(
			destination,
			source,
			[&](CodeGen& codeGen, Registers x, Registers y) { Amd64Backend::compareRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, ExtendedRegisters y) { Amd64Backend::compareRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, Registers x, ExtendedRegisters y) { Amd64Backend::compareRegToReg(codeGen, x, y); },
			[&](CodeGen& codeGen, ExtendedRegisters x, Registers y) { Amd64Backend::compareRegToReg(codeGen, x, y); });
	}

	void Amd64Assembler::compare(FloatRegisters destination, FloatRegisters source) {
		//ucomiss xmm0, xmm1
		Amd64Backend::compareRegToReg(mData, destination, source);
	}

	void Amd64Assembler::jump(JumpCondition condition, int target, bool unsignedComparison) {
		switch (condition) {
			case JumpCondition::Always:
				Amd64Backend::jump(mData, target);
				break;
			case JumpCondition::Equal:
				Amd64Backend::jumpEqual(mData, target);
				break;
			case JumpCondition::NotEqual:
				Amd64Backend::jumpNotEqual(mData, target);
				break;
			case JumpCondition::LessThan:
				if (unsignedComparison) {
					Amd64Backend::jumpLessThanUnsigned(mData, target);
				}
				else {
					Amd64Backend::jumpLessThan(mData, target);
				}
				break;
			case JumpCondition::LessThanOrEqual:
				if (unsignedComparison) {
					Amd64Backend::jumpLessThanOrEqualUnsigned(mData, target);
				} else {
					Amd64Backend::jumpLessThanOrEqual(mData, target);
				}
				break;
			case JumpCondition::GreaterThan:
				if (unsignedComparison) {
					Amd64Backend::jumpGreaterThanUnsigned(mData, target);
				} else {
					Amd64Backend::jumpGreaterThan(mData, target);
				}
				break;
			case JumpCondition::GreaterThanOrEqual:
				if (unsignedComparison) {
					Amd64Backend::jumpGreaterThanOrEqualUnsigned(mData, target);
				} else {
					Amd64Backend::jumpGreaterThanOrEqual(mData, target);
				}
				break;
		}
	}

	void Amd64Assembler::call(IntRegister intRegister) {
		generateOneRegisterInstruction(
			intRegister,
			[&](CodeGen& codeGen, Registers reg) { Amd64Backend::callInReg(mData, reg);	},
			[&](CodeGen& codeGen, ExtendedRegisters reg) { Amd64Backend::callInReg(mData, reg);	});
	}

	void Amd64Assembler::call(int relativeAddress) {
		Amd64Backend::call(mData, relativeAddress);
	}

	void Amd64Assembler::ret() {
		Amd64Backend::ret(mData);
	}
}
