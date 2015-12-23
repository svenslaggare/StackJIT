#pragma once
#include <string>
#include <vector>
#include "../vmstate.h"
#include "parser.h"

class Assembly;
class VMState;
class FunctionDefinition;
class ImageContainer;

//Represents a loader
namespace Loader {
	//Loads an assembly from the given stream
	void load(std::istream& stream, VMState& vmState, AssemblyParser::Assembly& assembly);

	//Loads the given classes from the given images container
	void loadClasses(VMState& vmState, ImageContainer& imageContainer);

	//Generates a definition for the given function
	void generateDefinition(VMState& vmState, const AssemblyParser::Function& function, FunctionDefinition& definition);

	//Loads the given external function
	void loadExternalFunction(VMState& vmState, const AssemblyParser::Function& function, FunctionDefinition& loadedFunction);

	//Loads the given managed function
	ManagedFunction* loadManagedFunction(VMState& vmState, const AssemblyParser::Function& function,
										 const FunctionDefinition& functionDefinition);
}