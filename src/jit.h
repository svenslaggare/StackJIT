#pragma once
#include "linux.h"
#include "callingconvention.h"
#include "codegenerator.h"
#include "exceptions.h"
#include <unordered_map>
#include <vector>
#include <functional>

class VMState;
class Function;
class Type;
class MemoryManager;

//Represents a compiled function
typedef void (*JitFunction)();

//Represents a branch target
struct BranchTarget {
	//The target of the branch
	const unsigned int target;

	//The size of the branch instruction
	const unsigned int instructionSize;

	BranchTarget(unsigned int target, unsigned int instructionSize);
};

//The type of a function call
enum class FunctionCallType {
	//A direct address to the function is used
	Absolute,
	//An address relative callee function to the function is used
	Relative
};

//Represents an unresolved function call
struct UnresolvedFunctionCall {
	const FunctionCallType type;

	//The offset for the call instruction
	const std::size_t callOffset;

	//The function to call
	const FunctionDefinition& funcToCall;

	//Creates a new unresolved function call
	UnresolvedFunctionCall(FunctionCallType type, std::size_t callOffset, const FunctionDefinition& funcToCall);
};

//Holds compilation data for a function
struct FunctionCompilationData {
	Function& function;

	//Unresolved branches
	std::unordered_map<unsigned int, BranchTarget> unresolvedBranches;

	//Unresolved native branches
	std::unordered_map<unsigned int, long> unresolvedNativeBranches;

	//Mapping from instruction number to native instruction offset
	std::vector<unsigned int> instructionNumMapping;			

	//Unresolved function calls						 
	std::vector<UnresolvedFunctionCall> unresolvedCalls;

	//Holds compilation data for the given function
	FunctionCompilationData(Function& function);
};

//Represents the JIT compiler
class JITCompiler {
private:
	VMState& mVMState;
	LinuxMemoryManager mMemoryManager;
	LinuxCallingConvention mCallingConvention;
	ExceptionHandling mExceptionHandling;
	CodeGenerator mCodeGen;
	std::unordered_map<std::string, FunctionCompilationData> mFunctions;

	//Creates macro functions
	void createMacros();

	//Resolves branches for the given function
	void resolveBranches(FunctionCompilationData& functionData);

	//Resolves native branches for the given function
	void resolveNativeBranches(FunctionCompilationData& functionData);

	//Resolves call targets. This function should only be called after all functions has been compiled.
	void resolveCallTargets(FunctionCompilationData& functionData);
public:
	//Creates a new JIT compiler
	JITCompiler(VMState& vmState);

	//Prevent it from being copied
	JITCompiler(const JITCompiler&) = delete;
	JITCompiler& operator=(const JITCompiler&) = delete;

	//Returns the memory manager
	MemoryManager& memoryManager();

	//Indicates if the given function has been compiled
	bool hasCompiled(std::string signature) const;

	//Returns the compiled functions
	const std::unordered_map<std::string, FunctionCompilationData>& functions() const;

	//Compiles the given function
	JitFunction compileFunction(Function* function);

	//Resolves symbols for the given function
	void resolveSymbols(std::string signature);

	//Resolves symbols. This function should only be called after all functions has been compiled.
	void resolveSymbols();

	//Makes compiled functions executable.
	void makeExecutable();
};