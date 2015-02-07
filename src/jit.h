#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <deque>
#include <functional>

class VMState;
class Function;
class Type;

//Represents a jitted function
typedef int (*JitFunction)();

//Represents a branch target
struct BranchTarget {
	const unsigned int target;
	const unsigned int instructionSize;

	BranchTarget(unsigned int target, unsigned int instructionSize);
};

//Represents an unresolved function call
struct UnresolvedFunctionCall {
	//The function that has an unresolved call
	const std::string functionName;

	//The offset for the call instruction
	const unsigned int callOffset;

	UnresolvedFunctionCall(std::string functionName, unsigned int callOffset);

	bool operator<(const UnresolvedFunctionCall& rhs) const;
	bool operator==(const UnresolvedFunctionCall& rhs) const;

	//The custom hash function
	typedef std::function<std::size_t(const UnresolvedFunctionCall& call)> Hash_t;
	static Hash_t Hash;
};

//Holds compilation data for a function
struct FunctionCompilationData {
	Function& function;

	//Unresolved branches
	std::unordered_map<unsigned int, BranchTarget> unresolvedBranches;

	//Mapping from instruction num to native instruction
	std::vector<unsigned int> instructionNumMapping;			

	//Unresolved function calls						 
	std::unordered_map<UnresolvedFunctionCall, std::string,	UnresolvedFunctionCall::Hash_t> unresolvedCalls;

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