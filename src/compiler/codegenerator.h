#pragma once
#include "amd64.h"
#include "../core/function.h"
#include "binder.h"
#include "amd64assembler.h"
#include <string>
#include <functional>
#include <unordered_map>

namespace stackjit {
	struct FunctionCompilationData;
	class VMState;
	class Instruction;
	class CallingConvention;
	class MemoryManager;
	class ManagedFunction;
	class ExceptionHandling;
	class FunctionDefinition;

	//Represents context for a macro function
	struct MacroFunctionContext {
		const VMState& vmState;

		const CallingConvention& callingConvention;
		const ExceptionHandling& exceptionHandling;

		FunctionCompilationData& functionData;

		const Instruction& inst;
		const int instIndex;

		MacroFunctionContext(
				const VMState& vmState,
				const CallingConvention& callingConvention,
				const ExceptionHandling& exceptionHandling,
				FunctionCompilationData& functionData,
				const Instruction& inst,
				const int instIndex);
	};

	//Represents a macro function
	using MacroFunction = std::function<void (MacroFunctionContext)>;

	//Represents a code generator
	class CodeGenerator {
	private:
		const CallingConvention& mCallingConvention;
		const ExceptionHandling& mExceptionHandling;
		std::unordered_map<std::string, MacroFunction> mMacros;

		//Indicates if the given function needs to be compiled at runtime
		bool compileAtRuntime(const VMState& vmState, const FunctionDefinition& funcToCall, std::string funcSignature);

		//Generates a compile call for the given function
		std::size_t generateCompileCall(CodeGen& generatedCode, ManagedFunction& function, const FunctionDefinition& funcToCall);

		//Zeroes the locals
		void zeroLocals(FunctionCompilationData& functionData);

		//Pushes a function to the call stack
		void pushFunc(const VMState& vmState, FunctionCompilationData& functionData, int instIndex);

		//Pops a function from the call stack
		void popFunc(const VMState& vmState, CodeGen& generatedCode);
	public:
		//Creates a new code generator
		CodeGenerator(const CallingConvention& callingConvention, const ExceptionHandling& exceptionHandling);

		//Defines the given macro function
		void defineMacro(const FunctionDefinition& function, MacroFunction macroFunction);

		//Generates a call to the given function
		void generateCall(CodeGen& generatedCode, BytePtr funcPtr, IntRegister addressRegister = Registers::AX, bool shadowSpaceNeeded = true);

		//Generates a call to the garbage collect runtime function
		void generateGCCall(CodeGen& generatedCode, ManagedFunction& function, int instIndex);

		//Initializes the given function
		void initializeFunction(FunctionCompilationData& functionData);

		//Generates native instructions for the given VM instruction
		void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
	};
}
