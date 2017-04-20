#include "bytecodeparser.h"
#include <cctype>
#include <string>
#include <iostream>
#include <unordered_map>

namespace stackjit {
	namespace {
		std::string toLower(std::string str) {
			std::string newString { "" };
			auto length = str.length();

			for (std::size_t i = 0; i < length; i++) {
				newString += std::tolower(str[i]);
			}

			return newString;
		}

		const std::unordered_map<std::string, OpCodes> noOperandsInstructions {
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

		const std::unordered_map<std::string, OpCodes> branchInstructions {
			{ "beq", OpCodes::BRANCH_EQUAL },
			{ "bne", OpCodes::BRANCH_NOT_EQUAL },
			{ "bgt", OpCodes::BRANCH_GREATER_THAN },
			{ "bge", OpCodes::BRANCH_GREATER_THAN_OR_EQUAL },
			{ "blt", OpCodes::BRANCH_LESS_THAN },
			{ "ble", OpCodes::BRANCH_LESS_THAN_OR_EQUAL }
		};

		const std::unordered_map<std::string, OpCodes> stringOperandInstructions {
			{ "newarr", OpCodes::NEW_ARRAY },
			{ "stelem", OpCodes::STORE_ELEMENT },
			{ "ldelem", OpCodes::LOAD_ELEMENT },
			{ "stfield", OpCodes::STORE_FIELD },
			{ "ldfield", OpCodes::LOAD_FIELD }
		};
	}

