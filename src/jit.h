#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <deque>

class VMState;
class Function;
class Type;

//Represents a jitted function
typedef int (*JitFunction)();

typedef std::pair<std::string, unsigned int> FunctionCall;
typedef std::pair<unsigned int, unsigned int> BranchTarget;

//Holds compilation data for a function
struct FunctionCompilationData {
	Function& function;

	//Unresolved branches
	std::unordered_map<unsigned int, BranchTarget> unresolvedBranches;

	//Mapping from instruction num to native instruction
	std::vector<unsigned int> instructionNumMapping;			

	//Unresolved function calls						 
	std::map<FunctionCall, std::string> unresolvedCalls;

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

	//Resolves branches for the given function
	void resolveBranches(FunctionCompilationData& functionData);
public:
	//Creates a new JIT compiler
	JITCompiler(VMState& vmState);

	//Prevent it from being copied
	JITCompiler(const JITCompiler&) = delete;
	JITCompiler& operator=(const JITCompiler&) = delete;

	//JITs the given function
	JitFunction generateFunction(Function* function);

	//Resolves call targets. This function should only be called after all functions has been jitted.
	void resolveCallTargets();

	//Makes jitted functions executable.
	void makeExecutable();
};