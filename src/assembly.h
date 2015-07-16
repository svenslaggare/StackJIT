#pragma once

//The type of the assembly
enum class AssemblyType {
	//The assembly is a program. This requires an entry point (main function)
	Program,
	//The assembly is a library. A library cannot be executed.
	Library
};