	//Tokenizes the given stream
	std::vector<std::string> tokenize(std::istream& stream) {
		std::vector<std::string> tokens;
		std::string token;
		bool isComment = false;
		bool isString = false;
		bool escape = false;

		char currentChar;
		while (stream.get(currentChar)) {
			bool newToken = false;
			bool newIdentifier = false;

			if (!isComment && currentChar == '#') {
				isComment = true;
				continue;
			}

			if (isComment && currentChar == '\n') {
				isComment = false;
				continue;
			}

			if (!isComment) {
				if (!escape) {
					if (currentChar == '\\') {
						escape = true;
						continue;
					}

					if (currentChar == '"') {
						if (isString) {
							tokens.push_back(token);
							token = "";
						}

						isString = !isString;
						continue;
					}
				}

				if (isspace(currentChar) && !isString) {
					newToken = true;
				}

				if (currentChar == '(' || currentChar == ')') {
					newToken = true;
					newIdentifier = true;
				}

				if (currentChar == '@') {
					newToken = true;
					newIdentifier = true;
				}

				if (currentChar == '=') {
					newToken = true;
					newIdentifier = true;
				}

				if (newToken) {
					if (token != "") {
						tokens.push_back(token);
					}

					token = "";
				} else {
					token += currentChar;
				}

				if (newIdentifier) {
					tokens.push_back(std::string {currentChar});
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

	ByteCodeParser::ByteCodeParser(std::vector<std::string> tokens)
			: mTokens(tokens) {

	}

	ByteCodeParser::ByteCodeParser(std::istream& stream)
		: mTokens(tokenize(stream)) {

	}

	std::string ByteCodeParser::currentToken() const {
		return mTokens[mTokenIndex];
	}

	std::string ByteCodeParser::currentTokenToLower() const {
		return toLower(currentToken());
	}

	std::string ByteCodeParser::nextToken() {
		mTokenIndex++;
		if (mTokenIndex >= mTokens.size()) {
			throw std::runtime_error("Reached end of tokens");
		}

		return mTokens[mTokenIndex];
	}

	std::string ByteCodeParser::peekNextToken() {
		if (mTokens.size() >= mTokenIndex + 1) {
			return mTokens[mTokenIndex + 1];
		} else {
			throw std::runtime_error("Reached end of tokens.");
		}
	}

	void ByteCodeParser::nextTokenAtEnd() {
		if (mTokenIndex != mTokens.size() - 1) {
			nextToken();
		} else {
			mTokenIndex++;
		}
	}

	void ByteCodeParser::parseFunctionDefinition(Loader::Function& function) {
		function.name = nextToken();

		if (nextToken() != "(") {
			throw std::runtime_error("Expected '(' after function name.");
		}

		while (true) {
			auto parameter = nextToken();
			if (parameter == ")") {
				break;
			}

			function.parameters.push_back(parameter);
		}

		function.returnType = nextToken();
	}

	void ByteCodeParser::readCallParameters(std::vector<std::string>& parameters) {
		while (true) {
			auto parameter = nextToken();
			if (parameter == ")") {
				break;
			}

			parameters.push_back(parameter);
		}
	}

	void ByteCodeParser::parseAttribute(Loader::AttributeContainer& container) {
		auto attributeName = nextToken();

		if (nextToken() != "(") {
			throw std::runtime_error("Expected '(' after attribute name");
		}

		if (container.count(attributeName) > 0) {
			throw std::runtime_error("The attribute '" + attributeName + "' is already defined.'");
		}

		Loader::Attribute attribute(attributeName);

		while (true) {
			auto key = nextToken();

			if (key == ")") {
				break;
			}

			if (nextToken() != "=") {
				throw std::runtime_error("Expected '=' after name in attribute.");
			}

			auto value = nextToken();

			if (attribute.values().count(key) == 0) {
				attribute.values().insert({key, value});
			} else {
				throw std::runtime_error(
						"The key '" + key + "' is already defined in the attribute '" + attributeName + "'.");
			}
		}

		container.insert({attributeName, attribute});
	}

	void ByteCodeParser::parseInstruction(Loader::Function& currentFunction) {
		using namespace Loader;
		auto currentToLower = currentTokenToLower();

		if (currentToLower == "@") {
			parseAttribute(currentFunction.attributes);
			return;
		}

		if (currentToLower == "ldint") {
			int value = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(OpCodes::LOAD_INT, value));
			return;
		}

		if (currentToLower == "ldfloat") {
			float value = stof(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithFloat(OpCodes::LOAD_FLOAT, value));
			return;
		}

		if (currentToLower == "ldchar") {
			char value = (char)stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithChar(OpCodes::LOAD_CHAR, value));
			return;
		}

		if (noOperandsInstructions.count(currentToLower) > 0) {
			currentFunction.instructions.push_back(Instruction::make(noOperandsInstructions.at(currentToLower)));
			return;
		}

		if (stringOperandInstructions.count(currentToLower) > 0) {
			std::string value = nextToken();
			currentFunction.instructions.push_back(Instruction::makeWithString(stringOperandInstructions.at(currentToLower), value));
			return;
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

				return;
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

				return;
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
				return;
			} else {
				throw std::runtime_error("The local index is out of range.");
			}
		}

		if (currentToLower == "call" || currentToLower == "callinst" || currentToLower == "callvirt") {
			bool isInstance = currentToLower == "callinst" || currentToLower == "callvirt";
			bool isVirtual = currentToLower == "callvirt";

			auto funcName = nextToken();
			std::string classType = "";

			if (isInstance) {
				auto classNamePosition = funcName.find("::");
				if (classNamePosition != std::string::npos) {
					classType = funcName.substr(0, classNamePosition);
				} else {
					throw std::runtime_error("Expected '::' in called member function.");
				}

				funcName = funcName.substr(classNamePosition + 2);
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

			return;
		}

		if (currentToLower == "ldarg") {
			int argumentNum = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(OpCodes::LOAD_ARG, argumentNum));
			return;
		}

		if (currentToLower == "newobj") {
			auto funcName = nextToken();
			std::string classType = "";

			auto classNamePosition = funcName.find("::");
			if (classNamePosition != std::string::npos) {
				classType = funcName.substr(0, classNamePosition);
			} else {
				throw std::runtime_error("Expected '::' after the type in a new object instruction.");
			}

			funcName = funcName.substr(classNamePosition + 2);

			if (funcName != ".constructor") {
				throw std::runtime_error("Expected call to constructor.");
			}

			if (nextToken() != "(") {
				throw std::runtime_error("Expected '(' after called function.");
			}

			std::vector<std::string> parameters;
			readCallParameters(parameters);
			currentFunction.instructions.push_back(Instruction::makeNewObject(classType, parameters));
			return;
		}

		if (currentToLower == "br") {
			int target = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(OpCodes::BRANCH, target));
			return;
		}

		if (branchInstructions.count(currentToLower) > 0) {
			int target = stoi(nextToken());
			currentFunction.instructions.push_back(Instruction::makeWithInt(branchInstructions.at(currentToLower), target));
			return;
		}

		if (currentToLower == "ldstr") {
			currentFunction.instructions.push_back(Instruction::makeWithStringConstant(OpCodes::LOAD_STRING, nextToken()));
			return;
		}

		throw std::runtime_error("'" + currentToken() + "' is not a valid instruction.");
	}

