#pragma once
#include <vector>

struct VMState;
struct Instruction;
struct Program;

typedef int (*JitFunction)();

JitFunction generateProgram(Program& program, VMState& vmState);

JitFunction generateFunction(const std::vector<Instruction>& instructions, VMState& vmState);

void generateCode(std::vector<unsigned char>& generatedCode, VMState& vmState, const Instruction& inst);