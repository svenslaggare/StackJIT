#pragma once
#include <stack>
#include <string>

struct FunctionCompilationData;
class VMState;
class Type;

// //The types
// enum Types : unsigned char {
//     Untyped,
//     Void,
//     Int,
//     ArrayRef,
//     StructRef
// };

typedef std::stack<Type*> InstructionTypes;

namespace TypeChecker {
	//Pops a type from the given stack
	Type* popType(std::stack<Type*>& stack);

	//Converts the given type to a string
	std::string typeToString(Type* type);

	//Converts the given string into a type
	Type* stringToType(VMState&, std::string);

	//Type checks the given function
	void typeCheckFunction(FunctionCompilationData& function, VMState& vmState, bool showDebug = false);
}