	void ByteCodeParser::parseFunctionBody(Loader::Assembly& assembly, Loader::Function& currentFunction) {
		nextToken();
		if (currentToken() != "{") {
			throw std::runtime_error("Expected '{' after function definition.");
		}
		nextToken();

		mLocalsSet = false;
		while (true) {
			if (currentToken() == "}") {
				assembly.functions().push_back(currentFunction);
				nextTokenAtEnd();
				break;
			} else {
				parseInstruction(currentFunction);
			}

			nextToken();
		}
	}

	void ByteCodeParser::parseClassBody(Loader::Assembly& assembly, Loader::Class& currentClass) {
		using namespace Loader;

		nextToken();
		if (currentToken() != "{") {
			throw std::runtime_error("Expected '{' after function definition.");
		}
		nextToken();

		Field* currentField = nullptr;
		while (true) {
			if (currentToken() == "}") {
				assembly.classes().push_back(currentClass);
				nextTokenAtEnd();
				break;
			} else {
				auto current = currentToken();

				if (current == "@") {
					if (currentField == nullptr) {
						parseAttribute(currentClass.attributes()); //Class attribute
					} else {
						parseAttribute(currentField->attributes()); //Field attribute
					}

					nextToken();
					continue;
				}

				//Parse field
				auto fieldName = current;
				auto fieldType = nextToken();
				Loader::Field field(fieldName, fieldType);

				currentClass.fields().push_back(field);
				currentField = &currentClass.fields().back();
			}

			nextToken();
		}
	}

	void ByteCodeParser::parse(Loader::Assembly& assembly) {
		using namespace Loader;

		mTokenIndex = 0;
		while (mTokenIndex < mTokens.size()) {
			auto topLevelCurrent = currentToken();

			if (topLevelCurrent == "func") {
				Function currentFunction;
				parseFunctionDefinition(currentFunction);

				if (currentFunction.name.find("::") != std::string::npos) {
					throw std::runtime_error("'::' is only allowed in member functions.");
				}

				parseFunctionBody(assembly, currentFunction);
			} else if (topLevelCurrent == "class") {
				Class currentClass(nextToken());

				if (peekNextToken() == "extends") {
					nextToken();
					currentClass.parentClassName() = nextToken();
				}

				parseClassBody(assembly, currentClass);
			} else if (topLevelCurrent == "extern") {
				Function currentFunction;
				parseFunctionDefinition(currentFunction);
				currentFunction.isExternal = true;
				assembly.functions().push_back(currentFunction);
				nextTokenAtEnd();
			} else if (topLevelCurrent == "member") {
				Function currentFunction;
				parseFunctionDefinition(currentFunction);

				auto funcName = currentFunction.name;

				//Get the class name
				auto classNamePosition = funcName.find("::");
				if (classNamePosition == std::string::npos) {
					throw std::runtime_error("Expected '::' in member function name.");
				}

				auto classTypeName = funcName.substr(0, classNamePosition);
				auto memberFunctionName = funcName.substr(classNamePosition + 2);

				currentFunction.className = classTypeName;
				currentFunction.memberFunctionName = memberFunctionName;
				currentFunction.isMemberFunction = true;

				parseFunctionBody(assembly, currentFunction);
			} else {
				throw std::runtime_error("Invalid identifier '" + topLevelCurrent + "'");
			}
		}
	}

	void Loader::load(std::istream& stream, Loader::Assembly& assembly) {
		ByteCodeParser byteCodeParser(stream);
		byteCodeParser.parse(assembly);
	}
}