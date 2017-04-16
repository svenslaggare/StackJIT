#include "parser.h"
#include "../core/functionsignature.h"
#include "../type/classmetadata.h"
#include <cctype>
#include <string>
#include <iostream>
#include <unordered_map>

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

	namespace {
		std::string toLower(std::string str) {
			std::string newStr { "" };
			auto length = str.length();

			for (std::size_t i = 0; i < length; i++) {
				newStr += std::tolower(str[i]);
			}

			return newStr;
		}

		const std::unordered_map<std::string, OpCodes> noOperandsInstructions	{
			{ "nop", OpCodes::NOP },
			{ "pop", OpCodes::POP },
			{ "dup", OpCodes::DUPLICATE },
			{ "add", OpCodes::ADD },
			{ "sub", OpCodes::SUB },
			{ "mul", OpCodes::MUL },
			{ "div", OpCodes::DIV },
			{ "ldtrue", OpCodes::LOAD_TRUE},
			{ "ldfalse", OpCodes::LOAD_FALSE},
			{ "and", OpCodes::AND },
			{ "or", OpCodes::OR },
			{ "not", OpCodes::NOT },
			{ "convinttofloat", OpCodes::CONVERT_INT_TO_FLOAT },
			{ "convfloattoint", OpCodes::CONVERT_FLOAT_TO_INT },
			{ "cmpeq", OpCodes::COMPARE_EQUAL },
			{ "cmpne", OpCodes::COMPARE_NOT_EQUAL },
			{ "cmpgt", OpCodes::COMPARE_GREATER_THAN },
			{ "cmpge", OpCodes::COMPARE_GREATER_THAN_OR_EQUAL },
			{ "cmplt", OpCodes::COMPARE_LESS_THAN },
			{ "cmple", OpCodes::COMPARE_LESS_THAN_OR_EQUAL },
			{ "ldnull", OpCodes::LOAD_NULL},
			{ "ldlen", OpCodes::LOAD_ARRAY_LENGTH },
			{ "ret", OpCodes::RET }
		};

		const std::unordered_map<std::string, OpCodes> branchInstructions	{
			{ "beq", OpCodes::BRANCH_EQUAL },
			{ "bne", OpCodes::BRANCH_NOT_EQUAL },
			{ "bgt", OpCodes::BRANCH_GREATER_THAN },
			{ "bge", OpCodes::BRANCH_GREATER_THAN_OR_EQUAL },
			{ "blt", OpCodes::BRANCH_LESS_THAN },
			{ "ble", OpCodes::BRANCH_LESS_THAN_OR_EQUAL }
		};

		const std::unordered_map<std::string, OpCodes> stringOperandInstructions	{
			{ "newarr", OpCodes::NEW_ARRAY },
			{ "stelem", OpCodes::STORE_ELEMENT },
			{ "ldelem", OpCodes::LOAD_ELEMENT },
			{ "stfield", OpCodes::STORE_FIELD },
			{ "ldfield", OpCodes::LOAD_FIELD }
		};
	}

	std::string AssemblyParser::getSignature(const AssemblyParser::Function& function) {
		return FunctionSignature::createSignature<std::string>(function.name, function.parameters, [](std::string str) { return str; });
	}

	std::vector<std::string> AssemblyParser::tokenize(std::istream& stream) {
		std::vector<std::string> tokens;
		std::string token;
		bool isComment = false;
		bool isString = false;
		bool escape = false;

		char c;
		while (stream.get(c)) {
			bool newToken = false;
			bool newIdentifier = false;

			if (!isComment && c == '#') {
				isComment = true;
				continue;
			}

			if (isComment && c == '\n') {
				isComment = false;
				continue;
			}

			if (!isComment) {
				if (!escape) {
					if (c == '\\') {
						escape = true;
						continue;
					}

					if (c == '"') {
						if (isString) {
							tokens.push_back(token);
							token = "";
						}

						isString = !isString;
						continue;
					}
				}

				if (isspace(c) && !isString) {
					newToken = true;
				}

				if (c == '(' || c == ')') {
					newToken = true;
					newIdentifier = true;
				}

				if (c == '@') {
					newToken = true;
					newIdentifier = true;
				}

				if (c == '=') {
					newToken = true;
					newIdentifier = true;
				}

				if (newToken) {
					if (token != "") {
						tokens.push_back(token);
					}

					token = "";
				} else {
					token += c;
				}

				if (newIdentifier) {
					tokens.push_back(std::string { c });
				}
			}

			if (escape) {
				escape = false;
			}
		}

		if (token != "") {
			tokens.push_back(token);
		}

		return tokens;
	}

	void AssemblyParser::load(std::istream& stream, AssemblyParser::Assembly& assembly) {
		ByteCodeParser byteCodeParser(AssemblyParser::tokenize(stream));
		byteCodeParser.parse(assembly);
	}

	AssemblyParser::ByteCodeParser::ByteCodeParser(std::vector<std::string> tokens)
		: mTokens(tokens) {

	}

	std::string AssemblyParser::ByteCodeParser::currentToken() const {
		return mTokens[mTokenIndex];
	}

	std::string AssemblyParser::ByteCodeParser::currentTokenToLower() const {
		return toLower(currentToken());
	}

	std::string AssemblyParser::ByteCodeParser::nextToken() {
		mTokenIndex++;
		if (mTokenIndex >= mTokens.size()) {
			throw std::runtime_error("Reached end of tokens");
		}

		return mTokens[mTokenIndex];
	}

	std::string AssemblyParser::ByteCodeParser::peekNextToken() {
		if (mTokens.size() >= mTokenIndex + 1) {
			return mTokens[mTokenIndex + 1];
		} else {
			throw std::runtime_error("Reached end of tokens.");
		}
	}

	void AssemblyParser::ByteCodeParser::parseFunctionDef(AssemblyParser::Function& function) {
		function.name = nextToken();

		if (nextToken() != "(") {
			throw std::runtime_error("Expected '(' after function name.");
		}

		while (true) {
			std::string param = nextToken();

			if (param == ")") {
				break;
			}

			function.parameters.push_back(param);
		}

		function.returnType = nextToken();
	}

	void AssemblyParser::ByteCodeParser::readCallParameters(std::vector<std::string>& parameters) {
		while (true) {
			auto param = nextToken();

			if (param == ")") {
				break;
			}

			parameters.push_back(param);
		}
	}

	void AssemblyParser::ByteCodeParser::parseAttribute(AssemblyParser::AttributeContainer& container) {
		auto attributeName = nextToken();

		if (nextToken() != "(") {
			throw std::runtime_error("Expected '(' after attribute name");
		}

		if (container.count(attributeName) > 0) {
			throw std::runtime_error("The attribute '" + attributeName + "' is already defined.'");
		}

		AssemblyParser::Attribute attribute;
		attribute.name = attributeName;

		while (true) {
			auto key = nextToken();

			if (key == ")") {
				break;
			}

			if (nextToken() != "=") {
				throw std::runtime_error("Expected '=' after name in attribute.");
			}

			auto value = nextToken();

			if (attribute.values.count(key) == 0) {
				attribute.values.insert({ key, value });
			} else {
				throw std::runtime_error("The key '" + key + "' is already defined in the attribute '" + attributeName + "'.");
			}
		}

		container.insert({ attributeName, attribute });
	}

	bool AssemblyParser::ByteCodeParser::parseFunctionBody(AssemblyParser::Function& currentFunction) {
		using namespace AssemblyParser;
		auto currentToLower = currentTokenToLower();

		if (currentToLower == "@") {
			parseAttribute(currentFunction.attributes);
			return true;
		}

		if (currentToLower == "ldint") {
			int value = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(OpCodes::LOAD_INT, value));
			return true;
		}

		if (currentToLower == "ldfloat") {
			float value = stof(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithFloat(OpCodes::LOAD_FLOAT, value));
			return true;
		}

		if (currentToLower == "ldchar") {
			char value = (char)stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithChar(OpCodes::LOAD_CHAR, value));
			return true;
		}

		if (noOperandsInstructions.count(currentToLower) > 0) {
			currentFunction.instructions.push_back(Instruction::make(noOperandsInstructions.at(currentToLower)));
			return true;
		}

		if (stringOperandInstructions.count(currentToLower) > 0) {
			std::string value = nextToken();
			currentFunction.instructions.push_back(Instruction::makeWithString(stringOperandInstructions.at(currentToLower), value));
			return true;
		}

		if (currentToLower == ".locals") {
			if (!mLocalsSet) {
				int localsCount = stoi(nextToken());

				if (localsCount >= 0) {
					mLocalsSet = true;
					currentFunction.setNumLocals(localsCount);
				} else {
					throw std::runtime_error("The number of locals must be >= 0.");
				}

				return true;
			} else {
				throw std::runtime_error("The locals has already been set.");
			}
		}

		if (currentToLower == ".local") {
			if (mLocalsSet) {
				int localIndex = stoi(nextToken());
				auto localType = nextToken();

				if (localIndex >= 0 && localIndex < (int)currentFunction.numLocals()) {
					currentFunction.localTypes.at((std::size_t)localIndex) = localType;
				} else {
					throw std::runtime_error("Invalid local index.");
				}

				return true;
			} else {
				throw std::runtime_error("The locals must been set.");
			}
		}

		if (currentToLower == "ldloc" || currentToLower == "stloc") {
			if (!mLocalsSet) {
				throw std::runtime_error("The locals must be set.");
			}

			int local = stoi(nextToken());
			auto opCode = currentToLower == "ldloc" ? OpCodes::LOAD_LOCAL : OpCodes::STORE_LOCAL;

			if (local >= 0 && local < (int)currentFunction.numLocals()) {
				currentFunction.instructions.push_back(Instruction::makeWithInt(opCode, local));
				return true;
			} else {
				throw std::runtime_error("The local index is out of range.");
			}
		}

		if (currentToLower == "call" || currentToLower == "callinst" || currentToLower == "callvirt") {
			bool isInstance = currentToLower == "callinst" || currentToLower == "callvirt";
			bool isVirtual = currentToLower == "callvirt";

			std::string funcName = nextToken();
			std::string classType = "";

			if (isInstance) {
				auto classNamePos = funcName.find("::");

				if (classNamePos != std::string::npos) {
					classType = funcName.substr(0, classNamePos);
				} else {
					throw std::runtime_error("Expected '::' in called member function.");
				}

				funcName = funcName.substr(classNamePos + 2);
			}

			if (nextToken() != "(") {
				throw std::runtime_error("Expected '(' after called function.");
			}

			std::vector<std::string> parameters;
			readCallParameters(parameters);

			if (isInstance) {
				if (!isVirtual) {
					currentFunction.instructions.push_back(Instruction::makeCallInstance(classType, funcName, parameters));
				} else {
					currentFunction.instructions.push_back(Instruction::makeCallVirtual(classType, funcName, parameters));
				}
			} else {
				currentFunction.instructions.push_back(Instruction::makeCall(funcName, parameters));
			}

			return true;
		}

		if (currentToLower == "ldarg") {
			int argNum = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(OpCodes::LOAD_ARG, argNum));
			return true;
		}

		if (currentToLower == "newobj") {
			std::string funcName = nextToken();
			std::string classType = "";

			auto classNamePos = funcName.find("::");

			if (classNamePos != std::string::npos) {
				classType = funcName.substr(0, classNamePos);
			} else {
				throw std::runtime_error("Expected '::' after the type in a new object instruction.");
			}

			funcName = funcName.substr(classNamePos + 2);

			if (funcName != ".constructor") {
				throw std::runtime_error("Expected call to constructor.");
			}

			if (nextToken() != "(") {
				throw std::runtime_error("Expected '(' after called function.");
			}

			std::vector<std::string> parameters;
			readCallParameters(parameters);
			currentFunction.instructions.push_back(Instruction::makeNewObject(classType, parameters));
			return true;
		}

		if (currentToLower == "br") {
			int target = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(OpCodes::BRANCH, target));
			return true;
		}

		if (branchInstructions.count(currentToLower) > 0) {
			int target = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(branchInstructions.at(currentToLower), target));
			return true;
		}

		if (currentToLower == "ldstr") {
			auto str = nextToken();
			currentFunction.instructions.push_back(Instruction::makeWithStringConstant(OpCodes::LOAD_STRING, str));
			return true;
		}

		throw std::runtime_error("'" + currentToken() + "' is not a valid instruction.");
	}

	bool AssemblyParser::ByteCodeParser::parseClassBody(AssemblyParser::Class& currentClass, AssemblyParser::Field*& currentField) {
		auto current = currentToken();
		auto currentToLower = currentTokenToLower();

		if (currentToLower == "@") {
			if (currentField == nullptr) {
				parseAttribute(currentClass.attributes); //Class attribute
			} else {
				parseAttribute(currentField->attributes); //Field attribute
			}

			return true;
		}

		AssemblyParser::Field field;
		field.name = current;
		field.type = nextToken();

		currentClass.fields.push_back(field);
		currentField = &currentClass.fields.back();
		return false;
	}

	void AssemblyParser::ByteCodeParser::parse(AssemblyParser::Assembly& assembly) {
		Function currentFunc;
		Class currentClass;
		Field* currentField = nullptr;

		for (mTokenIndex = 0; mTokenIndex < mTokens.size(); mTokenIndex++) {
			auto current = currentToken();
			auto currentToLower = toLower(current);

			//Bodies
			if (mIsFunctionBody) {
				if (currentToLower == "}") {
					mIsFunctionBody = false;
					mIsFunction = false;
					assembly.functions.push_back(currentFunc);
					continue;
				}

				if (parseFunctionBody(currentFunc)) {
					continue;
				}
			}

			if (mIsClassBody) {
				if (currentToLower == "}") {
					assembly.classes.push_back(currentClass);
					mIsClass = false;
					mIsClassBody = false;
					currentField = nullptr;
					continue;
				}

				if (parseClassBody(currentClass, currentField)) {
					continue;
				}
			}

			//Definitions
			bool isFuncDef = false;
			bool isExternFunc = false;
			bool isMemberDef = false;

			if (!mIsFunction && !mIsClass && !isExternFunc) {
				if (currentToLower == "func") {
					isFuncDef = true;
					mIsFunction = true;
				} else if (currentToLower == "class") {
					currentClass = {};
					currentClass.name = nextToken();

					if (peekNextToken() == "extends") {
						nextToken();
						currentClass.parentClassName = nextToken();
					}

					mIsClass = true;
				} else if (currentToLower == "extern") {
					isExternFunc = true;
				} else if (currentToLower == "member") {
					isMemberDef = true;
				} else {
					throw std::runtime_error("Invalid identifier '" + current + "'");
				}
			}

			if (mIsFunction && !isFuncDef && currentToLower == "{") {
				mIsFunctionBody = true;
			}

			if (mIsClass && currentToLower == "{") {
				mIsClassBody = true;
			}

			//Parse function definition
			if (isFuncDef) {
				currentFunc = {};
				parseFunctionDef(currentFunc);

				if (currentFunc.name.find("::") != std::string::npos) {
					throw std::runtime_error("'::' is only allowed in member functions.");
				}

				mLocalsSet = false;
			}

			//Parse external function
			if (isExternFunc) {
				currentFunc = {};
				parseFunctionDef(currentFunc);
				currentFunc.isExternal = true;
				assembly.functions.push_back(currentFunc);
			}

			//Parse member function
			if (isMemberDef) {
				currentFunc = {};
				parseFunctionDef(currentFunc);

				auto funcName = currentFunc.name;

				//Get the class name
				auto classNamePosition = funcName.find("::");
				if (classNamePosition == std::string::npos) {
					throw std::runtime_error("Expected '::' in member function name.");
				}

				auto classTypeName = funcName.substr(0, classNamePosition);
				auto memberFunctionName = funcName.substr(classNamePosition + 2);

				currentFunc.className = classTypeName;
				currentFunc.memberFunctionName = memberFunctionName;
				currentFunc.isMemberFunction = true;

				mLocalsSet = false;
				mIsFunction = true;
			}
		}
	}
}
