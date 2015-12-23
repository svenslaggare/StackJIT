#include <cxxtest/TestSuite.h>
#include <vector>

#include "../src/compiler/amd64.h"

class Amd64Suite : public CxxTest::TestSuite {
public:
    //Tests pushReg
    void testPushReg() {
        CodeGen generatedCode;
        Amd64Backend::pushReg(generatedCode, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode[0], 0x50);
        generatedCode.clear();

        Amd64Backend::pushReg(generatedCode, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode[0], 0x51);
        generatedCode.clear();
    }

    //Tests pushInt
    void testPushInt() {
        CodeGen generatedCode;
        Amd64Backend::pushInt(generatedCode, 4711);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x68, 0x67, 0x12, 0x00, 0x00 }));
        generatedCode.clear();
    }

    //Tests pop
    void testPop() {
        CodeGen generatedCode;
        Amd64Backend::popReg(generatedCode, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode[0], 0x58);
        generatedCode.clear();

        Amd64Backend::popReg(generatedCode, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode[0], 0x59);
        generatedCode.clear();

        Amd64Backend::popReg(generatedCode, NumberedRegisters::R8);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x41, 0x58 }));
        generatedCode.clear();

        Amd64Backend::popReg(generatedCode, NumberedRegisters::R9);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x41, 0x59 }));
        generatedCode.clear();
    }

    //Tests moveRegToReg
    void testMoveRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::moveRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, Registers::AX, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0xC8 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, Registers::CX, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0xC9 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, Registers::AX, Registers::SP);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0xE0 } ));
        generatedCode.clear();

		Amd64Backend::moveRegToReg(generatedCode, Registers::SP, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0xC4 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, Registers::AX, NumberedRegisters::R8);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, Registers::AX, NumberedRegisters::R10);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0xD0 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, Registers::CX, NumberedRegisters::R8);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0xC1 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, Registers::CX, NumberedRegisters::R9);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0xC9 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, NumberedRegisters::R8, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x49, 0x89, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, NumberedRegisters::R8, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x49, 0x89, 0xC8 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, NumberedRegisters::R9, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x49, 0x89, 0xC9 }));
        generatedCode.clear();

        Amd64Backend::moveRegToReg(generatedCode, NumberedRegisters::R10, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x49, 0x89, 0xC2 }));
        generatedCode.clear();
    }

    //Tests moveRegToMemory
    void testMoveRegToMemory() {
        CodeGen generatedCode;
        Amd64Backend::moveRegToMemory(generatedCode, (unsigned char*)0xfcdebc03, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xA3, 0x03, 0xBC, 0xDE, 0xFC, 0x00, 0x00, 0x00, 0x00 }));
        generatedCode.clear();
    }

    //Tests moveMemoryToReg
    void testMoveMemoryToReg() {
        CodeGen generatedCode;
        Amd64Backend::moveMemoryToReg(generatedCode, Registers::AX, (unsigned char*)0xfcdebc03);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xA1, 0x03, 0xBC, 0xDE, 0xFC, 0x00, 0x00, 0x00, 0x00 }));
        generatedCode.clear();
    }

    //Tests moveMemoryByRegToReg
    void testMoveMemoryByRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x08 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x01 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x09 }));
        generatedCode.clear();

        // Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::R8, Registers::CX);
        // TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x8B, 0x01 }));
        // generatedCode.clear();

        // Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::R9);
        // TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x49, 0x8B, 0x01 }));
        // generatedCode.clear();
    }

    //Tests moveRegToMemoryRegWithCharOffset
    void testMoveRegToMemoryRegWithOffset() {
        CodeGen generatedCode;
        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::AX, 4, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x40, 0x04 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::AX, -4, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x40, 0xFC }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::AX, -4, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x48, 0xFC }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::CX, -4, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x41, 0xFC }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::CX, -4, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x49, 0xFC }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::BP, -4, Registers::DI);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x7D, 0xFC }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::BP, -8, Registers::SI);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x75, 0xF8 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::BP, -12, Registers::DX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x55, 0xF4 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::BP, -16, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x4D, 0xF0 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::SP, 8, Registers::AX);
		TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x44, 0x24, 0x08 }));
		generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::SP, 8, Registers::CX);
		TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x4C, 0x24, 0x08 }));
		generatedCode.clear();

        //Numbered registers
        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::BP, -16, NumberedRegisters::R8);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0x45, 0xF0 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::AX, -16, NumberedRegisters::R9);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0x48, 0xF0 }));
        generatedCode.clear();
    }

    //Tests moveRegToMemoryRegWithIntOffset
    void testMoveRegToMemoryRegWithIntOffset() {
        CodeGen generatedCode;
        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::BP, 1337, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x85, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::AX, 1337, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x88, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::CX, 1337, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x81, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::SP, 1337, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x89, 0x84, 0x24, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();
    }

    //Tests moveRegToMemoryRegWithIntOffset
    void testMoveNumeredRegToMemoryRegWithIntOffset() {
        CodeGen generatedCode;
        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::AX, 1337, NumberedRegisters::R8);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0x80, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::AX, 1337, NumberedRegisters::R9);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0x88, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::CX, 1337, NumberedRegisters::R9);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0x89, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::SP, 1337, NumberedRegisters::R9);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x4C, 0x89, 0x8C, 0x24, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();
    }

	//Tests moveMemoryRegWithCharOffsetToReg
    void testMoveMemoryRegWithOffsetToReg() {
		CodeGen generatedCode;
        Amd64Backend::moveMemoryRegWithCharOffsetToReg(generatedCode, Registers::AX, Registers::AX, 16);
		TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x40, 0x10 }));
		generatedCode.clear();

        Amd64Backend::moveMemoryRegWithCharOffsetToReg(generatedCode, Registers::AX, Registers::CX, 16);
		TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x41, 0x10 }));
		generatedCode.clear();

        Amd64Backend::moveMemoryRegWithCharOffsetToReg(generatedCode, Registers::CX, Registers::AX, 16);
		TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x48, 0x10 }));
		generatedCode.clear();

        Amd64Backend::moveMemoryRegWithCharOffsetToReg(generatedCode, Registers::AX, Registers::BP, 16);
		TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x45, 0x10 }));
		generatedCode.clear();

        Amd64Backend::moveMemoryRegWithCharOffsetToReg(generatedCode, Registers::AX, Registers::SP, 8);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x44, 0x24, 0x08 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryRegWithCharOffsetToReg(generatedCode, Registers::CX, Registers::SP, 8);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x4C, 0x24, 0x08 }));
        generatedCode.clear();
	}

    //Tests moveMemoryRegWithIntOffsetToReg
    void testMoveMemoryRegWithIntOffsetToReg() {
        CodeGen generatedCode;
        Amd64Backend::moveMemoryRegWithIntOffsetToReg(generatedCode, Registers::AX, Registers::AX, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x80, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryRegWithIntOffsetToReg(generatedCode, Registers::AX, Registers::CX, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x81, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryRegWithIntOffsetToReg(generatedCode, Registers::CX, Registers::AX, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x88, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryRegWithIntOffsetToReg(generatedCode, Registers::AX, Registers::BP, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x85, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryRegWithIntOffsetToReg(generatedCode, Registers::AX, Registers::SP, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x84, 0x24, 0x39, 0x05, 0x00, 0x00 } ));
        generatedCode.clear();

        Amd64Backend::moveMemoryRegWithIntOffsetToReg(generatedCode, Registers::CX, Registers::SP, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x8B, 0x8C, 0x24, 0x39, 0x05, 0x00, 0x00 } ));
        generatedCode.clear();
    }

    //Tests moveIntToReg
    void testMoveIntToReg() {
        CodeGen generatedCode;
        Amd64Backend::moveIntToReg(generatedCode, Registers::AX, 4711);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xC7, 0xC0, 0x67, 0x12, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveIntToReg(generatedCode, Registers::CX, 4711);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xC7, 0xC1, 0x67, 0x12, 0x00, 0x00 }));
        generatedCode.clear();
    }

    //Tests moveLongToReg
    void testMoveLongToReg() {
        CodeGen generatedCode;
        Amd64Backend::moveLongToReg(generatedCode, Registers::AX, 0x118d2cc5a);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xB8, 0x5A, 0xCC, 0xD2, 0x18, 0x01, 0x00, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveLongToReg(generatedCode, Registers::CX, 0x118d2cc5a);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xB9, 0x5A, 0xCC, 0xD2, 0x18, 0x01, 0x00, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveLongToReg(generatedCode, NumberedRegisters::R8, 0x118d2cc5a);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x49, 0xB8, 0x5A, 0xCC, 0xD2, 0x18, 0x01, 0x00, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveLongToReg(generatedCode, NumberedRegisters::R9, 0x118d2cc5a);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x49, 0xB9, 0x5A, 0xCC, 0xD2, 0x18, 0x01, 0x00, 0x00, 0x00 } ));
        generatedCode.clear();
    }

    //Tests moveMemoryByRegToReg
    void testMoveMemoryByRegToRegFloat() {
        CodeGen generatedCode;
        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM0, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM1, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x08 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM0, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x01 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM1, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x09 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM0, Registers::BP);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x45, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM1, Registers::BP);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x4D, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM0, Registers::SP);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x04, 0x24 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM1, Registers::SP);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x0C, 0x24 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM2, Registers::SP);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x14, 0x24 }));
        generatedCode.clear();

        Amd64Backend::moveMemoryByRegToReg(generatedCode, FloatRegisters::XMM3, Registers::SP);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x10, 0x1C, 0x24 }));
        generatedCode.clear();
    }

    //Tests the moveRegToMemoryRegWithCharOffset generator
    void testMoveRegToMemoryRegWithOffsetFloat() {
        CodeGen generatedCode;
        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::AX, 0, FloatRegisters::XMM0);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x40, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::AX, 0, FloatRegisters::XMM1);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x48, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::AX, 0, FloatRegisters::XMM3);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x58, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::CX, 0, FloatRegisters::XMM0);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x41, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::CX, 0, FloatRegisters::XMM1);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x49, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::CX, 0, FloatRegisters::XMM2);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x51, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::BP, 0, FloatRegisters::XMM2);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x55, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::SP, 0, FloatRegisters::XMM0);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x44, 0x24, 0x0 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::SP, 0, FloatRegisters::XMM1);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x4C, 0x24, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::SP, 0, FloatRegisters::XMM2);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x54, 0x24, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithCharOffset(generatedCode, Registers::SP, 0, FloatRegisters::XMM3);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x5C, 0x24, 0x00 }));
        generatedCode.clear();
    }

    //Tests the moveRegToMemoryRegWithIntOffset generator
    void testMoveRegToMemoryRegWithIntOffsetFloat() {
        CodeGen generatedCode;
        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::AX, 1337, FloatRegisters::XMM0);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x80, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::AX, 1337, FloatRegisters::XMM1);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x88, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::CX, 1337, FloatRegisters::XMM1);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x89, 0x39, 0x05, 0x00, 0x00 } ));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::SP, 1337, FloatRegisters::XMM0);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF3, 0x0F, 0x11, 0x84, 0x24, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::moveRegToMemoryRegWithIntOffset(generatedCode, Registers::SP, 1337, FloatRegisters::XMM2);
        TS_ASSERT_EQUALS(generatedCode, CodeGen( { 0xF3, 0x0F, 0x11, 0x94, 0x24, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();
    }


    //Tests the callInReg generator
    void testCallInReg() {
        CodeGen generatedCode;
        Amd64Backend::callInReg(generatedCode, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xFF, 0xD0 }) );
        generatedCode.clear();
    }

    //Tests the ret generator
    void testRet() {
        CodeGen generatedCode;
        Amd64Backend::ret(generatedCode);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xC3 }));
    }

    //Tests the addRegToReg generator
    void testAddRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x01, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x01, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::addRegToReg(generatedCode, Registers::BX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x01, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::addRegToReg(generatedCode, Registers::BX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x01, 0xDB }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x01, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::addRegToReg(generatedCode, Registers::AX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x01, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::addRegToReg(generatedCode, Registers::BX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x01, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::addRegToReg(generatedCode, Registers::BX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x01, 0xDB }));
        generatedCode.clear();
    }

    //Tests the addByteToReg generator
    void testAddByteToReg() {
        CodeGen generatedCode;
        Amd64Backend::addByteToReg(generatedCode, Registers::AX, 25);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x83, 0xC0, 0x19 }));
        generatedCode.clear();

        Amd64Backend::addByteToReg(generatedCode, Registers::BX, 25);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x83, 0xC3, 0x19 }));
        generatedCode.clear();

        Amd64Backend::addByteToReg(generatedCode, Registers::AX, 117);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x83, 0xC0, 0x75 }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::addByteToReg(generatedCode, Registers::AX, 25, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x83, 0xC0, 0x19 }));
        generatedCode.clear();

        Amd64Backend::addByteToReg(generatedCode, Registers::BX, 25, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x83, 0xC3, 0x19 }));
        generatedCode.clear();

        Amd64Backend::addByteToReg(generatedCode, Registers::AX, 117, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x83, 0xC0, 0x75 }));
        generatedCode.clear();
    }

    //Tests the addIntToReg generator
    void testAddIntToReg() {
        CodeGen generatedCode;
        Amd64Backend::addIntToReg(generatedCode, Registers::AX, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x05, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::addIntToReg(generatedCode, Registers::CX, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x81, 0xC1, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::addIntToReg(generatedCode, Registers::SP, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x81, 0xC4, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::addIntToReg(generatedCode, Registers::BX, 1337);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x81, 0xC3, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::addIntToReg(generatedCode, Registers::AX, 1337, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x05, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::addIntToReg(generatedCode, Registers::CX, 1337, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x81, 0xC1, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::addIntToReg(generatedCode, Registers::BX, 1337, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x81, 0xC3, 0x39, 0x05, 0x00, 0x00 }));
        generatedCode.clear();
    }

    //Tests the subRegFromReg generator
    void testSubRegFromReg() {
        CodeGen generatedCode;
        Amd64Backend::subRegFromReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x29, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::subRegFromReg(generatedCode, Registers::AX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x29, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::subRegFromReg(generatedCode, Registers::BX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x29, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::subRegFromReg(generatedCode, Registers::BX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x29, 0xDB }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::subRegFromReg(generatedCode, Registers::AX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x29, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::subRegFromReg(generatedCode, Registers::AX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x29, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::subRegFromReg(generatedCode, Registers::BX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x29, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::subRegFromReg(generatedCode, Registers::BX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x29, 0xDB }));
        generatedCode.clear();
    }

    //Tests the subByteToReg generator
    void testSubByteToReg() {
        CodeGen generatedCode;
        Amd64Backend::subByteFromReg(generatedCode, Registers::AX, 25);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x83, 0xE8, 0x19 }));
        generatedCode.clear();

        Amd64Backend::subByteFromReg(generatedCode, Registers::BX, 25);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x83, 0xEB, 0x19 }));
        generatedCode.clear();

        Amd64Backend::subByteFromReg(generatedCode, Registers::AX, 117);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x83, 0xE8, 0x75 }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::subByteFromReg(generatedCode, Registers::AX, 25, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x83, 0xE8, 0x19 }));
        generatedCode.clear();

        Amd64Backend::subByteFromReg(generatedCode, Registers::BX, 25, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x83, 0xEB, 0x19 }));
        generatedCode.clear();

        Amd64Backend::subByteFromReg(generatedCode, Registers::AX, 117, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x83, 0xE8, 0x75 }));
        generatedCode.clear();
    }

    //Tests the subIntFromReg generator
    void testSubIntFromReg() {
        CodeGen generatedCode;
        Amd64Backend::subIntFromReg(generatedCode, Registers::AX, 20000);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x2D, 0x20, 0x4E, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::subIntFromReg(generatedCode, Registers::BX, 20000);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x81, 0xEB, 0x20, 0x4E, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::subIntFromReg(generatedCode, Registers::SP, 20000);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x81, 0xEC, 0x20, 0x4E, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::subIntFromReg(generatedCode, Registers::CX, 30000);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x81, 0xE9, 0x30, 0x75, 0x00, 0x00 }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::subIntFromReg(generatedCode, Registers::AX, 20000, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x2D, 0x20, 0x4E, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::subIntFromReg(generatedCode, Registers::BX, 20000, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x81, 0xEB, 0x20, 0x4E, 0x00, 0x00 }));
        generatedCode.clear();

        Amd64Backend::subIntFromReg(generatedCode, Registers::CX, 30000, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x81, 0xE9, 0x30, 0x75, 0x00, 0x00 }));
        generatedCode.clear();
    }

    //Tests the multRegToReg generator
    void testMultRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::multRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x0F, 0xAF, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::multRegToReg(generatedCode, Registers::AX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x0F, 0xAF, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::multRegToReg(generatedCode, Registers::BX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x0F, 0xAF, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::multRegToReg(generatedCode, Registers::BX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x0F, 0xAF, 0xDB }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::multRegToReg(generatedCode, Registers::AX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x0F, 0xAF, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::multRegToReg(generatedCode, Registers::AX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x0F, 0xAF, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::multRegToReg(generatedCode, Registers::BX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x0F, 0xAF, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::multRegToReg(generatedCode, Registers::BX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x0F, 0xAF, 0xDB }));
        generatedCode.clear();
    }

    //Tests the divRegFromReg generator
    void testDivRegFromReg() {
        CodeGen generatedCode;
        Amd64Backend::divRegFromReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xF7, 0xF8 }));
        generatedCode.clear();

        Amd64Backend::divRegFromReg(generatedCode, Registers::AX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xF7, 0xFB }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::divRegFromReg(generatedCode, Registers::AX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF7, 0xF8 }));
        generatedCode.clear();

        Amd64Backend::divRegFromReg(generatedCode, Registers::AX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF7, 0xFB }));
        generatedCode.clear();
    }

    //Tests the andRegToReg generator
    void testAndRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::andRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x21, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::andRegToReg(generatedCode, Registers::AX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x21, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::andRegToReg(generatedCode, Registers::BX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x21, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::andRegToReg(generatedCode, Registers::BX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x21, 0xDB }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::andRegToReg(generatedCode, Registers::AX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x21, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::andRegToReg(generatedCode, Registers::AX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x21, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::andRegToReg(generatedCode, Registers::BX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x21, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::andRegToReg(generatedCode, Registers::BX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x21, 0xDB }));
        generatedCode.clear();
    }

    //Tests the orRegToReg generator
    void testOrRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::orRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x09, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::orRegToReg(generatedCode, Registers::AX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x09, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::orRegToReg(generatedCode, Registers::BX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x09, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::orRegToReg(generatedCode, Registers::BX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x09, 0xDB }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::orRegToReg(generatedCode, Registers::AX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x09, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::orRegToReg(generatedCode, Registers::AX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x09, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::orRegToReg(generatedCode, Registers::BX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x09, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::orRegToReg(generatedCode, Registers::BX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x09, 0xDB }));
        generatedCode.clear();
    }

    //Tests the xorRegToReg generator
    void testXorRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::xorRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x31, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::xorRegToReg(generatedCode, Registers::AX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x31, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::xorRegToReg(generatedCode, Registers::BX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x31, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::xorRegToReg(generatedCode, Registers::BX, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x31, 0xDB }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::xorRegToReg(generatedCode, Registers::AX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x31, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::xorRegToReg(generatedCode, Registers::AX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x31, 0xD8 }));
        generatedCode.clear();

        Amd64Backend::xorRegToReg(generatedCode, Registers::BX, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x31, 0xC3 }));
        generatedCode.clear();

        Amd64Backend::xorRegToReg(generatedCode, Registers::BX, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x31, 0xDB }));
        generatedCode.clear();
    }

    //Tests the notReg generator
    void testNotReg() {
        CodeGen generatedCode;
        Amd64Backend::notReg(generatedCode, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xF7, 0xD0 }));
        generatedCode.clear();

        Amd64Backend::notReg(generatedCode, Registers::BX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0xF7, 0xD3 }));
        generatedCode.clear();

        //32 bits
        Amd64Backend::notReg(generatedCode, Registers::AX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF7, 0xD0 }));
        generatedCode.clear();

        Amd64Backend::notReg(generatedCode, Registers::BX, true);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0xF7, 0xD3 }));
        generatedCode.clear();
    }

    //Tests the compareRegToReg generator
    void testCompareRegToReg() {
        CodeGen generatedCode;
        Amd64Backend::compareRegToReg(generatedCode, Registers::AX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x39, 0xC0 }));
        generatedCode.clear();

        Amd64Backend::compareRegToReg(generatedCode, Registers::AX, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x39, 0xC8 }));
        generatedCode.clear();

        Amd64Backend::compareRegToReg(generatedCode, Registers::CX, Registers::AX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x39, 0xC1 }));
        generatedCode.clear();

        Amd64Backend::compareRegToReg(generatedCode, Registers::CX, Registers::CX);
        TS_ASSERT_EQUALS(generatedCode, CodeGen({ 0x48, 0x39, 0xC9 }));
        generatedCode.clear();
    }
};