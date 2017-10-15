#pragma once
#include "compiler/binder.h"
#include "compiler/jit.h"
#include "loader/loader.h"
#include "loader/functionloader.h"
#include "loader/classloader.h"
#include "loader/verifier.h"
#include "runtime/callstack.h"
#include "loader/imageloader.h"
#include "loader/imagecontainer.h"
#include <vector>
#include <unordered_map>

namespace stackjit {
	class VMState;
	class Assembly;
	class ManagedFunction;

	namespace Loader {
		class Assembly;
	}

	//The type of the assembly
	enum class AssemblyType {
		Program, //The assembly is a program. This requires an entry point (main function).
		Library  //The assembly is a library. A library cannot be executed.
	};

	//Represents an entry point
	using EntryPointFunction = int (*)();

	//The signature of the entry point
	const std::string ENTRY_POINT_SIGNATURE = "main()";

	//Represents the execution engine
	class ExecutionEngine {
	private:
		VMState& mVMState;
		JITCompiler mJIT;
		CallStack mCallStack;
		Verifier mVerifier;

		std::string mBaseDir;

		FunctionLoader mFunctionLoader;
		ClassLoader mClassLoader;

		ImageContainer mImageContainer;
		std::unordered_map<std::string, ManagedFunction*> mLoadedFunctions;
		bool mHasMainInitialized = false;

		//Generates code for loaded functions
		void generateCode();

		//Loads the runtime library
		void loadRuntimeLibrary();

		//Loads the given image
		void loadImage(AssemblyImage* image, AssemblyType assemblyType);

		//Loads the given image from the given stream
		void loadImage(std::ifstream& stream, AssemblyType assemblyType);

		//Compiles the given function
		JitFunction compileFunction(ManagedFunction* function, bool resolveSymbols = false);
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
		void loadAssembly(Loader::Assembly& assembly, AssemblyType assemblyType);

		//Loads the all the data needed before execution
		void load(bool loadFunctionBodies = false);

		//Compiles the function with the given signature
		bool compileFunction(const std::string& signature, JitFunction& entryPoint);
		bool compileFunction(const std::string& signature);

		//Loads and compiles all functions
		void loadAndCompileAll();

		//Returns the call stack
		CallStack& callStack();
		const CallStack& callStack() const;
	};
}