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
typedef std::pair<unsigned int, unsigned int> BranchTarget;

//Contains compilation data for a function
struct FunctionCompilationData {
	struct Function& function; 															 //The function being jitted
	std::unordered_map<unsigned int, BranchTarget> branchTable; 						 //Branch sources and inst targets
	std::vector<unsigned int> instructionNumMapping;									 //Mapping from instruction num to native instruction
	std::map<FunctionCall, std::string> callTable;										 //The called functions
	std::vector<std::deque<Type*>> instructionOperandTypes;							 	 //The types of the operands for the instruction
	std::vector<std::deque<Type*>> postInstructionOperandTypes;							 //The types of the operands after an instruction has been executed
	int operandStackSize;																 //The size of the operand stack

	FunctionCompilationData(struct Function& function)
		: function(function), operandStackSize(0)
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