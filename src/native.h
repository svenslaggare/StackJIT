#pragma once
class VMState;

//The part of the runtime library exposed to programs
namespace NativeLibrary {
	//Adds the native library to the given VM state
	void add(VMState& vmState);
}