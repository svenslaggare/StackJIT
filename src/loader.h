#pragma once
#include <string>
#include <vector>
#include "vmstate.h"
#include "parser.h"

class Assembly;
class VMState;

//Represents a loader
namespace Loader {
	//Loads an assembly from the given stream
	void load(std::istream& stream, VMState& vmState, AssemblyParser::Assembly& assembly);

	//Loads the given classes from the given assemblies
	void loadClasses(VMState& vmState, std::vector<AssemblyParser::Assembly*>& assemblies);

	//Loads the given function
	Function* loadFunction(VMState& vmState, AssemblyParser::Function& function);
}