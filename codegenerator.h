#pragma once
#include <vector>
#include <map>
#include <unordered_map>

struct VMState;
struct Program;
struct Function;
struct Instruction;

typedef int (*JitFunction)();
typedef std::pair<std::string, unsigned int> FunctionCall;

//Contains compilation data for a function
struct FunctionCompilationData {
	Function& Function; 																 //The function being jitted
	std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> BranchTable; //Branch sources and inst targets
	std::vector<unsigned int> InstructionNumMapping;									 //Mapping from instruction num to native instruction

	FunctionCompilationData(struct Function& function)
		: Function(function)
	{

	}
};

//The code generator
namespace CodeGenerator {
	//Generates a program
	JitFunction generateProgram(Program& program, VMState& vmState);

	//Generates a function
	JitFunction generateFunction(Function& function, const VMState& vmState);

	//Generates code for the given instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst);
}