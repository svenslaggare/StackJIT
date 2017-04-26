#include "loader.h"
#include "../core/functionsignature.h"
#include "../type/classmetadata.h"

namespace stackjit {
	Loader::Instruction::Instruction(Loader::InstructionFormats format, OpCodes opCode)
		: mFormat(format), mOpCode(opCode) {

	}

	Loader::InstructionFormats Loader::Instruction::format() const {
		return mFormat;
	}

	OpCodes Loader::Instruction::opCode() const {
		return mOpCode;
	}

	float Loader::Instruction::floatValue() const {
		return mFloatValue;
	}

	int Loader::Instruction::intValue() const {
		return mIntValue;
	}

	char Loader::Instruction::charValue() const {
		return mCharValue;
	}

	const std::string& Loader::Instruction::stringValue() const {
		return mStringValue;
	}

	const std::vector<std::string>& Loader::Instruction::callParameters() const {
		return mCallParameters;
	}

	const std::string& Loader::Instruction::calledClassType() const {
		return mCalledClassType;
	}

	Loader::Instruction Loader::Instruction::make(OpCodes opCode) {
		return Loader::Instruction(InstructionFormats::OpCodeOnly, opCode);
	}

	Loader::Instruction Loader::Instruction::makeWithInt(OpCodes opCode, int value) {
		Loader::Instruction instruction(InstructionFormats::IntData, opCode);
		instruction.mIntValue = value;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithFloat(OpCodes opCode, float value) {
		Loader::Instruction instruction(InstructionFormats::FloatData, opCode);
		instruction.mFloatValue = value;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithChar(OpCodes opCode, char value) {
		Loader::Instruction instruction(InstructionFormats::CharData, opCode);
		instruction.mCharValue = value;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithString(OpCodes opCode, std::string value) {
		Loader::Instruction instruction(InstructionFormats::StringData, opCode);
		instruction.mStringValue = value;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeWithStringConstant(OpCodes opCode, std::string value) {
		Loader::Instruction instruction(InstructionFormats::StringConstantData, opCode);
		instruction.mStringValue = value;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeCall(std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction instruction(InstructionFormats::Call, OpCodes::CALL);
		instruction.mStringValue = funcName;
		instruction.mCallParameters = parameters;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeCallInstance(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction instruction(InstructionFormats::CallInstance, OpCodes::CALL_INSTANCE);
		instruction.mCalledClassType = classType;
		instruction.mStringValue = funcName;
		instruction.mCallParameters = parameters;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeCallVirtual(std::string classType, std::string funcName, std::vector<std::string> parameters) {
		Loader::Instruction instruction(InstructionFormats::CallInstance, OpCodes::CALL_VIRTUAL);
		instruction.mCalledClassType = classType;
		instruction.mStringValue = funcName;
		instruction.mCallParameters = parameters;
		return instruction;
	}

	Loader::Instruction Loader::Instruction::makeNewObject(std::string classType, std::vector<std::string> parameters) {
		Loader::Instruction instruction(InstructionFormats::CallInstance, OpCodes::NEW_OBJECT);
		instruction.mCalledClassType = classType;
		instruction.mStringValue = ".constructor";
		instruction.mCallParameters = parameters;
		return instruction;
	}

	Loader::Attribute::Attribute(std::string name)
		: mName(name) {

	}

	const std::string& Loader::Attribute::name() const {
		return mName;
	}

	const std::unordered_map<std::string, std::string>& Loader::Attribute::values() const {
		return mValues;
	}

	std::unordered_map<std::string, std::string>& Loader::Attribute::values() {
		return mValues;
	}

	Loader::Function::Function()
			: mIsMemberFunction(false),
			  mIsExternal(false) {

	}

	Loader::Function::Function(std::string name, std::string returnType, const std::vector<std::string>& parameters, bool isExternal)
			: mName(name),
			  mReturnType(returnType),
			  mParameters(parameters),
			  mIsMemberFunction(false),
			  mIsExternal(isExternal) {

	}

	std::string Loader::Function::name() const {
		return mName;
	}

	std::string Loader::Function::returnType() const {
		return mReturnType;
	}

	const std::vector<std::string>& Loader::Function::parameters() const {
		return mParameters;
	}

	bool Loader::Function::isExternal() const {
		return mIsExternal;
	}

	bool Loader::Function::isMemberFunction() const {
		return mIsMemberFunction;
	}

	bool& Loader::Function::isMemberFunction() {
		return mIsMemberFunction;
	}

	std::string Loader::Function::className() const {
		return mClassName;
	}

	std::string& Loader::Function::className() {
		return mClassName;
	}

	std::string Loader::Function::memberFunctionName() const {
		return mMemberFunctionName;
	}

	std::string& Loader::Function::memberFunctionName() {
		return mMemberFunctionName;
	}

	const std::vector<Loader::Instruction>& Loader::Function::instructions() const {
		return mInstructions;
	}

	std::vector<Loader::Instruction>& Loader::Function::instructions() {
		return mInstructions;
	}

	const std::vector<std::string>& Loader::Function::localTypes() const {
		return mLocalTypes;
	}

	std::vector<std::string>& Loader::Function::localTypes() {
		return mLocalTypes;
	}

	const Loader::AttributeContainer& Loader::Function::attributes() const {
		return mAttributes;
	}

	Loader::AttributeContainer& Loader::Function::attributes() {
		return mAttributes;
	}

	void Loader::Function::setNumLocals(int num) {
		mLocalTypes.resize((std::size_t)num);
	}

	std::size_t Loader::Function::numLocals() const {
		return mLocalTypes.size();
	}

	std::string Loader::Function::toString() const {
		std::string parametersString = "";
		bool isFirst = true;

		for (auto parameter : mParameters) {
			if (isFirst) {
				isFirst = false;
			} else {
				parametersString += " ";
			}

			parametersString += parameter;
		}

		return mName + "(" + parametersString + ") " + mReturnType;
	}

	Loader::Field::Field(std::string name, std::string type)
		: mName(name), mType(type) {

	}

	const std::string& Loader::Field::name() const {
		return mName;
	}

	const std::string& Loader::Field::type() const {
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

	const std::string& Loader::Class::name() const {
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

	const std::string& Loader::Assembly::name() const {
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
		return FunctionSignature::createSignature<std::string>(function.name(), function.parameters(), [](std::string str) { return str; });
	}
}
