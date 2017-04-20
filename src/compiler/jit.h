#pragma once
#include "memory.h"
#include "callingconvention.h"
#include "codegenerator.h"
#include "compilationdata.h"
#include "exceptions.h"
#include <unordered_map>
#include <vector>
#include <functional>

namespace stackjit {
	class VMState;
	class ManagedFunction;
	class Type;

	//Represents a compiled function
	using JitFunction = void(*)();

	//The type of a function call
	enum class FunctionCallType : unsigned char {
		Absolute,
		Relative
	};

	//Represents the JIT compiler
	class JITCompiler {
	private:
		VMState& mVMState;
		MemoryManager mMemoryManager;
		CallingConvention mCallingConvention;
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

		//Returns the memory manager
		MemoryManager& memoryManager();

		//Returns the compiled functions
		const std::unordered_map<std::string, FunctionCompilationData>& functions() const;
	public:
		//Creates a new JIT compiler
		JITCompiler(VMState& vmState);

		//Prevent it from being copied
		JITCompiler(const JITCompiler&) = delete;
		JITCompiler& operator=(const JITCompiler&) = delete;

		//Indicates if the given function has been compiled
		bool hasCompiled(std::string signature) const;

		//Compiles the given function
		JitFunction compileFunction(ManagedFunction* function);

		//Resolves symbols for the given function
		void resolveSymbols(std::string signature);

		//Resolves symbols for all functions.
		//This function should only be called after all functions has been compiled.
		void resolveSymbols();

		//Makes compiled functions executable.
		void makeExecutable();
	};
}
