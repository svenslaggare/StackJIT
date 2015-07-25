#pragma once
#include <stack>
#include <string>

class Function;
class VMState;
class Type;

typedef std::stack<const Type*> InstructionTypes;

//The function verifier
namespace Verifier {
	//Converts the given type to a string
	std::string typeToString(const Type* type);

	//Verifies the given function
	void verifyFunction(Function& function, VMState& vmState, bool showDebug = false);
}