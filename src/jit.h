#pragma once
#include <unordered_map>

class VMState;
class Function;

//Represents a jitted function
typedef void (*JitFunction)();

typedef std::pair<std::string, unsigned int> FunctionCall;
typedef std::pair<unsigned int, unsigned int> BranchTarget;

//Holds compilation data for a function
struct FunctionCompilationData {
	Function& function;

	//Unresolved branches
	std::unordered_map<unsigned int, BranchTarget> branchTable;

	//Mapping from instruction num to native instruction
	std::vector<unsigned int> instructionNumMapping;			

	//Unresolved function calls						 
	std::map<FunctionCall, std::string> callTable;

	//The types of the operands for the instruction
	std::vector<std::deque<const Type*>> preInstructionOperandTypes;

	//The types of the operands after an instruction has been executed
	std::vector<std::deque<const Type*>> postInstructionOperandTypes;

	//The size of the operand stack
	int operandStackSize;

	//Holds compilation data for the given function
	FunctionCompilationData(Function& function);
};

//Represents the JIT compiler
class JITCompiler {
private:
	VMState& mVMState;
	std::unordered_map<std::string, FunctionCompilationData> mFunctions;
public:
	//Creates a new JIT compiler
	JITCompiler(VMState& vmState);

	//JITs the given function
	JitFunction generateFunction(Function* function);

	//Resolves call targets. This function should only be called after all functions has been jitted.
	void resolveCallTargets();
};