#pragma once
#include <vector>
#include <deque>
#include <unordered_map>
#include <map>

class VMState;
struct Program;
struct Function;
struct Instruction;
class Type;

typedef int (*JitFunction)();
typedef std::pair<std::string, unsigned int> FunctionCall;

//Contains compilation data for a function
struct FunctionCompilationData {
	struct Function& Function; 															 //The function being jitted
	std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> BranchTable; //Branch sources and inst targets
	std::vector<unsigned int> InstructionNumMapping;									 //Mapping from instruction num to native instruction
	std::map<FunctionCall, std::string> CallTable;										 //The called functions
	std::vector<std::deque<Type*>> InstructionOperandTypes;							 	//The types of the operands for the instruction

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
	JitFunction generateFunction(FunctionCompilationData& function, VMState& vmState);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
}