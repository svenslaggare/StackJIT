#pragma once
#include "linux.h"
#include "callingconvention.h"
#include "codegenerator.h"

#include <unordered_map>
#include <vector>
#include <deque>
#include <functional>

class VMState;
class Function;
class Type;
class MemoryManager;

//Represents a jitted function
typedef void (*JitFunction)();

//Represents a branch target
struct BranchTarget {
	//The target of the branch
	const unsigned int target;

	//The size of the bransh instruction
	const unsigned int instructionSize;

	BranchTarget(unsigned int target, unsigned int instructionSize);
};

//The type of a function call
enum class FunctionCallType {
	//A direct address to the function is used
	DIRECT,
	//An address relative callee function to the function is used
	RELATIVE
};

//Represents an unresolved function call
struct UnresolvedFunctionCall {
	const FunctionCallType type;

	//The function that has an unresolved call
	const std::string functionName;

	//The offset for the call instruction
	const std::size_t callOffset;

	//Creates a new unresolved function call
	UnresolvedFunctionCall(FunctionCallType type, std::string functionName, std::size_t callOffset);

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

	//The size of the operand stack
	int operandStackSize;

	//Holds compilation data for the given function
	FunctionCompilationData(Function& function);
};

//Represents the JIT compiler
class JITCompiler {
private:
	VMState& mVMState;
	LinuxMemoryManager mMemoryManager;
	LinuxCallingConvention mCallingConvention;
	CodeGenerator mCodeGen;
	std::unordered_map<std::string, FunctionCompilationData> mFunctions;

	//Resolves branches for the given function
	void resolveBranches(FunctionCompilationData& functionData);
public:
	//Creates a new JIT compiler
	JITCompiler(VMState& vmState);

	//Prevent it from being copied
	JITCompiler(const JITCompiler&) = delete;
	JITCompiler& operator=(const JITCompiler&) = delete;

	//Returns the memory manager
	MemoryManager& memoryManager();

	//JITs the given function
	JitFunction generateFunction(Function* function);

	//Resolves call targets. This function should only be called after all functions has been jitted.
	void resolveCallTargets();

	//Makes jitted functions executable.
	void makeExecutable();
};