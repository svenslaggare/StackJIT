#include "parser.h"
#include "../core/instruction.h"
#include "../core/functionsignature.h"
#include <cctype>
#include <string>
#include <iostream>
#include <unordered_map>

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

AssemblyParser::Instruction AssemblyParser::Instruction::makeWithStr(OpCodes opCode, std::string value) {
	AssemblyParser::Instruction inst;
	inst.strValue = value;
	inst.opCode = opCode;
	inst.format = InstructionFormats::StrData;
	return inst;
}

AssemblyParser::Instruction AssemblyParser::Instruction::makeCall(std::string funcName, std::vector<std::string> parameters) {
	AssemblyParser::Instruction inst;
	inst.strValue = funcName;
	inst.parameters = parameters;
	inst.opCode = OpCodes::CALL;
	inst.format = InstructionFormats::Call;
	return inst;
}

AssemblyParser::Instruction AssemblyParser::Instruction::makeCallInstance(std::string classType, std::string funcName, std::vector<std::string> parameters) {
	AssemblyParser::Instruction inst;
	inst.calledClassType = classType;
	inst.strValue = funcName;
	inst.parameters = parameters;
	inst.opCode = OpCodes::CALL_INSTANCE;
	inst.format = InstructionFormats::CallInstance;
	return inst;
}

AssemblyParser::Instruction AssemblyParser::Instruction::makeCallVirtual(std::string classType, std::string funcName, std::vector<std::string> parameters) {
	AssemblyParser::Instruction inst;
	inst.calledClassType = classType;
	inst.strValue = funcName;
	inst.parameters = parameters;
	inst.opCode = OpCodes::CALL_VIRTUAL;
	inst.format = InstructionFormats::CallInstance;
	return inst;
}

AssemblyParser::Instruction AssemblyParser::Instruction::makeNewObject(std::string classType, std::vector<std::string> parameters) {
	AssemblyParser::Instruction inst;
	inst.calledClassType = classType;
	inst.strValue = ".constructor";
	inst.parameters = parameters;
	inst.opCode = OpCodes::NEW_OBJECT;
	inst.format = InstructionFormats::CallInstance;
	return inst;
}

AssemblyParser::Function::Function()
	: isMemberFunction(false), isExternal(false) {

}

