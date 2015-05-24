#pragma once
#include <string>

class Assembly;
class VMState;

//Represents a loader
namespace Loader {
	//Loads an assembly from the given stream
	void load(std::istream& stream, VMState& vmState, Assembly& assembly);
}