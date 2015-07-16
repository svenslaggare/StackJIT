#pragma once
#include <string>
#include "vmstate.h"
#include "parser.h"

class Assembly;
class VMState;

//Represents a loader
namespace Loader {
	//Loads an assembly from the given stream
	void load(std::istream& stream, VMState& vmState, AssemblyParser::Assembly& assembly);

	//Loads the given struct
	void loadStruct(VMState& vmState, AssemblyParser::Struct& structure);

	//Loads the given function
	Function* loadFunction(VMState& vmState, AssemblyParser::Function& function);
}