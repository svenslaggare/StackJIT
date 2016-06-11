#include "loader.h"
#include "parser.h"
#include "../core/function.h"
#include "../vmstate.h"
#include "../core/instruction.h"
#include "../type/type.h"
#include "../core/functionsignature.h"
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

	//Returns the given class type
	const ClassType* getClassType(VMState& vmState, std::string typeName) {
		if (!vmState.classProvider().isDefined(typeName)) {
        	throw std::runtime_error("'" + typeName + "' is not a defined class.");
        }

		return (const ClassType*)vmState.typeProvider().makeType("Ref." + typeName);
	}

	//Loads the given instruction
	Instruction loadInstruction(VMState& vmState, ManagedFunction* function, AssemblyParser::Instruction inst) {
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

		if (inst.calledClassType != "") {
			newInst.classType = getClassType(vmState, inst.calledClassType);
		}

		return newInst;
	}

	//Returns the access modifier or the default modifier
	AccessModifier getAccessModifier(const AssemblyParser::AttributeContainer& attributeContainer) {
		AccessModifier accessModifier = ClassMetadata::DEFAULT_ACCESS_MODIFIER;

		if (attributeContainer.count("AccessModifier") > 0) {
			auto& accessModifierAttribute = attributeContainer.at("AccessModifier");
			if (accessModifierAttribute.values.count("value") > 0) {
				auto modifierValue = accessModifierAttribute.values.at("value");
				if (!fromString(modifierValue, accessModifier)) {
					throw std::runtime_error("'" + modifierValue + "' is not a valid access modifier.");
				}
			}
		}

		return accessModifier;
	}

	//Indicates if the given function is virtual
	bool getIsVirtual(const AssemblyParser::AttributeContainer& attributeContainer) {
		bool isVirtual = false;

		if (attributeContainer.count("Virtual") > 0) {
			auto& attribute = attributeContainer.at("Virtual");
			if (attribute.values.count("value") > 0) {
				auto value = attribute.values.at("value");
				if (value == "true") {
					isVirtual = true;
				} else if (value == "false") {
					isVirtual = false;
				} else {
					throw std::runtime_error("'" + value + "' is not valid value for the attribute 'Virtual'.");
				}
			}
		}

		return isVirtual;
	}
}

void Loader::generateDefinition(VMState& vmState, const AssemblyParser::Function& function, FunctionDefinition& definition) {
	auto returnType = getType(vmState, function.returnType);

	std::vector<const Type*> parameters;
	for (auto param : function.parameters) {
		parameters.push_back(getType(vmState, param));
	}

	const ClassType* classType = nullptr;
	AccessModifier accessModifier = ClassMetadata::DEFAULT_ACCESS_MODIFIER;
	bool isVirtual = false;

	if (function.isMemberFunction) {
		classType = dynamic_cast<const ClassType*>(getType(vmState, "Ref." + function.className));
		if (classType == nullptr) {
			throw std::runtime_error("'" + function.className + "' is not a class type.");
		}

		accessModifier = getAccessModifier(function.attributes);
		isVirtual = getIsVirtual(function.attributes);
	}

	definition = FunctionDefinition(
		function.name,
		parameters,
		returnType,
		classType,
		accessModifier,
		function.memberFunctionName == ".constructor",
		isVirtual);
}

void Loader::loadExternalFunction(VMState& vmState, const AssemblyParser::Function& function, FunctionDefinition& loadedFunction) {
	if (!function.isExternal) {
		throw std::runtime_error("Expected an external function");
	}

	generateDefinition(vmState, function, loadedFunction);
	auto signature = FunctionSignature::from(loadedFunction).str();

	//Check if defined
	if (!vmState.binder().isDefined(signature)) {
		throw std::runtime_error("The external function '" + signature + "' is not defined.");
	}
}

ManagedFunction* Loader::loadManagedFunction(VMState& vmState, const AssemblyParser::Function& function, const FunctionDefinition& functionDefinition) {
	if (function.isExternal) {
		throw std::runtime_error("Expected a managed function");
	}

	auto loadedFunc = new ManagedFunction(functionDefinition);

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
		loadedFunc->instructions().push_back(loadInstruction(vmState, loadedFunc, inst));
	}

	return loadedFunc;
}

void Loader::loadClasses(VMState& vmState, ImageContainer& imageContainer) {
	//First, create the classes
	std::vector<std::pair<ClassMetadata*, std::string>> inheritingClasses;
	for (auto& image : imageContainer.images()) {
		for (auto& current : image->classes()) {
			auto& classDef = current.second;
			vmState.classProvider().add(classDef.name, std::move(ClassMetadata(classDef.name)));

			if (classDef.parentClassName != "") {
				inheritingClasses.push_back(std::make_pair(
					&vmState.classProvider().getMetadata(classDef.name),
					classDef.parentClassName));
			}
		}
	}

	//Then add the fields
	for (auto& image : imageContainer.images()) {
		for (auto& current : image->classes()) {
			auto& classDef = current.second;

			imageContainer.loadClassBody(classDef.name);
			auto& classMetadata = vmState.classProvider().getMetadata(classDef.name);

			for (auto& field : classDef.fields) {
				auto accessModifier = getAccessModifier(field.attributes);
				classMetadata.addField(field.name, getType(vmState, field.type), accessModifier);
			}
		}
	}

	//Handle inheritance
	if (inheritingClasses.size() > 0) {
		for (auto& current : inheritingClasses) {
			auto parentClass = getClassType(vmState, current.second);
			current.first->setParentClass(parentClass);
		}
	}
}

void Loader::load(std::istream& stream, VMState& vmState, AssemblyParser::Assembly& assembly) {
	auto tokens = AssemblyParser::tokenize(stream);
	AssemblyParser::parseTokens(tokens, assembly);
}