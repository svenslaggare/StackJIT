#pragma once
#include <stack>
#include <string>

class Function;
class VMState;
class Type;

typedef std::stack<const Type*> InstructionTypes;

//The function verifier
namespace Verifier {
	//Verifies the given function
	void verifyFunction(Function& function, VMState& vmState, bool showDebug = false);
}