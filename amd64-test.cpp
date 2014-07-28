#include "amd64.h"

#include <assert.h>
#include <vector>
#include <iostream>

void arrayAssert(const std::vector<unsigned char>& actual, const std::vector<unsigned char>& expected) {
	for (int i = 0; i < expected.size(); i++) {
		if (expected[i] != actual[i]) {
			std::cout << std::hex << "Expected '" << (int)expected[i] << "' but got '" << (int)actual[i] << "'." << std::endl;
			assert(true == false);
		}
	}
}

//Tests the push generator
void testPush() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::pushReg(generatedCode, Registers::AX);
	assert(generatedCode[0] == 0x50);
	generatedCode.clear();

	Amd64Backend::pushReg(generatedCode, Registers::CX);
	assert(generatedCode[0] == 0x51);
	generatedCode.clear();
} 

//Tests the pushInt generator
void testPushInt() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::pushInt(generatedCode, 4711);
	arrayAssert(generatedCode, { 0x68, 0x67, 0x12, 0x00, 0x00 });
	generatedCode.clear();
} 

//Tests the pop generator
void testPop() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::popReg(generatedCode, Registers::AX);
	assert(generatedCode[0] == 0x58);
	generatedCode.clear();

	Amd64Backend::popReg(generatedCode, Registers::CX);
	assert(generatedCode[0] == 0x59);
	generatedCode.clear();
} 

//Tests the moveRegToReg generator
void testMoveRegToReg() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::moveRegToReg(generatedCode, Registers::AX, Registers::AX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0xC0 });
	generatedCode.clear();

	Amd64Backend::moveRegToReg(generatedCode, Registers::AX, Registers::CX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0xC8 });
	generatedCode.clear();

	Amd64Backend::moveRegToReg(generatedCode, Registers::CX, Registers::CX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0xC9 });
	generatedCode.clear();
} 

//Tests the moveRegToMemory generator
void testMoveRegToMemory() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::moveRegToMemory(generatedCode, 0xfcdebc03, Registers::AX);
	arrayAssert(generatedCode, { 0x48, 0xA3, 0x03, 0xBC, 0xDE, 0xFC, 0x00, 0x00, 0x00, 0x00 });
	generatedCode.clear();
}

//Tests the moveMemoryToReg generator
void testMoveMemoryToReg() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::moveMemoryToReg(generatedCode, Registers::AX, 0xfcdebc03);
	arrayAssert(generatedCode, { 0x48, 0xA1, 0x03, 0xBC, 0xDE, 0xFC, 0x00, 0x00, 0x00, 0x00 });
	generatedCode.clear();
}

//Tests the moveMemoryByRegToReg generator
void testMoveMemoryByRegToReg() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::AX);
	arrayAssert(generatedCode, { 0x48, 0x8B, 0x00 });
	generatedCode.clear();

	Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::AX);
	arrayAssert(generatedCode, { 0x48, 0x8B, 0x08 });
	generatedCode.clear();

	Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::AX, Registers::CX);
	arrayAssert(generatedCode, { 0x48, 0x8B, 0x01 });
	generatedCode.clear();

	Amd64Backend::moveMemoryByRegToReg(generatedCode, Registers::CX, Registers::CX);
	arrayAssert(generatedCode, { 0x48, 0x8B, 0x09 });
	generatedCode.clear();
}

//Tests the moveRegToMemoryRegWithOffset generator
void testMoveRegToMemoryRegWithOffset() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, 4, Registers::AX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x40, 0x04 });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, -4, Registers::AX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x40, 0xFC });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::AX, -4, Registers::CX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x48, 0xFC });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::CX, -4, Registers::AX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x41, 0xFC });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::CX, -4, Registers::CX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x49, 0xFC });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::BP, -4, Registers::DI);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x7D, 0xFC });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::BP, -8, Registers::SI);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x75, 0xF8 });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::BP, -12, Registers::DX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x55, 0xF4 });
	generatedCode.clear();

	Amd64Backend::moveRegToMemoryRegWithOffset(generatedCode, Registers::BP, -16, Registers::CX);
	arrayAssert(generatedCode, { 0x48, 0x89, 0x4D, 0xF0 });
	generatedCode.clear();
}

//Tests the moveIntToReg generator
void testMoveIntToReg() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::moveIntToReg(generatedCode, Registers::AX, 4711);
	arrayAssert(generatedCode, { 0x48, 0xC7, 0xC0, 0x67, 0x12, 0x00, 0x00 });
	generatedCode.clear();

	Amd64Backend::moveIntToReg(generatedCode, Registers::CX, 4711);
	arrayAssert(generatedCode, { 0x48, 0xC7, 0xC1, 0x67, 0x12, 0x00, 0x00 });
	generatedCode.clear();
}

//Tests the moveLongToReg generator
void testMoveLongToReg() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::moveLongToReg(generatedCode, Registers::AX, 0x118d2cc5a);
	arrayAssert(generatedCode, { 0x48, 0xB8, 0x5A, 0xCC, 0xD2, 0x18, 0x01, 0x00, 0x00, 0x00 } );
	generatedCode.clear();

	Amd64Backend::moveLongToReg(generatedCode, Registers::CX, 0x118d2cc5a);
	arrayAssert(generatedCode, { 0x48, 0xB9, 0x5A, 0xCC, 0xD2, 0x18, 0x01, 0x00, 0x00, 0x00 });
	generatedCode.clear();
}

//Tests the callInReg generator
void testCallInReg() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::callInReg(generatedCode, Registers::AX);
	arrayAssert(generatedCode, { 0xFF, 0xD0 } );
	generatedCode.clear();
}

//Tests the ret generator
void testRet() {
	std::vector<unsigned char> generatedCode;
	Amd64Backend::ret(generatedCode);
	arrayAssert(generatedCode, { 0xC3 } );
}

int main() {
	std::cout << "Running amd64-test.." << std::endl;
	testPush();
	testPushInt();
	testPop();
	testMoveRegToReg();
	testMoveRegToMemory();
	testMoveMemoryToReg();
	testMoveMemoryByRegToReg();
	testMoveRegToMemoryRegWithOffset();
	testMoveIntToReg();
	testMoveLongToReg();
	testCallInReg();
	testRet();
	std::cout << "All tests passed." << std::endl;
	return 0;
}