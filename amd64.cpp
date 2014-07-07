#include "amd64.h"
#include <vector>

void Amd64Backend::pushReg(CodeGen& codeGen, Registers reg) {
	codeGen.push_back(0x50 | reg);
}