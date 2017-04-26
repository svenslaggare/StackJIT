#pragma once
#include <string>
#include <vector>
#include <functional>

namespace stackjit {
	class Type;
	class ClassType;
	class FunctionDefinition;

	//Represents a function signature
	class FunctionSignature {
	private:
		std::string mSignature;

		//Creates a new signature from the given string
		FunctionSignature(std::string signature);
	public:
		//Creates a signature for the given name and parameters
		template<typename T>
		static std::string createSignature(std::string name,
										   const std::vector<T>& parameters,
										   std::function<std::string (T)> toStringFn);

		//Constructs a signature for the given function
		static FunctionSignature function(std::string name, const std::vector<const Type*>& parameters);

		//Constructs a signature for the given member function
		static FunctionSignature memberFunction(const ClassType* classType, std::string name, const std::vector<const Type*>& parameters);

		//Constructs a signature from the given function definition
		static FunctionSignature from(const FunctionDefinition& function);

		//Returns a string representation of the current signature
		const std::string& str() const;

		bool operator==(const FunctionSignature& rhs) const;
		bool operator!=(const FunctionSignature& rhs) const;
	};

	std::ostream& operator<<(std::ostream& os, const FunctionSignature& signature);

	template<typename T>
	std::string FunctionSignature::createSignature(std::string name,
												   const std::vector<T>& parameters,
												   std::function<std::string (T)> toStringFn) {
		std::string parametersString = "";
		bool isFirst = true;

		for (auto param : parameters) {
			if (isFirst) {
				isFirst = false;
			} else {
				parametersString += " ";
			}

			parametersString += toStringFn(param);
		}

		return name + "(" + parametersString + ")";
	}
}
