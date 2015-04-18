#include "parser.h"
#include "instructions.h"

#include <cctype>
#include <string>
#include <iostream>
#include <unordered_map>

Parser::Instruction::Instruction() {

}

Parser::Instruction Parser::Instruction::make(OpCodes opCode) {
	Parser::Instruction inst;
	inst.opCode = opCode;
	return inst;
}

Parser::Instruction Parser::Instruction::makeWithInt(OpCodes opCode, int value) {
	Parser::Instruction inst;
	inst.intValue = value;
	inst.opCode = opCode;
	return inst;
}

Parser::Instruction Parser::Instruction::makeWithFloat(OpCodes opCode, float value) {
	Parser::Instruction inst;
	inst.floatValue = value;
	inst.opCode = opCode;
	return inst;
}

Parser::Instruction Parser::Instruction::makeWithChar(OpCodes opCode, char value) {
	Parser::Instruction inst;
	inst.charValue = value;
	inst.opCode = opCode;
	return inst;
}

Parser::Instruction Parser::Instruction::makeWithStr(OpCodes opCode, std::string value) {
	Parser::Instruction inst;
	inst.strValue = value;
	inst.opCode = opCode;
	return inst;
}

Parser::Instruction Parser::Instruction::makeCall(std::string funcName, std::vector<std::string> parameters) {
	Parser::Instruction inst;
	inst.strValue = funcName;
	inst.parameters = parameters;
	inst.opCode = OpCodes::CALL;
	return inst;
}

Parser::Instruction Parser::Instruction::makeCallInstance(std::string structType, std::string funcName, std::vector<std::string> parameters) {
	Parser::Instruction inst;
	inst.calledStructType = structType;
	inst.strValue = funcName;
	inst.parameters = parameters;
	inst.opCode = OpCodes::CALL_INSTANCE;
	return inst;
}

Parser::Instruction Parser::Instruction::makeNewObject(std::string structType, std::vector<std::string> parameters) {
	Parser::Instruction inst;
	inst.calledStructType = structType;
	inst.strValue = ".constructor";
	inst.parameters = parameters;
	inst.opCode = OpCodes::NEW_OBJECT;
	return inst;
}

Parser::Function::Function()
	: isMemberFunction(false), isExternal(false) {

}

void Parser::Function::setNumLocals(int num) {
	localTypes.resize(num);
}

std::size_t Parser::Function::numLocals() const {
	return localTypes.size();
}

namespace {
	std::string toLower(std::string str) {
		std::string newStr { "" };
		int length = str.length();

		for (int i = 0; i < length; i++) {
			newStr += std::tolower(str[i]);
		}

		return newStr;
	}

	void assertTokenCount(const std::vector<std::string>& tokens, int index, int count) {
		int left = tokens.size() - (index + 1);

		if (left < count) {
			throw std::runtime_error("Expected '" + std::to_string(count) + "' tokens.");
		}
	}

	std::unordered_map<std::string, OpCodes> noOperandsInstructions
	{
		{ "nop", OpCodes::NOP },
		{ "pop", OpCodes::POP },
		{ "add", OpCodes::ADD },
		{ "sub", OpCodes::SUB },
		{ "mul", OpCodes::MUL },
		{ "div", OpCodes::DIV },
		{ "pushtrue", OpCodes::PUSH_TRUE },
		{ "pushfalse", OpCodes::PUSH_FALSE },
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
		{ "pushnull", OpCodes::PUSH_NULL },
		{ "ldlen", OpCodes::LOAD_ARRAY_LENGTH },
		{ "ret", OpCodes::RET },
		{ "gc", OpCodes::GARBAGE_COLLECT },
	};

	std::unordered_map<std::string, OpCodes> branchInstructions
	{
		{ "beq", OpCodes::BRANCH_EQUAL },
		{ "bne", OpCodes::BRANCH_NOT_EQUAL },
		{ "bgt", OpCodes::BRANCH_GREATER_THAN },
		{ "bge", OpCodes::BRANCH_GREATER_THAN_OR_EQUAL },
		{ "blt", OpCodes::BRANCH_LESS_THAN },
		{ "ble", OpCodes::BRANCH_LESS_THAN_OR_EQUAL }
	};

