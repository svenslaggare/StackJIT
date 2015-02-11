#include <cctype>
#include <string>
#include <iostream>
#include <unordered_map>

#include "parser.h"
#include "instructions.h"
#include "codegenerator.h"
#include "assembly.h"
#include "function.h"
#include "typechecker.h"
#include "type.h"
#include "vmstate.h"

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
                tokens.push_back(std::string{ c });
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
    { "newobj", OpCodes::NEW_OBJECT },
    { "stfield", OpCodes::STORE_FIELD },
    { "ldfield", OpCodes::LOAD_FIELD }
};

std::string nextToken(const std::vector<std::string>& tokens, int& index) {
    int left = tokens.size() - (index + 1);

    if (left > 0) {
        return tokens[++index];
    } else {
        throw std::runtime_error("Reached end of tokens.");
    }
}

void parseFunctionDef(const std::vector<std::string>& tokens, int& tokenIndex, VMState& vmState, std::string& name, std::vector<const Type*>& parameters, const Type*& returnType) {
    name = nextToken(tokens, tokenIndex);

    if (nextToken(tokens, tokenIndex) != "(") {
        throw std::runtime_error("Expected '(' after function name.");
    } 

    while (true) {
        std::string param = nextToken(tokens, tokenIndex);

        if (param == ")") {
            break;
        }

        auto paramType = vmState.findType(param);

        if (paramType == nullptr) {
            throw std::runtime_error("'" + param + "' is not a type.");
        }

        parameters.push_back(paramType);
    }

    auto returnTypeName = nextToken(tokens, tokenIndex);
    returnType = vmState.findType(returnTypeName);

    if (returnType == nullptr) {
        throw std::runtime_error("'" + returnTypeName + "' is not a type.");
    }
}

