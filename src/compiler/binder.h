#pragma once
#include <unordered_map>
#include <string>
#include "../core/function.h"

namespace stackjit {
	class Type;
	class ClassType;

	//Represents a binder
	class Binder {
	private:
		std::unordered_map<std::string, FunctionDefinition> mFunctionTable;
	public:
		//Returns the function table
		const std::unordered_map<std::string, FunctionDefinition>& functionTable() const;

		//Defines the given function
		bool define(FunctionDefinition funcDef);

		//Indicates if the given function signature is defined
		bool isDefined(std::string signature) const;

		//Returns the function with the given signature
		FunctionDefinition& getFunction(std::string signature);
		const FunctionDefinition& getFunction(std::string signature) const;
	};
}
