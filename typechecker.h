#pragma once
#include <stack>
#include <string>

struct FunctionCompilationData;
struct VMState;

//The types
enum Types : unsigned char {
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

	//Converts the given string into a type
	Types stringToType(std::string);

	//Type checks the given function
	void typeCheckFunction(FunctionCompilationData& function, const VMState& vmState, bool showDebug = false);
}