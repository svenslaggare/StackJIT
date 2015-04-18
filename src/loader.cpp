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
	Instruction loadInstruction(VMState& vmState, Function* function, Parser::Instruction inst) {
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
	Function* loadFunction(VMState& vmState, Parser::Function* function) {
		std::vector<const Type*> parameters;
		const Type* returnType;

		for (auto param : function->parameters) {
			parameters.push_back(getType(vmState, param));
		}

		returnType = getType(vmState, function->returnType);

		auto loadedFunc = new Function(
			function->name,
			parameters,
			returnType,
			function->isMemberFunction,
			function->memberFunctionName == ".constructor");

		//Locals
		loadedFunc->setNumLocals(function->localTypes.size());
		for (std::size_t local = 0; local < function->localTypes.size(); local++) {
			auto localType = function->localTypes[local];

			if (localType != "") {
				loadedFunc->setLocal(local, getType(vmState, localType));
			}
		}

		//Instructions
		for (auto inst : function->instructions) {
			loadedFunc->instructions.push_back(loadInstruction(vmState, loadedFunc, inst));
		}

		return loadedFunc;
	}

	//Loads the given external function
	void loadExternalFunction(VMState& vmState, Assembly& assembly, Parser::Function* function) {
		std::vector<const Type*> parameters;

		for (auto param : function->parameters) {
			parameters.push_back(getType(vmState, param));
		}

		auto signature = vmState.binder().functionSignature(function->name, parameters);

        if (assembly.functions.count(signature) == 0 && !vmState.binder().isDefined(signature)) {
            auto externSignature = vmState.binder().functionSignature(function->externalName, parameters);

            if (vmState.binder().isDefined(externSignature)) {
                if (!vmState.binder().defineExternal(signature, externSignature)) {
                    throw std::runtime_error("'" + externSignature + "' is not an external function.");
                }
            } else {
                throw std::runtime_error("The external function '" + externSignature + "' is not defined.");
            }
        } else {
            throw std::runtime_error("The function '" + signature + "' is already defined.");
        }
	}

	//Loads the given struct
	void loadStruct(VMState& vmState, Parser::Struct* structure) {
		std::vector<std::pair<std::string, const Type*>> fields;

		for (auto field : structure->fields) {
			fields.push_back(std::make_pair(field.name, getType(vmState, field.type)));
		}

		vmState.structProvider().add(structure->name, StructMetadata(fields));
	}
}

void Loader::load(std::istream& stream, VMState& vmState, Assembly& assembly) {
	//Parse it
	auto tokens = Parser::tokenize(stream);
	Parser::Assembly parsedAssembly;
    Parser::parseTokens(tokens, parsedAssembly);

    //Load
    for (auto currentStruct : parsedAssembly.structs) {
    	loadStruct(vmState, currentStruct);
    }

    for (auto currentFunc : parsedAssembly.functions) {
    	auto loadedFunc = loadFunction(vmState, currentFunc);

    	if (!currentFunc->isExternal) {
	    	auto signature = vmState.binder().functionSignature(
	    		loadedFunc->name(),
	    		loadedFunc->arguments());

	    	if (assembly.functions.count(signature) == 0 && !vmState.binder().isDefined(signature)) {
	            assembly.functions[signature] = loadedFunc;
	        } else {
	            throw std::runtime_error("The function '" + signature + "' is already defined.");
	        }
	    } else {
	    	loadExternalFunction(vmState, assembly, currentFunc);
	    }
    }

    //Free the parsed assembly
    for (auto currentFunc : parsedAssembly.functions) {
    	delete currentFunc;
    }

    for (auto currentStruct : parsedAssembly.structs) {
    	delete currentStruct;
    }
}