#pragma once
#include <vector>
#include <map>

struct VMState;
struct Program;
struct Function;
struct Instruction;

typedef int (*JitFunction)();
typedef std::pair<std::string, unsigned int> FunctionCall;

//The code generator
namespace CodeGenerator {
	//Generates a program
	JitFunction generateProgram(Program& program, VMState& vmState);

	//Generates a function
	JitFunction generateFunction(Function& function, const VMState& vmState);

	//Generates code for the given instruction
	void generateInstruction(Function& function, const VMState& vmState, const Instruction& inst);
}