#include "loader.h"
#include "parser.h"
#include "function.h"
#include "vmstate.h"
#include "instructions.h"
#include "type.h"
#include "assembly.h"
#include <stdexcept>
#include <iostream>

namespace {
	//Returns the type for the given type name
	const Type* getType(VMState& vmState, std::string typeName) {
		auto type = vmState.typeProvider().makeType(typeName);

		if (type == nullptr) {
			throw std::runtime_error("There exists no type called '" + typeName  + "'.");
		}

		return type;
	}

	//Returns the given struct type
	const StructType* getStructType(VMState& vmState, std::string typeName) {
		if (!vmState.structProvider().isDefined(typeName)) {
        	throw std::runtime_error("'" + typeName + "' is not a defined struct.");
        }

		return (const StructType*)vmState.typeProvider().makeType("Ref.Struct." + typeName);
	}

	//Loads the given instruction
	Instruction loadInstruction(VMState& vmState, Function* function, AssemblyParser::Instruction inst) {
		Instruction newInst(inst.opCode);

		newInst.intValue = inst.intValue;
		newInst.charValue = inst.charValue;
		newInst.floatValue = inst.floatValue;
		newInst.strValue = inst.strValue;

		if (inst.parameters.size() > 0) {
			for (auto param : inst.parameters) {
				newInst.parameters.push_back(getType(vmState, param));
			}
		}

		if (inst.calledStructType != "") {
			newInst.calledStructType = getStructType(vmState, inst.calledStructType);
		}

		return newInst;
	}

	//Loads the given function
	Function* loadManagedFunction(VMState& vmState, AssemblyParser::Function& function) {
		std::vector<const Type*> parameters;
		const Type* returnType;

		for (auto param : function.parameters) {
			parameters.push_back(getType(vmState, param));
		}

		returnType = getType(vmState, function.returnType);

		auto loadedFunc = new Function(
			function.name,
			parameters,
			returnType,
			function.isMemberFunction,
			function.memberFunctionName == ".constructor");

		//Locals
		loadedFunc->setNumLocals(function.localTypes.size());
		for (std::size_t local = 0; local < function.localTypes.size(); local++) {
			auto localType = function.localTypes[local];

			if (localType != "") {
				loadedFunc->setLocal(local, getType(vmState, localType));
			}
		}

		//Instructions
		for (auto inst : function.instructions) {
			loadedFunc->instructions.push_back(loadInstruction(vmState, loadedFunc, inst));
		}

		return loadedFunc;
	}

	//Loads the given external function
	void loadExternalFunction(VMState& vmState, AssemblyParser::Function& function) {
		std::vector<const Type*> parameters;

		for (auto param : function.parameters) {
			parameters.push_back(getType(vmState, param));
		}

		auto signature = vmState.binder().functionSignature(function.name, parameters);

		if (!vmState.binder().isDefined(signature)) {
            throw std::runtime_error("The external function '" + signature + "' is not defined.");
        }
	}
}

Function* Loader::loadFunction(VMState& vmState, AssemblyParser::Function& function) {
	auto loadedFunc = loadManagedFunction(vmState, function);

	if (!function.isExternal) {
		auto signature = vmState.binder().functionSignature(
			loadedFunc->name(),
			loadedFunc->arguments());

		if (vmState.binder().isDefined(signature)) {
			throw std::runtime_error("The function '" + signature + "' is already defined.");
		}
	} else {
		loadExternalFunction(vmState, function);
	}

	return loadedFunc;
}

void Loader::loadStructs(VMState& vmState, std::vector<AssemblyParser::Assembly*>& assemblies) {
	//First, create the structs
	for (auto assembly : assemblies) {
		for (auto& structure : assembly->structs) {
			vmState.structProvider().add(structure.name, StructMetadata());
		}
	}

	//Then add the fields
	for (auto assembly : assemblies) {
		for (auto& structure : assembly->structs) {
			StructMetadata& structMetadata = vmState.structProvider()[structure.name];

			for (auto field : structure.fields) {
				structMetadata.addField(field.name, getType(vmState, field.type));
			}
		}
	}
}

void Loader::load(std::istream& stream, VMState& vmState, AssemblyParser::Assembly& assembly) {
	auto tokens = AssemblyParser::tokenize(stream);
	AssemblyParser::parseTokens(tokens, assembly);
}