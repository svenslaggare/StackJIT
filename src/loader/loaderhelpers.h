#pragma once
#include <string>
#include "../type/classmetadata.h"
#include "parser.h"

namespace stackjit {
	class VMState;
	class Type;
	class ClassType;

	//Contains helper functions for loaders
	namespace LoaderHelpers {
		//Returns the type for the given type name
		const Type* getType(VMState& vmState, std::string typeName);

		//Returns the given class type
		const ClassType* getClassType(VMState& vmState, std::string typeName);

		//Returns the access modifier or the default modifier
		AccessModifier getAccessModifier(const AssemblyParser::AttributeContainer& attributeContainer);

		//Indicates if the given function is virtual
		bool getIsVirtual(const AssemblyParser::AttributeContainer& attributeContainer);
	}
}