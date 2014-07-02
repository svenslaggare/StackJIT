#pragma once
#include <vector>

struct VMState;
struct Instruction;

std::vector<unsigned char> generateProgram(const std::vector<Instruction>& instructions, VMState& vmState);

void generateCode(std::vector<unsigned char>& generatedCode, VMState& vmState, const Instruction& inst);