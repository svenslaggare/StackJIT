#pragma once
#include <stack>
#include <string>

class Function;
class VMState;
class Type;

typedef std::stack<const Type*> InstructionTypes;

//The type checker
namespace TypeChecker {
	//Converts the given type to a string
	std::string typeToString(const Type* type);

	//Type checks the given function
	void typeCheckFunction(Function& function, VMState& vmState, bool showDebug = false);
}