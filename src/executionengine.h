#pragma once
#include "binder.h"
#include "jit.h"
#include "assembly.h"
#include "parser.h"
#include <vector>

//Represents a entry point
typedef int (*EntryPointFunction)();

class VMState;
class Assembly;
class Function;

//Represents a call stack entry
struct CallStackEntry {
	Function* function;
	int callPoint;

	CallStackEntry(Function* function, int callPoint);
	CallStackEntry();
};

//Manages the call stack
class CallStack {
private:
	std::size_t mSize;
	CallStackEntry* mStart;
	CallStackEntry* mTop;
public:
	//Creates a new call stack of the given size
	CallStack(std::size_t size);
	~CallStack();

	//Pushes the given function to the stack
	void push(Function* function, int callPoint);

	//Pops the top entry
	CallStackEntry pop();

	//Returns the start of the stack
	CallStackEntry* start();

	//Returns top of the stack
	CallStackEntry* top();

	//Pointer to the top variable
	CallStackEntry* const * const topPtr() const;
};

//Represents the execution engine
class ExecutionEngine {
private:
	VMState& mVMState;
	JITCompiler mJIT;
	CallStack mCallStack;

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
    CallStack& callStack();
    const CallStack& callStack() const;
};