#pragma once
#include <string>
#include <vector>
#include "vmstate.h"
#include "parser.h"

class Assembly;
class VMState;
class FunctionDefinition;

//Represents a loader
namespace Loader {
	//Loads an assembly from the given stream
	void load(std::istream& stream, VMState& vmState, AssemblyParser::Assembly& assembly);

	//Loads the given classes from the given assemblies
	void loadClasses(VMState& vmState, std::vector<AssemblyParser::Assembly*>& assemblies);

	//Generates a definition for the given function
	void generateDefinition(VMState& vmState, AssemblyParser::Function& function, FunctionDefinition& definition);

	//Loads the given external function
	void loadExternalFunction(VMState& vmState, AssemblyParser::Function& function, FunctionDefinition& loadedFunction);

	//Loads the given managed function
	Function* loadManagedFunction(VMState& vmState, AssemblyParser::Function& function, bool checkIfDefined = true);
}