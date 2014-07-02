#pragma once
#include <vector>

struct VMState;
struct Instruction;

void generateCode(std::vector<unsigned char>& generatedCode, VMState& vmState, const Instruction& inst);