void AssemblyParser::Function::setNumLocals(int num) {
	localTypes.resize(num);
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

	std::unordered_map<std::string, OpCodes> noOperandsInstructions	{
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

	std::unordered_map<std::string, OpCodes> branchInstructions	{
		{ "beq", OpCodes::BRANCH_EQUAL },
		{ "bne", OpCodes::BRANCH_NOT_EQUAL },
		{ "bgt", OpCodes::BRANCH_GREATER_THAN },
		{ "bge", OpCodes::BRANCH_GREATER_THAN_OR_EQUAL },
		{ "blt", OpCodes::BRANCH_LESS_THAN },
		{ "ble", OpCodes::BRANCH_LESS_THAN_OR_EQUAL }
	};

	std::unordered_map<std::string, OpCodes> strOperandInstructions	{
		{ "newarr", OpCodes::NEW_ARRAY },
		{ "stelem", OpCodes::STORE_ELEMENT },
		{ "ldelem", OpCodes::LOAD_ELEMENT },
		{ "stfield", OpCodes::STORE_FIELD },
		{ "ldfield", OpCodes::LOAD_FIELD }
	};

	std::string nextToken(const std::vector<std::string>& tokens, std::size_t& index) {
		if (tokens.size() >= (index + 1)) {
			return tokens[++index];
		} else {
			throw std::runtime_error("Reached end of tokens.");
		}
	}

	std::string peekNextToken(const std::vector<std::string>& tokens, std::size_t index) {
		if (tokens.size() >= (index + 1)) {
			return tokens[index + 1];
		} else {
			throw std::runtime_error("Reached end of tokens.");
		}
	}

	void parseFunctionDef(const std::vector<std::string>& tokens, std::size_t& tokenIndex, AssemblyParser::Function& func) {
		func.name = nextToken(tokens, tokenIndex);

		if (nextToken(tokens, tokenIndex) != "(") {
			throw std::runtime_error("Expected '(' after function name.");
		} 

		while (true) {
			std::string param = nextToken(tokens, tokenIndex);

			if (param == ")") {
				break;
			}

			func.parameters.push_back(param);
		}

		func.returnType = nextToken(tokens, tokenIndex);
	}

	void readCallParameters(const std::vector<std::string>& tokens, std::size_t& tokenIndex, std::vector<std::string>& parameters) {
		while (true) {
			auto param = nextToken(tokens, tokenIndex);

			if (param == ")") {
				break;
			}

			parameters.push_back(param);
		}
	}

	void parseAttribute(const std::vector<std::string>& tokens, std::size_t& tokenIndex, AssemblyParser::AttributeContainer& container) {
		auto attributeName = nextToken(tokens, tokenIndex);

		if (nextToken(tokens, tokenIndex) != "(") {
			throw std::runtime_error("Expected '(' after attribute name");
		}

		if (container.count(attributeName) > 0) {
			throw std::runtime_error("The attribute '" + attributeName + "' is already defined.'");
		}

		AssemblyParser::Attribute attribute;
		attribute.name = attributeName;

		while (true) {
			auto key = nextToken(tokens, tokenIndex);

			if (key == ")") {
				break;
			}

			if (nextToken(tokens, tokenIndex) != "=") {
				throw std::runtime_error("Expected '=' after name in attribute.");
			}

			auto value = nextToken(tokens, tokenIndex);

			if (attribute.values.count(key) == 0) {
				attribute.values.insert({ key, value });
			} else {
				throw std::runtime_error(
					"The key '" + key + "' is already defined in the attribute '" + attributeName + "'.");
			}
		}

		container.insert({ attributeName, attribute });
	}
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

void AssemblyParser::parseTokens(const std::vector<std::string>& tokens, AssemblyParser::Assembly& assembly) {
	bool isFunc = false;
	bool isFuncBody = false;
	bool localsSet = false;

	Function currentFunc;

	bool isClass = false;
	bool isClassBody = false;
	
	Class currentClass;
	Field* currentField = nullptr;

	for (std::size_t i = 0; i < tokens.size(); i++) {
		std::string current = tokens[i];
		std::string currentToLower = toLower(current);

		//Bodies
		if (isFuncBody) {
			if (currentToLower == "}") {
				isFuncBody = false;
				isFunc = false;
				assembly.functions.push_back(currentFunc);
				continue;
			}

			if (currentToLower == "@") {
				parseAttribute(tokens, i, currentFunc.attributes);
				continue;
			}

			if (currentToLower == "ldint") {
				int value = stoi(nextToken(tokens, i));
				currentFunc.instructions.push_back(Instruction::makeWithInt(OpCodes::LOAD_INT, value));
				continue;
			}

			if (currentToLower == "ldfloat") {
				float value = stof(nextToken(tokens, i));
				currentFunc.instructions.push_back(Instruction::makeWithFloat(OpCodes::LOAD_FLOAT, value));
				continue;
			}

			if (currentToLower == "ldchar") {
				char value = (char)stoi(nextToken(tokens, i));
				currentFunc.instructions.push_back(Instruction::makeWithChar(OpCodes::LOAD_CHAR, value));
				continue;
			}

			if (noOperandsInstructions.count(currentToLower) > 0) {
				currentFunc.instructions.push_back(Instruction::make(noOperandsInstructions[currentToLower]));
				continue;
			}

			if (strOperandInstructions.count(currentToLower) > 0) {
				std::string value = nextToken(tokens, i);
				currentFunc.instructions.push_back(Instruction::makeWithStr(strOperandInstructions[currentToLower], value));
				continue;
			}

			if (currentToLower == ".locals") {
				if (!localsSet) {
					int localsCount = stoi(nextToken(tokens, i));

					if (localsCount >= 0) {
						localsSet = true;
						currentFunc.setNumLocals(localsCount);
					} else {
						throw std::runtime_error("The number of locals must be >= 0.");
					}
					continue;
				} else {
					throw std::runtime_error("The locals has already been set.");
				}
			}

			if (currentToLower == ".local") {
				if (localsSet) {
					int localIndex = stoi(nextToken(tokens, i));
					auto localType = nextToken(tokens, i);

					if (localIndex >= 0 && localIndex < (int)currentFunc.numLocals()) {
						currentFunc.localTypes.at(localIndex) = localType;
					} else {
                    	throw std::runtime_error("Invalid local index.");
                    }
					continue;
				} else {
					throw std::runtime_error("The locals must been set.");
				}
			}

			if (currentToLower == "ldloc" || currentToLower == "stloc") {
				if (!localsSet) {
					throw std::runtime_error("The locals must be set.");
				}

				int local = stoi(nextToken(tokens, i));
				auto opCode = currentToLower == "ldloc" ? OpCodes::LOAD_LOCAL : OpCodes::STORE_LOCAL;
				
				if (local >= 0 && local < (int)currentFunc.numLocals()) {
					currentFunc.instructions.push_back(Instruction::makeWithInt(opCode, local));
					continue;
				} else {
                    throw std::runtime_error("The local index is out of range.");
                }
			}

			if (currentToLower == "call" || currentToLower == "callinst" || currentToLower == "callvirt") {
				bool isInstance = currentToLower == "callinst" || currentToLower == "callvirt";
				bool isVirtual = currentToLower == "callvirt";

				std::string funcName = nextToken(tokens, i);
				std::string classType = "";

				if (isInstance) {
					auto structNamePos = funcName.find("::");

					if (structNamePos != std::string::npos) {
						classType = funcName.substr(0, structNamePos);
					} else {
						throw std::runtime_error("Expected '::' in called member function.");
					}

					funcName = funcName.substr(structNamePos + 2);
				}

				if (nextToken(tokens, i) != "(") {
					throw std::runtime_error("Expected '(' after called function.");
				}

				std::vector<std::string> parameters;
				readCallParameters(tokens, i, parameters);

				if (isInstance) {
					if (!isVirtual) {
						currentFunc.instructions.push_back(Instruction::makeCallInstance(classType, funcName, parameters));
					} else {
						currentFunc.instructions.push_back(Instruction::makeCallVirtual(classType, funcName, parameters));
					}
				} else {
					currentFunc.instructions.push_back(Instruction::makeCall(funcName, parameters));
				}
				continue;
			}

			if (currentToLower == "ldarg") {
				int argNum = stoi(nextToken(tokens, i));
				currentFunc.instructions.push_back(Instruction::makeWithInt(OpCodes::LOAD_ARG, argNum));
				continue;
			}

			if (currentToLower == "newobj") {
				std::string funcName = nextToken(tokens, i);
				std::string structType = "";

				auto structNamePos = funcName.find("::");

				if (structNamePos != std::string::npos) {
					structType = funcName.substr(0, structNamePos);
				} else {
					throw std::runtime_error("Expected '::' after the type in a new object instruction.");
				}

				funcName = funcName.substr(structNamePos + 2);

				if (funcName != ".constructor") {
					throw std::runtime_error("Expected call to constructor.");
				}

				if (nextToken(tokens, i) != "(") {
					throw std::runtime_error("Expected '(' after called function.");
				}

				std::vector<std::string> parameters;
				readCallParameters(tokens, i, parameters);
				currentFunc.instructions.push_back(Instruction::makeNewObject(structType, parameters));
				continue;
			}

			if (currentToLower == "br") {
				int target = stoi(nextToken(tokens, i));
				currentFunc.instructions.push_back(Instruction::makeWithInt(OpCodes::BRANCH, target));
				continue;
			}

			if (branchInstructions.count(currentToLower) > 0) {
				int target = stoi(nextToken(tokens, i));
				currentFunc.instructions.push_back(Instruction::makeWithInt(branchInstructions[currentToLower], target));
				continue;
			}

			if (currentToLower == "ldstr") {
				auto str = nextToken(tokens, i);
				currentFunc.instructions.push_back(Instruction::makeWithStr(OpCodes::LOAD_STRING, str));
				continue;
			}

			throw std::runtime_error("'" + current + "' is not a valid instruction.");
		}

		if (isClassBody) {
			if (currentToLower == "@") {
				if (currentField == nullptr) {
					//Class attribute
					parseAttribute(tokens, i, currentClass.attributes);
				} else {
					//Field attribute
					parseAttribute(tokens, i, currentField->attributes);
				}
				continue;
			}

			if (currentToLower == "}") {
				assembly.classes.push_back(currentClass);
				isClass = false;
				isClassBody = false;
				currentField = nullptr;
				continue;
			}

			Field field;
			field.name = current;
			field.type = nextToken(tokens, i);

			currentClass.fields.push_back(field);
			currentField = &currentClass.fields.back();
		}

		//Definitions
		bool isFuncDef = false;
		bool isExternFunc = false;
		bool isMemberDef = false;

		if (!isFunc && !isClass && !isExternFunc) {
			if (currentToLower == "func") {
				isFuncDef = true;
				isFunc = true;
			} else if (currentToLower == "class") {
				currentClass = {};
				currentClass.name = nextToken(tokens, i);

				if (peekNextToken(tokens, i) == "extends") {
					nextToken(tokens, i);
					currentClass.parentClassName = nextToken(tokens, i);
				}

				isClass = true;
			} else if (currentToLower == "extern") {
				isExternFunc = true;
			} else if (currentToLower == "member") {
				isMemberDef = true;
			} else {
				throw std::runtime_error("Invalid identifier '" + current + "'");
			}
		}

		if (isFunc && !isFuncDef && currentToLower == "{") {
			isFuncBody = true;
		}

		if (isClass && currentToLower == "{") {
			isClassBody = true;
		}

		//Parse the function definition
		if (isFuncDef) {
			currentFunc = {};
			parseFunctionDef(tokens, i, currentFunc);            

			if (currentFunc.name.find("::") != std::string::npos) {
				throw std::runtime_error("'::' is only allowed in member functions.");
			}

			localsSet = false;
		}

		//Parse external function
        if (isExternFunc) {
            currentFunc = {};
            parseFunctionDef(tokens, i, currentFunc);
            currentFunc.isExternal = true;
            
            assembly.functions.push_back(currentFunc);
        }

        //Parse the member function
        if (isMemberDef) {
            currentFunc = {};
            parseFunctionDef(tokens, i, currentFunc);            

            auto funcName = currentFunc.name;

            //Get the struct name
            auto classNamePos = funcName.find("::");

            if (classNamePos == std::string::npos) {
                throw std::runtime_error("Expected '::' in member function name.");
            }

            auto classTypeName = funcName.substr(0, classNamePos);
            auto memberFunctionName = funcName.substr(classNamePos + 2);

			currentFunc.className = classTypeName;
			currentFunc.memberFunctionName = memberFunctionName;
			currentFunc.isMemberFunction = true;

            localsSet = false;
            isFunc = true;
        }
	}
}