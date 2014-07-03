#pragma once
#include <vector>

struct VMState;
struct Instruction;

typedef int (*JitFunction)();

JitFunction generateFunction(const std::vector<Instruction>& instructions, VMState& vmState);

void generateCode(std::vector<unsigned char>& generatedCode, VMState& vmState, const Instruction& inst);