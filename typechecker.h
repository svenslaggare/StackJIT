#pragma once
#include <stack>
#include <string>

struct FunctionCompilationData;
struct VMState;

//The types
enum Types : char {
    Untyped,
    Int,
    ArrayRef
};

typedef std::stack<Types> InstructionTypes;

namespace TypeChecker {
	//Pops a type from the given stack
	Types popType(std::stack<Types>& stack);

	//Converts the given type to a string
	std::string typeToString(Types type);

	//Type checks the given function
	void typeCheckFunction(FunctionCompilationData& function, const VMState& vmState, bool showDebug = false);
}