#pragma once
#include "binder.h"
#include "jit.h"
#include "assembly.h"
#include "parser.h"
#include <deque>
#include <vector>

typedef int (*EntryPointFunction)();

class VMState;
class Assembly;
class Function;

using CallStackEntry = std::pair<Function*, int>;

//Represents the execution engine
class ExecutionEngine {
private:
	VMState& mVMState;
	JITCompiler mJIT;
	std::deque<CallStackEntry> mCallStack;

	std::vector<AssemblyParser::Assembly*> mAssemblies;
	std::vector<Function*> mLoadedFunctions;

	//Loads the assemblies
	void load();

	//Generates code for loaded functions
	void generateCode();
public:
	//Creates a new execution engine
	ExecutionEngine(VMState& vmState);
	~ExecutionEngine();

	//Prevent it from being copied
	ExecutionEngine(const ExecutionEngine&) = delete;
	ExecutionEngine& operator=(const ExecutionEngine&) = delete;

	//Returns the entry point
	EntryPointFunction entryPoint() const; 

	//Loads the given assembly
	void loadAssembly(AssemblyParser::Assembly& assembly, AssemblyType assemblyType);

	//Compiles the functions
	void compile();

	//Returns the call stack
    const std::deque<CallStackEntry>& callStack() const;

    //Pops the top function
    CallStackEntry popFunc();

    //Pushes the given function to the top of the stack
    void pushFunc(Function* func, int instIndex);
};