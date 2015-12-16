#pragma once
#include "binder.h"
#include "jit.h"
#include "parser.h"
#include "callstack.h"
#include "imageloader.h"
#include "imagecontainer.h"
#include <vector>
#include <unordered_map>

class VMState;
class Assembly;
class ManagedFunction;

namespace AssemblyParser {
	struct Assembly;
}

//The type of the assembly
enum class AssemblyType {
	//The assembly is a program. This requires an entry point (main function).
	Program,
	//The assembly is a library. A library cannot be executed.
	Library
};

//Represents an entry point
typedef int (*EntryPointFunction)();

//Represents the execution engine
class ExecutionEngine {
private:
	VMState& mVMState;
	JITCompiler mJIT;
	CallStack mCallStack;

	std::string mBaseDir;

	ImageContainer mImageContainer;
	std::unordered_map<std::string, ManagedFunction*> mLoadedFunctions;

	//Generates code for loaded functions
	void generateCode();

	//Loads the runtime library
	void loadRuntimeLibrary();

	//Loads the given image
	void loadImage(AssemblyImage* image, AssemblyType assemblyType);

	//Loads the given image from the given stream
	void loadImage(std::ifstream& stream, AssemblyType assemblyType);

	//Compiles the given function
	void compileFunction(ManagedFunction* function, bool resolveSymbols = false);
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

	//Loads the given assembly from a file
	bool loadAssembly(std::string filePath, AssemblyType assemblyType = AssemblyType::Library);

	//Loads the given assembly
	void loadAssembly(AssemblyParser::Assembly& assembly, AssemblyType assemblyType);

	//Loads assemblies
	void load(bool loadBody = false);

	//Compiles the function with the given signature
	bool compileFunction(std::string signature);

	//Compiles all functions
	void compile();

	//Returns the call stack
	CallStack& callStack();
	const CallStack& callStack() const;
};