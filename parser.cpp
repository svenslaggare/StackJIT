#include <cctype>
#include <string>
#include <iostream>
#include <unordered_map>

#include "parser.h"
#include "instructions.h"
#include "codegenerator.h"
#include "program.h"
#include "typechecker.h"
#include "type.h"
#include "vmstate.h"

std::vector<std::string> Parser::tokenize(std::istream& stream) {
    std::vector<std::string> tokens;
    std::string token;

    char c;
    while (stream.get(c)) {
        bool newToken = false;
        bool newIdentifier = false;

        if (isspace(c)) {
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

    tokens.push_back(token);
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
    { "pop", OpCodes::POP },
    { "add", OpCodes::ADD },
    { "sub", OpCodes::SUB },
    { "mul", OpCodes::MUL },
    { "div", OpCodes::DIV },
    { "ldlen", OpCodes::LOAD_ARRAY_LENGTH },
    { "ret", OpCodes::RET }
};

std::unordered_map<std::string, OpCodes> branchInstructions
{
    { "beq", OpCodes::BEQ },
    { "bne", OpCodes::BNE },
    { "bgt", OpCodes::BGT },
    { "bge", OpCodes::BGE },
    { "blt", OpCodes::BLT },
    { "ble", OpCodes::BLE }
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

void Parser::parseTokens(const std::vector<std::string>& tokens, VMState& vmState, Program& program) {
    bool isFuncBody = false;
    bool isFuncDef = false;
    std::string funcName;
    bool isFuncParams = false;
    std::vector<Type*> funcParams {};
    bool localsSet = false;

    Function* currentFunc = nullptr;

    for (int i = 0; i < tokens.size(); i++) {
        std::string current = tokens[i];
        std::string currentToLower = toLower(current);

        if (isFuncBody) {
            if (currentToLower == "push") {
                assertTokenCount(tokens, i, 1);
                int value = stoi(tokens[i + 1]);
                currentFunc->instructions.push_back(makeInstWithInt(OpCodes::PUSH_INT, value));
            }

            if (noOperandsInstructions.count(currentToLower) > 0) {
                currentFunc->instructions.push_back(makeInstruction(noOperandsInstructions[currentToLower]));
            }

            if (strOperandInstructions.count(currentToLower) > 0) {
                assertTokenCount(tokens, i, 1);
                std::string value = tokens[i + 1];
                currentFunc->instructions.push_back(makeInstWithStr(strOperandInstructions[currentToLower], value));
            }

            if (currentToLower == ".locals") {
                if (!localsSet) {
                    assertTokenCount(tokens, i, 1);
                    int localsCount = stoi(tokens[i + 1]);

                    if (localsCount >= 0) {
                        localsSet = true;
                        currentFunc->numLocals = localsCount;
                    } else {
                        throw std::runtime_error("The number of locals must be >= 0.");
                    }
                } else {
                    throw std::runtime_error("The locals has already been set.");
                }
            }

            if (currentToLower == "ldloc" || currentToLower == "stloc") {
                assertTokenCount(tokens, i, 1);

                if (!localsSet) {
                    throw std::runtime_error("The locals must be set.");
                }

                int local = stoi(tokens[i + 1]);
                auto opCode = currentToLower == "ldloc" ? OpCodes::LOAD_LOCAL : OpCodes::STORE_LOCAL;

                if (local >= 0 && local < currentFunc->numLocals) {
                    currentFunc->instructions.push_back(makeInstWithInt(opCode, local));
                } else {
                    throw std::runtime_error("The local index is out of range.");
                }
            }

            if (currentToLower == "call") {
                assertTokenCount(tokens, i, 1);
                std::string funcName = tokens[i + 1];
                currentFunc->instructions.push_back(makeCall(funcName));
            }

            if (currentToLower == "ldarg") {
                assertTokenCount(tokens, i, 1);
                int argNum = stoi(tokens[i + 1]);

                if (argNum >= 0 && argNum < currentFunc->numArgs()) {
                    currentFunc->instructions.push_back(makeInstWithInt(OpCodes::LOAD_ARG, argNum));
                } else {
                    throw std::runtime_error("The argument index is out of range.");
                }
            }

            if (currentToLower == "br") {
                assertTokenCount(tokens, i, 1);
                int target = stoi(tokens[i + 1]);
                currentFunc->instructions.push_back(makeInstWithInt(OpCodes::BR, target));
            }

            if (branchInstructions.count(currentToLower) > 0) {
                assertTokenCount(tokens, i, 1);
                int target = stoi(tokens[i + 1]);
                currentFunc->instructions.push_back(makeInstWithInt(branchInstructions[currentToLower], target));
            }
        }

        if (!isFuncBody) {
            if (!isFuncDef) {
                if (currentToLower == "func") {
                    assertTokenCount(tokens, i, 1);

                    isFuncDef = true;
                    funcName = tokens[i + 1];
                } else if (currentToLower == "{") {
                    isFuncBody = true;
                }
            } else {
                if (isFuncParams) {
                    if (currentToLower == ")") {     
                        assertTokenCount(tokens, i, 1);                   
                        auto returnType = vmState.findType(tokens[i + 1]);
                        int numArgs = funcParams.size();

                        if (numArgs >= 0 && numArgs <= 4) {
                            //Create a new function        
                            Function* newFunc = new Function(funcName, funcParams, returnType);
                            newFunc->numLocals = 0;
                            program.Functions[funcName] = newFunc;

                            currentFunc = newFunc;
                        } else {
                            throw std::runtime_error("Maximum four arguments are supported.");
                        }

                        isFuncParams = false;
                        isFuncDef = false;
                        funcParams = {};
                        funcName = "";
                        localsSet = false;
                    } else {
                        funcParams.push_back(vmState.findType(current));
                    }
                }

                if (currentToLower == "(") {
                    isFuncParams = true;
                }
            }
        } else {
            if (currentToLower == "}") {
                isFuncBody = false;
                currentFunc = nullptr;
            }
        }
    }

    if (program.Functions.count("main") > 0) {
        auto mainFunc = program.Functions["main"];

        if (mainFunc->arguments.size() != 0 || !TypeSystem::isPrimitiveType(mainFunc->returnType, PrimitiveTypes::Integer)) {
           throw std::runtime_error("The main function must have the following signature: 'func main() Int'"); 
        }
    } else {
        throw std::runtime_error("The main function must be defined.");
    }
}