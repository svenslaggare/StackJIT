#include "loader.h"
#include "../core/functionsignature.h"
#include "../type/classmetadata.h"

namespace stackjit {
	Loader::Instruction::Instruction() {

	}

	Loader::Instruction Loader::Instruction::make(OpCodes opCode) {
		Loader::Instruction instruction;
		instruction.opCode = opCode;
		instruction.format = InstructionFormats::OpCodeOnly;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithInt(OpCodes opCode, int value) {
		Loader::Instruction instruction;
		instruction.intValue = value;
		instruction.opCode = opCode;
		instruction.format = InstructionFormats::IntData;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithFloat(OpCodes opCode, float value) {
		Loader::Instruction instruction;
		instruction.floatValue = value;
		instruction.opCode = opCode;
		instruction.format = InstructionFormats::FloatData;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithChar(OpCodes opCode, char value) {
		Loader::Instruction instruction;
		instruction.charValue = value;
		instruction.opCode = opCode;
		instruction.format = InstructionFormats::CharData;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithString(OpCodes opCode, std::string value) {
		Loader::Instruction instruction;
		instruction.stringValue = value;
		instruction.opCode = opCode;
		instruction.format = InstructionFormats::StringData;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithStringConstant(OpCodes opCode, std::string value) {
		Loader::Instruction instruction;
		instruction.stringValue = value;
		instruction.opCode = opCode;
		instruction.format = InstructionFormats::StringConstantData;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeCall(std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction instruction;
		instruction.stringValue = funcName;
		instruction.parameters = parameters;
		instruction.opCode = OpCodes::CALL;
		instruction.format = InstructionFormats::Call;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeCallInstance(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction instruction;
		instruction.calledClassType = classType;
		instruction.stringValue = funcName;
		instruction.parameters = parameters;
		instruction.opCode = OpCodes::CALL_INSTANCE;
		instruction.format = InstructionFormats::CallInstance;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeCallVirtual(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction instruction;
		instruction.calledClassType = classType;
		instruction.stringValue = funcName;
		instruction.parameters = parameters;
		instruction.opCode = OpCodes::CALL_VIRTUAL;
		instruction.format = InstructionFormats::CallInstance;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeNewObject(std::string classType, std::vector<std::string> parameters) {
		Loader::Instruction instruction;
		instruction.calledClassType = classType;
		instruction.stringValue = ".constructor";
		instruction.parameters = parameters;
		instruction.opCode = OpCodes::NEW_OBJECT;
		instruction.format = InstructionFormats::CallInstance;
		return instruction;
	}

	Loader::Attribute::Attribute(std::string name)
		: mName(name) {

	}

	std::string Loader::Attribute::name() const {
		return mName;
	}

	const std::unordered_map<std::string, std::string>& Loader::Attribute::values() const {
		return mValues;
	}

	std::unordered_map<std::string, std::string>& Loader::Attribute::values() {
		return mValues;
	}

	Loader::Function::Function()
		: isMemberFunction(false), isExternal(false) {

	}

	void Loader::Function::setNumLocals(int num) {
		localTypes.resize((std::size_t)num);
	}

	std::size_t Loader::Function::numLocals() const {
		return localTypes.size();
	}

	Loader::Field::Field(std::string name, std::string type)
		: mName(name), mType(type) {

	}

	std::string Loader::Field::name() const {
		return mName;
	}

	std::string Loader::Field::type() const {
		return mType;
	}

	const Loader::AttributeContainer& Loader::Field::attributes() const {
		return mAttributes;
	}

	Loader::AttributeContainer& Loader::Field::attributes() {
		return mAttributes;
	}

	Loader::Class::Class(std::string name)
		: mName(name) {

	}

	Loader::Class::Class() {

	}

	std::string Loader::Class::name() const {
		return mName;
	}

	const std::vector<Loader::Field>& Loader::Class::fields() const {
		return mFields;
	}

	std::vector<Loader::Field>& Loader::Class::fields() {
		return mFields;
	}

	std::string Loader::Class::parentClassName() const {
		return mParentClassName;
	}

	std::string& Loader::Class::parentClassName() {
		return mParentClassName;
	}

	const Loader::AttributeContainer& Loader::Class::attributes() const {
		return mAttributes;
	}

	Loader::AttributeContainer& Loader::Class::attributes() {
		return mAttributes;
	}

	Loader::Assembly::Assembly(std::string name)
		: mName(name) {

	}

	std::string Loader::Assembly::name() const {
		return mName;
	}

	const std::vector<Loader::Function>& Loader::Assembly::functions() const {
		return mFunctions;
	}

	std::vector<Loader::Function>& Loader::Assembly::functions() {
		return mFunctions;
	}

	const std::vector<Loader::Class>& Loader::Assembly::classes() const {
		return mClasses;
	}

	std::vector<Loader::Class>& Loader::Assembly::classes() {
		return mClasses;
	}

	std::string Loader::getSignature(const Loader::Function& function) {
		return FunctionSignature::createSignature<std::string>(function.name, function.parameters, [](std::string str) { return str; });
	}
}
