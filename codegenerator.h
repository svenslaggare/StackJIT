#pragma once
#include <vector>
#include <map>

struct VMState;
struct Instruction;
struct Program;

typedef int (*JitFunction)();
typedef std::pair<std::string, unsigned int> FunctionCall;

struct Function {
	std::string Name;
	std::map<FunctionCall, std::string> CallTable;
	std::vector<Instruction> Instructions;
	std::vector<unsigned char> GeneratedCode;
};

JitFunction generateProgram(Program& program, VMState& vmState);

JitFunction generateFunction(Function& function, VMState& vmState);

void generateCode(Function& function, VMState& vmState, const Instruction& inst);