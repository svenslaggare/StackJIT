#pragma once
#include "binder.h"
#include "jit.h"
#include "parser.h"
#include <vector>
#include <unordered_map>

class VMState;
class Assembly;
class Function;

//The type of the assembly
enum class AssemblyType {
	//The assembly is a program. This requires an entry point (main function)
	Program,
	//The assembly is a library. A library cannot be executed.
	Library
};

namespace AssemblyParser {
	struct Assembly;
}

//Represents a entry point
typedef int (*EntryPointFunction)();

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

	//Returns the size of the stack
	std::size_t size() const;

	//Returns the start of the stack
	CallStackEntry* start();
	CallStackEntry* const start() const;

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

	std::string mBaseDir;

	std::vector<AssemblyParser::Assembly*> mAssemblies;
	std::unordered_map<std::string, Function*> mLoadedFunctions;
	std::unordered_map<std::string, AssemblyParser::Function> mLoadedDefinitions;

	//Generates code for loaded functions
	void generateCode();

	//Loads the assemblies
	void load();

	//Loads the runtime library
	void loadRuntimeLibrary();

	//Compiles the given function
	void compileFunction(Function* function, std::string signature = "", bool resolveSymbols = false);
public:
	//Creates a new execution engine
	ExecutionEngine(VMState& vmState);
	~ExecutionEngine();

	//Prevent it from being copied
	ExecutionEngine(const ExecutionEngine&) = delete;
	ExecutionEngine& operator=(const ExecutionEngine&) = delete;

	//Returns the JIT compiler
	JITCompiler& jitCompiler();
	const JITCompiler& jitCompiler() const;

	//Sets the base directory of the VM
	void setBaseDir(std::string baseDir);

	//Returns the entry point
	EntryPointFunction entryPoint() const; 

	//Loads the given library from a file
	bool loadLibrary(std::string filePath);

	//Loads the given assembly
	void loadAssembly(AssemblyParser::Assembly& assembly, AssemblyType assemblyType);

	//Loads definitions
	void loadDefinitions();

	//Compiles the function with the given signature
	bool compileFunction(std::string signature);

	//Compiles the functions
	void compile();

	//Returns the call stack
    CallStack& callStack();
    const CallStack& callStack() const;
};