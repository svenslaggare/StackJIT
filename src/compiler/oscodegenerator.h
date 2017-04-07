#pragma once
#include <string>

namespace stackjit {
	class Amd64Assembler;
	class ManagedFunction;
	class FunctionDefinition;
	class CallingConvention;

	/**
	 * Contains implementations of code generations specific for a particular OS
	 */
	namespace OSCodeGenerator {
		//Generates a compile call for the given function
		std::size_t generateCompileCall(const CallingConvention& callingConvention,
										Amd64Assembler& assembler,
										ManagedFunction& function,
										const FunctionDefinition& funcToCall);
	}
}