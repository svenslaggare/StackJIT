#include "parser.h"
#include "../core/functionsignature.h"
#include "../type/classmetadata.h"

namespace stackjit {
	AssemblyParser::Instruction::Instruction() {

	}

	AssemblyParser::Instruction AssemblyParser::Instruction::make(OpCodes opCode) {
		AssemblyParser::Instruction inst;
		inst.opCode = opCode;
		inst.format = InstructionFormats::OpCodeOnly;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeWithInt(OpCodes opCode, int value) {
		AssemblyParser::Instruction inst;
		inst.intValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::IntData;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeWithFloat(OpCodes opCode, float value) {
		AssemblyParser::Instruction inst;
		inst.floatValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::FloatData;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeWithChar(OpCodes opCode, char value) {
		AssemblyParser::Instruction inst;
		inst.charValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::CharData;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeWithString(OpCodes opCode, std::string value) {
		AssemblyParser::Instruction inst;
		inst.stringValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::StringData;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeWithStringConstant(OpCodes opCode, std::string value) {
		AssemblyParser::Instruction inst;
		inst.stringValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::StringConstantData;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeCall(std::string funcName, std::vector<std::string> parameters) {
		AssemblyParser::Instruction inst;
		inst.stringValue = funcName;
		inst.parameters = parameters;
		inst.opCode = OpCodes::CALL;
		inst.format = InstructionFormats::Call;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeCallInstance(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		AssemblyParser::Instruction inst;
		inst.calledClassType = classType;
		inst.stringValue = funcName;
		inst.parameters = parameters;
		inst.opCode = OpCodes::CALL_INSTANCE;
		inst.format = InstructionFormats::CallInstance;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeCallVirtual(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		AssemblyParser::Instruction inst;
		inst.calledClassType = classType;
		inst.stringValue = funcName;
		inst.parameters = parameters;
		inst.opCode = OpCodes::CALL_VIRTUAL;
		inst.format = InstructionFormats::CallInstance;
		return inst;
	}

	AssemblyParser::Instruction AssemblyParser::Instruction::makeNewObject(std::string classType, std::vector<std::string> parameters) {
		AssemblyParser::Instruction inst;
		inst.calledClassType = classType;
		inst.stringValue = ".constructor";
		inst.parameters = parameters;
		inst.opCode = OpCodes::NEW_OBJECT;
		inst.format = InstructionFormats::CallInstance;
		return inst;
	}

	AssemblyParser::Function::Function()
		: isMemberFunction(false), isExternal(false) {

	}

	void AssemblyParser::Function::setNumLocals(int num) {
		localTypes.resize((std::size_t)num);
	}

	std::size_t AssemblyParser::Function::numLocals() const {
		return localTypes.size();
	}

	AssemblyParser::Class::Class() {

	}

	std::string AssemblyParser::getSignature(const AssemblyParser::Function& function) {
		return FunctionSignature::createSignature<std::string>(function.name, function.parameters, [](std::string str) { return str; });
	}
}
