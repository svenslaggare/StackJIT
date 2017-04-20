#include "loader.h"
#include "../core/functionsignature.h"
#include "../type/classmetadata.h"

namespace stackjit {
	Loader::Instruction::Instruction() {

	}

	Loader::Instruction Loader::Instruction::make(OpCodes opCode) {
		Loader::Instruction inst;
		inst.opCode = opCode;
		inst.format = InstructionFormats::OpCodeOnly;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeWithInt(OpCodes opCode, int value) {
		Loader::Instruction inst;
		inst.intValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::IntData;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeWithFloat(OpCodes opCode, float value) {
		Loader::Instruction inst;
		inst.floatValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::FloatData;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeWithChar(OpCodes opCode, char value) {
		Loader::Instruction inst;
		inst.charValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::CharData;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeWithString(OpCodes opCode, std::string value) {
		Loader::Instruction inst;
		inst.stringValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::StringData;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeWithStringConstant(OpCodes opCode, std::string value) {
		Loader::Instruction inst;
		inst.stringValue = value;
		inst.opCode = opCode;
		inst.format = InstructionFormats::StringConstantData;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeCall(std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction inst;
		inst.stringValue = funcName;
		inst.parameters = parameters;
		inst.opCode = OpCodes::CALL;
		inst.format = InstructionFormats::Call;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeCallInstance(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction inst;
		inst.calledClassType = classType;
		inst.stringValue = funcName;
		inst.parameters = parameters;
		inst.opCode = OpCodes::CALL_INSTANCE;
		inst.format = InstructionFormats::CallInstance;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeCallVirtual(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction inst;
		inst.calledClassType = classType;
		inst.stringValue = funcName;
		inst.parameters = parameters;
		inst.opCode = OpCodes::CALL_VIRTUAL;
		inst.format = InstructionFormats::CallInstance;
		return inst;
	}

	Loader::Instruction Loader::Instruction::makeNewObject(std::string classType, std::vector<std::string> parameters) {
		Loader::Instruction inst;
		inst.calledClassType = classType;
		inst.stringValue = ".constructor";
		inst.parameters = parameters;
		inst.opCode = OpCodes::NEW_OBJECT;
		inst.format = InstructionFormats::CallInstance;
		return inst;
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
