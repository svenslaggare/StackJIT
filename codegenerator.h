#pragma once
#include <vector>
#include <map>

struct VMState;
struct Instruction;
struct Program;

typedef int (*JitFunction)();
typedef std::pair<std::string, unsigned int> FunctionCall;

//Represents an user defined function
struct Function {
	std::string Name;
	int NumArgs;
	std::map<FunctionCall, std::string> CallTable;
	std::vector<Instruction> Instructions;
	std::vector<unsigned char> GeneratedCode;
};

namespace CodeGenerator {
	//Generates a program
	JitFunction generateProgram(Program& program, VMState& vmState);

	//Generates a function
	JitFunction generateFunction(Function& function, const VMState& vmState);

	//Generates code for the given instruction
	void generateCode(Function& function, const VMState& vmState, const Instruction& inst);
}