	std::unordered_map<std::string, OpCodes> strOperandInstructions
	{
		{ "newarr", OpCodes::NEW_ARRAY },
		{ "stelem", OpCodes::STORE_ELEMENT },
		{ "ldelem", OpCodes::LOAD_ELEMENT },
		{ "stfield", OpCodes::STORE_FIELD },
		{ "ldfield", OpCodes::LOAD_FIELD }
	};

	std::string nextToken(const std::vector<std::string>& tokens, std::size_t& index) {
		int left = tokens.size() - (index + 1);

		if (left > 0) {
			return tokens[++index];
		} else {
			throw std::runtime_error("Reached end of tokens.");
		}
	}

	void parseFunctionDef(const std::vector<std::string>& tokens, std::size_t& tokenIndex, Parser::Function* func) {
		func->name = nextToken(tokens, tokenIndex);

		if (nextToken(tokens, tokenIndex) != "(") {
			throw std::runtime_error("Expected '(' after function name.");
		} 

		while (true) {
			std::string param = nextToken(tokens, tokenIndex);

			if (param == ")") {
				break;
			}

			func->parameters.push_back(param);
		}

		func->returnType = nextToken(tokens, tokenIndex);
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
}

std::vector<std::string> Parser::tokenize(std::istream& stream) {
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

void Parser::parseTokens(const std::vector<std::string>& tokens, Parser::Assembly& assembly) {
	bool isFunc = false;
	bool isFuncBody = false;
	bool localsSet = false;

	Function* currentFunc = nullptr;

	bool isStruct = false;
	bool isStructBody = false;
	
	Struct* currentStruct = nullptr;

	for (std::size_t i = 0; i < tokens.size(); i++) {
		std::string current = tokens[i];
		std::string currentToLower = toLower(current);

		//Bodies
		if (isFuncBody) {
			if (currentToLower == "pushint") {
				int value = stoi(nextToken(tokens, i));
				currentFunc->instructions.push_back(Instruction::makeWithInt(OpCodes::PUSH_INT, value));
				continue;
			}

			if (currentToLower == "pushfloat") {
				float value = stof(nextToken(tokens, i));
				currentFunc->instructions.push_back(Instruction::makeWithFloat(OpCodes::PUSH_FLOAT, value));
				continue;
			}

			if (currentToLower == "pushchar") {
				char value = (char)stoi(nextToken(tokens, i));
				currentFunc->instructions.push_back(Instruction::makeWithChar(OpCodes::PUSH_CHAR, value));
				continue;
			}

			if (noOperandsInstructions.count(currentToLower) > 0) {
				currentFunc->instructions.push_back(Instruction::make(noOperandsInstructions[currentToLower]));
			}

			if (strOperandInstructions.count(currentToLower) > 0) {
				std::string value = nextToken(tokens, i);
				currentFunc->instructions.push_back(Instruction::makeWithStr(strOperandInstructions[currentToLower], value));
				continue;
			}

			if (currentToLower == ".locals") {
				if (!localsSet) {
					int localsCount = stoi(nextToken(tokens, i));

					if (localsCount >= 0) {
						localsSet = true;
						currentFunc->setNumLocals(localsCount);
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

					if (localIndex >= 0 && localIndex < (int)currentFunc->numLocals()) {
						currentFunc->localTypes.at(localIndex) = localType;
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
				
				if (local >= 0 && local < (int)currentFunc->numLocals()) {
					currentFunc->instructions.push_back(Instruction::makeWithInt(opCode, local));
					continue;
				} else {
                    throw std::runtime_error("The local index is out of range.");
                }
			}

			if (currentToLower == "call" || currentToLower == "callinst") {
				bool isInstance = currentToLower == "callinst";

				std::string funcName = nextToken(tokens, i);
				std::string structType = "";

				if (isInstance) {
					auto structNamePos = funcName.find("::");

					if (structNamePos != std::string::npos) {
						structType = funcName.substr(0, structNamePos);
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
					currentFunc->instructions.push_back(Instruction::makeCallInstance(structType, funcName, parameters));
				} else {
					currentFunc->instructions.push_back(Instruction::makeCall(funcName, parameters));
				}

				continue;
			}

			if (currentToLower == "ldarg") {
				int argNum = stoi(nextToken(tokens, i));

				if (argNum >= 0 && argNum < (int)currentFunc->parameters.size()) {
                	currentFunc->instructions.push_back(Instruction::makeWithInt(OpCodes::LOAD_ARG, argNum));
                } else {
                    throw std::runtime_error("The argument index is out of range.");
                }
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
				currentFunc->instructions.push_back(Instruction::makeNewObject(structType, parameters));

				continue;
			}

			if (currentToLower == "br") {
				int target = stoi(nextToken(tokens, i));
				currentFunc->instructions.push_back(Instruction::makeWithInt(OpCodes::BRANCH, target));
				continue;
			}

			if (branchInstructions.count(currentToLower) > 0) {
				int target = stoi(nextToken(tokens, i));
				currentFunc->instructions.push_back(Instruction::makeWithInt(branchInstructions[currentToLower], target));
				continue;
			}

			if (currentToLower == "ldstr") {
				auto str = nextToken(tokens, i);
				currentFunc->instructions.push_back(Instruction::makeWithStr(OpCodes::LOAD_STRING, str));
			}
		}

		if (isStructBody) {
			if (currentToLower == "}") {
				currentStruct = nullptr;
				isStruct = false;
				isStructBody = false;
				continue;
			}

			Field field;
			field.name = current;
			field.type = nextToken(tokens, i);

			currentStruct->fields.push_back(field);
		}

		//Definitions
		bool isFuncDef = false;
		bool isExternFunc = false;
		bool isMemberDef = false;

		if (!isFunc && !isStruct && !isExternFunc) {
			if (currentToLower == "func") {
				isFuncDef = true;
				isFunc = true;
			} else if (currentToLower == "struct") {
				currentStruct = new Struct;
				currentStruct->name = nextToken(tokens, i);
				isStruct = true;
				assembly.structs.push_back(currentStruct);
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

		if (isStruct && currentToLower == "{") {
			isStructBody = true;
		}

		//Parse the function definition
		if (isFuncDef) {
			currentFunc = new Function;
			parseFunctionDef(tokens, i, currentFunc);            

			if (currentFunc->name.find("::") != std::string::npos) {
				throw std::runtime_error("'::' is only allowed in member functions.");
			}

			int numArgs = currentFunc->parameters.size();

			if (numArgs >= 0 && numArgs <= MAXIMUM_NUMBER_OF_ARGUMENTS) {
				assembly.functions.push_back(currentFunc);
			} else {
				throw std::runtime_error("Maximum " + std::to_string(MAXIMUM_NUMBER_OF_ARGUMENTS) + " arguments are supported.");
			}

			localsSet = false;
		}

		//Parse external function
        if (isExternFunc) {
            auto funcName = nextToken(tokens, i);

            if (nextToken(tokens, i) != "::") {
                throw std::runtime_error("Expected '::' after extern function name.");
            } 

            currentFunc = new Function;
            parseFunctionDef(tokens, i, currentFunc); 
            currentFunc->externalName = currentFunc->name;
            currentFunc->name = funcName;
            currentFunc->isExternal = true;
            
            assembly.functions.push_back(currentFunc);
        }

        //Parse the member function
        if (isMemberDef) {
            currentFunc = new Function;
            parseFunctionDef(tokens, i, currentFunc);            

            auto funcName = currentFunc->name;

            //Get the struct name
            auto structNamePos = funcName.find("::");

            if (structNamePos == std::string::npos) {
                throw std::runtime_error("Expected '::' in member function name.");
            }

            auto structTypeName = funcName.substr(0, structNamePos);
            auto memberFunctionName = funcName.substr(structNamePos + 2);

            //Add the implicit this reference
            currentFunc->parameters.insert(currentFunc->parameters.begin(), "Ref.Struct." + structTypeName);

            int numArgs = currentFunc->parameters.size();

            if (numArgs >= 0 && numArgs <= MAXIMUM_NUMBER_OF_ARGUMENTS) {
            	currentFunc->structName = structTypeName;
            	currentFunc->memberFunctionName = memberFunctionName;
                assembly.functions.push_back(currentFunc);
            } else {
                throw std::runtime_error("Maximum " + std::to_string(MAXIMUM_NUMBER_OF_ARGUMENTS) + " arguments are supported.");
            }

            localsSet = false;
            isFunc = true;
        }

        if (isFuncBody && currentToLower == "}") {
            isFuncBody = false;
            isFunc = false;
            currentFunc = nullptr;
        }
	}
}