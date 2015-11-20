#pragma once
#include "amd64.h"
#include "function.h"
#include "binder.h"
#include <string>
#include <functional>
#include <unordered_map>

struct FunctionCompilationData;
class VMState;
class Instruction;
class CallingConvention;
class MemoryManager;
class ManagedFunction;
class ExceptionHandling;
class FunctionDefinition;

//Manages the operand stack
namespace OperandStack {
	//Duplicates the top operand
	void duplicate(ManagedFunction& function, int operandStackIndex);

	//Pops an operand from the operand stack to the given register
	void popReg(ManagedFunction& function, int operandStackIndex, Registers reg);
	void popReg(ManagedFunction& function, int operandStackIndex, NumberedRegisters reg);
	void popReg(ManagedFunction& function, int operandStackIndex, FloatRegisters reg);

	//Pushes the given register to the operand stack
	void pushReg(ManagedFunction& function, int operandStackIndex, Registers reg);
	void pushReg(ManagedFunction& function, int operandStackIndex, FloatRegisters reg);

	//Pushes the given value to the operand stack
	void pushInt(ManagedFunction& function, int operandStackIndex, int value);
}

//Manages the operand stack
class ActualOperandStack {
private:
	ManagedFunction& mFunction;
	int mTopIndex = -1;

	//Asserts that the stack is not empty
	void assertNotEmpty();

	//Calculates the offset in the stack frame for the given stack operand
	int getStackOperandOffset(int operandIndex);
public:
	//Creates a new operand stack for the given function
	ActualOperandStack(ManagedFunction& function);

	//Duplicates the top operand
	void duplicate();

	//Pops an operand from the operand stack to the given register
	void popReg(Registers reg);
	void popReg(NumberedRegisters reg);
	void popReg(FloatRegisters reg);

	//Pushes the given register to the operand stack
	void pushReg(Registers reg);
	void pushReg(FloatRegisters reg);

	//Pushes the given value to the operand stack
	void pushInt(int value);
};

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
	void defineMacro( const FunctionDefinition& function, MacroFunction macroFunction);

	//Generates a call to the given function
	void generateCall(CodeGen& codeGen, unsigned char* funcPtr, Registers addrReg = Registers::AX, bool shadowSpaceNeeded = true);

	//Generates a call to the garbage collect runtime function
	void generateGCCall(CodeGen& generatedCode, ManagedFunction& function, int instIndex);

	//Initializes the given function
	void initializeFunction(FunctionCompilationData& functionData);

	//Generates native instructions for the given VM instruction
	void generateInstruction(FunctionCompilationData& functionData, const VMState& vmState, const Instruction& inst, int instIndex);
};