void Parser::parseTokens(const std::vector<std::string>& tokens, VMState& vmState, Assembly& assembly) {
    bool isFunc = false;
    bool isFuncBody = false;
    bool isFuncDef = false;
    bool localsSet = false;

    Function* currentFunc = nullptr;

    bool isStruct = false;
    bool isStructBody = false;
    std::string structName;
    std::map<std::string, const Type*> structFields;

    bool isExternFunc = false;

    for (int i = 0; i < tokens.size(); i++) {
        std::string current = tokens[i];
        std::string currentToLower = toLower(current);

        if (isFuncBody) {
            if (currentToLower == "pushint") {
                int value = stoi(nextToken(tokens, i));
                currentFunc->instructions.push_back(Instructions::makeWithInt(OpCodes::PUSH_INT, value));
                continue;
            }

            if (currentToLower == "pushfloat") {
                float value = stof(nextToken(tokens, i));
                currentFunc->instructions.push_back(Instructions::makeWithFloat(OpCodes::PUSH_FLOAT, value));
                continue;
            }

            if (currentToLower == "pushchar") {
                char value = (char)stoi(nextToken(tokens, i));
                currentFunc->instructions.push_back(Instructions::makeWithChar(OpCodes::PUSH_CHAR, value));
                continue;
            }

            if (noOperandsInstructions.count(currentToLower) > 0) {
                currentFunc->instructions.push_back(Instructions::make(noOperandsInstructions[currentToLower]));
            }

            if (strOperandInstructions.count(currentToLower) > 0) {
                std::string value = nextToken(tokens, i);
                currentFunc->instructions.push_back(Instructions::makeWithStr(strOperandInstructions[currentToLower], value));
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
                    auto localType = vmState.findType(nextToken(tokens, i));

                    if (localType == nullptr) {
                        throw std::runtime_error("'" + tokens[i] + "' is not a type");
                    }

                    if (localIndex >= 0 && localIndex < currentFunc->numLocals()) {
                        currentFunc->setLocal(localIndex, localType);
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

                if (local >= 0 && local < currentFunc->numLocals()) {
                    currentFunc->instructions.push_back(Instructions::makeWithInt(opCode, local));
                } else {
                    throw std::runtime_error("The local index is out of range.");
                }

                continue;
            }

            if (currentToLower == "call") {
                std::string funcName = nextToken(tokens, i);

                if (nextToken(tokens, i) != "(") {
                    throw std::runtime_error("Expected '(' after called function.");
                }

                std::vector<const Type*> parameters;

                while (true) {
                    auto param = nextToken(tokens, i);

                    if (param == ")") {
                        break;
                    }

                    auto paramType = vmState.findType(param);

                    if (paramType == nullptr) {
                        throw std::runtime_error("'" + param + "' is not a valid type.");
                    }

                    parameters.push_back(paramType);
                }

                currentFunc->instructions.push_back(Instructions::makeCall(funcName, parameters));
                continue;
            }

            if (currentToLower == "ldarg") {
                int argNum = stoi(nextToken(tokens, i));

                if (argNum >= 0 && argNum < currentFunc->numArgs()) {
                    currentFunc->instructions.push_back(Instructions::makeWithInt(OpCodes::LOAD_ARG, argNum));
                } else {
                    throw std::runtime_error("The argument index is out of range.");
                }

                continue;
            }

            if (currentToLower == "br") {
                int target = stoi(nextToken(tokens, i));
                currentFunc->instructions.push_back(Instructions::makeWithInt(OpCodes::BRANCH, target));
                continue;
            }

            if (branchInstructions.count(currentToLower) > 0) {
                int target = stoi(nextToken(tokens, i));
                currentFunc->instructions.push_back(Instructions::makeWithInt(branchInstructions[currentToLower], target));
                continue;
            }

            if (currentToLower == "ldstr") {
                auto str = nextToken(tokens, i);
                currentFunc->instructions.push_back(Instructions::makeWithStr(OpCodes::LOAD_STRING, str));
            }
        }

        if (isStructBody) {
            if (currentToLower == "}") {
                vmState.structProvider().add(structName, StructMetadata(structFields));
                structFields.clear();

                isStruct = false;
                isStructBody = false;
                continue;
            }

            auto fieldName = current;
            auto fieldType = vmState.findType(nextToken(tokens, i));

            if (fieldType == nullptr) {
                throw std::runtime_error("'" + tokens[i] + "' is not a valid type.");
            }

            structFields.insert({ fieldName, fieldType });
        }

        if (!isFunc && !isStruct && !isExternFunc) {
            if (currentToLower == "func") {
                isFuncDef = true;
                isFunc = true;
            } else if (currentToLower == "struct") {
                structName = nextToken(tokens, i);
                isStruct = true;
            } else if (currentToLower == "extern") {
                isExternFunc = true;
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
            std::string funcName;
            std::vector<const Type*> parameters;
            const Type* returnType = nullptr;
            parseFunctionDef(tokens, i, vmState, funcName, parameters, returnType);            

            int numArgs = parameters.size();
            auto signature = vmState.binder().functionSignature(funcName, parameters);

            if (numArgs >= 0 && numArgs <= 6) {
                if (assembly.functions.count(signature) == 0 && !vmState.binder().isDefined(signature)) {
                    //Create a new function        
                    Function* newFunc = new Function(funcName, parameters, returnType);
                    assembly.functions[signature] = newFunc;
                    currentFunc = newFunc;
                } else {
                    throw std::runtime_error("The function '" + signature + "' is already defined.");
                }
            } else {
                throw std::runtime_error("Maximum six arguments are supported.");
            }

            isFuncDef = false;
            localsSet = false;
        }

        //Parse external function
        if (isExternFunc) {
            auto funcName = nextToken(tokens, i);

            if (nextToken(tokens, i) != "::") {
                throw std::runtime_error("Expected '::' after extern function name.");
            } 

            std::string externFuncName;
            std::vector<const Type*> parameters;
            const Type* returnType = nullptr;
            parseFunctionDef(tokens, i, vmState, externFuncName, parameters, returnType); 

            auto signature = vmState.binder().functionSignature(funcName, parameters);

            if (assembly.functions.count(signature) == 0 && !vmState.binder().isDefined(signature)) {
                auto externSignature = vmState.binder().functionSignature(externFuncName, parameters);

                if (vmState.binder().isDefined(externSignature)) {
                    if (!vmState.binder().defineExternal(signature, externSignature)) {
                        throw std::runtime_error("'" + externSignature + "' is not an external function.");
                    }
                } else {
                    throw std::runtime_error("The external function '" + externSignature + "' is not defined.");
                }
            } else {
                throw std::runtime_error("The function '" + signature + "' is already defined.");
            }

            isExternFunc = false;
        }

        if (isFuncBody && currentToLower == "}") {
            isFuncBody = false;
            isFunc = false;
            currentFunc = nullptr;
        }
    }
}