#pragma once
class VMState;

//Exposes native functions used in tests
namespace TestLibrary {
	//Adds the test library to the given VM state
	void add(VMState& vmState);
}