#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>

struct VMState;
struct Program;
struct Function;
struct Instruction;
enum Types : char;

typedef int (*JitFunction)();
typedef std::pair<std::string, unsigned int> FunctionCall;

//Contains compilation data for a function
struct FunctionCompilationData {
	Function& Function; 																 //The function being jitted
	std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> BranchTable; //Branch sources and inst targets
	std::vector<unsigned int> InstructionNumMapping;									 //Mapping from instruction num to native instruction
	std::map<FunctionCall, std::string> CallTable;										 //The called functions
	std::vector<std::stack<Types>> InstructionOperandTypes;								 //The types of the operands for the instruction

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
	JitFunction generateFunction(FunctionCompilationData& function, const VMState& vmState);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst);
}