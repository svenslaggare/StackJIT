#include "functionloader.h"
#include "../core/function.h"
#include "../vmstate.h"
#include "../core/instruction.h"
#include "../type/type.h"
#include "../core/functionsignature.h"
#include "loaderhelpers.h"
#include <stdexcept>
#include <iostream>

namespace stackjit {
	namespace {
		//Loads the given instruction
		Instruction loadInstruction(VMState& vmState, const Loader::Instruction& instruction) {
			Instruction newInst(instruction.opCode());

			newInst.intValue = instruction.intValue();
			newInst.charValue = instruction.charValue();
			newInst.floatValue = instruction.floatValue();
			newInst.stringValue = instruction.stringValue();

			if (instruction.callParameters().size() > 0) {
				for (auto parameter : instruction.callParameters()) {
					newInst.parameters.push_back(LoaderHelpers::getType(vmState, parameter));
				}
			}

			if (instruction.calledClassType() != "") {
				newInst.classType = LoaderHelpers::getClassType(vmState, instruction.calledClassType());
			}

			return newInst;
		}
	}

	FunctionLoader::FunctionLoader(VMState& vmState)
		: mVMState(vmState) {

	}

	void FunctionLoader::generateDefinition(const Loader::Function& function, FunctionDefinition& definition) {
		auto returnType = LoaderHelpers::getType(mVMState, function.returnType());

		std::vector<const Type*> parameters;
		for (auto param : function.parameters()) {
			parameters.push_back(LoaderHelpers::getType(mVMState, param));
		}

		const ClassType* classType = nullptr;
		AccessModifier accessModifier = DEFAULT_ACCESS_MODIFIER;
		bool isVirtual = false;

		if (function.isMemberFunction()) {
			classType = dynamic_cast<const ClassType*>(LoaderHelpers::getType(mVMState, "Ref." + function.className()));
			if (classType == nullptr) {
				throw std::runtime_error("'" + function.className() + "' is not a class type.");
			}

			accessModifier = LoaderHelpers::getAccessModifier(function.attributes());
			isVirtual = LoaderHelpers::getIsVirtual(function.attributes());
		}

		definition = FunctionDefinition(
			function.isMemberFunction() ? function.memberFunctionName() : function.name(),
			parameters,
			returnType,
			classType,
			accessModifier,
			function.memberFunctionName() == ".constructor",
			isVirtual);
	}

	void FunctionLoader::loadExternal(const Loader::Function& function,	FunctionDefinition& loadedFunction) {
		if (!function.isExternal()) {
			throw std::runtime_error("Expected an external function");
		}

		generateDefinition(function, loadedFunction);
		auto signature = FunctionSignature::from(loadedFunction).str();

		//Check if defined
		if (!mVMState.binder().isDefined(signature)) {
			throw std::runtime_error("The external function '" + signature + "' is not defined.");
		}
	}

	ManagedFunction* FunctionLoader::loadManaged(const Loader::Function& function, const FunctionDefinition& functionDefinition) {
		if (function.isExternal()) {
			throw std::runtime_error("Expected a managed function");
		}

		auto loadedFunc = new ManagedFunction(functionDefinition);

		//Locals
		loadedFunc->setNumLocals(function.localTypes().size());
		for (std::size_t local = 0; local < function.localTypes().size(); local++) {
			auto localType = function.localTypes()[local];

			if (localType != "") {
				loadedFunc->setLocal(local, LoaderHelpers::getType(mVMState, localType));
			}
		}

		//Instructions
		for (auto& inst : function.instructions()) {
			loadedFunc->instructions().push_back(loadInstruction(mVMState, inst));
		}

		return loadedFunc;
	}
}