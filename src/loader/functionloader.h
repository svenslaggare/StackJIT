#pragma once
#include <string>
#include <vector>
#include "loader.h"

namespace stackjit {
	class VMState;
	class FunctionDefinition;
	class ManagedFunction;
	class ImageContainer;

	////Represents a function loader
	//namespace FunctionLoader {
	//	//Generates a definition for the given function
	//	void generateDefinition(VMState& vmState,
	//							const Loader::Function& function,
	//							FunctionDefinition& definition);

	//	//Loads the given external function
	//	void loadExternal(VMState& vmState,
	//					  const Loader::Function& function,
	//					  FunctionDefinition& loadedFunction);

	//	//Loads the given managed function
	//	ManagedFunction* loadManaged(VMState& vmState,
	//								 const Loader::Function& function,
	//								 const FunctionDefinition& functionDefinition);
	//}

	//Represents a function loader
	class FunctionLoader {
	private:
		VMState& mVMState;
	public:
		FunctionLoader(VMState& vmState);

		//Generates a definition for the given function
		void generateDefinition(const Loader::Function& function, FunctionDefinition& definition);

		//Loads the given external function
		void loadExternal(const Loader::Function& function, FunctionDefinition& loadedFunction);

		//Loads the given managed function
		ManagedFunction* loadManaged(const Loader::Function& function,const FunctionDefinition& functionDefinition);
	};
}
