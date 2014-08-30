#include <cctype>
#include <string>
#include <iostream>

#include "parser.h"
#include "instructions.h"
#include "codegenerator.h"
#include "program.h"
#include "typechecker.h"

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

        if (c == ':' || c == '(' || c == ')') {
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

void Parser::parseTokens(const std::vector<std::string>& tokens, Program& program) {
    bool isFuncBody = false;
    bool isFuncDef = false;
    std::string funcName;
    bool isFuncParams = false;
    std::vector<Types> funcParams {};

    int numLocals = 4;

    // //Create the main function
    // Function* mainFunc = new Function;
    // mainFunc->Name = "main";
    // mainFunc->NumArgs = 0;
    // mainFunc->ReturnType = Types::Int;
    // mainFunc->NumLocals = 4;
    // program.Functions["main"] = mainFunc;

    Function* currentFunc = nullptr;

    for (int i = 0; i < tokens.size(); i++) {
        std::string current = tokens[i];
        std::string currentToLower = toLower(current);

        if (isFuncBody) {
            if (currentToLower == "push") {
                int value = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makePushInt(value));
            }

            if (currentToLower == "pop") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::POP));
            }

            if (currentToLower == "add") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::ADD));
            }

            if (currentToLower == "sub") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::SUB));
            }

            if (currentToLower == "mul") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::MUL));
            }

            if (currentToLower == "div") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::DIV));
            }

            if (currentToLower == "ldloc") {
                int local = stoi(tokens[i + 1]);

                if (local >= 0 && local < currentFunc->NumLocals) {
                    currentFunc->Instructions.push_back(makeLoadLocal(local));
                } else {
                    throw std::runtime_error("Local out of range.");
                }
            }

            if (currentToLower == "stloc") {
                int local = stoi(tokens[i + 1]);
                
                if (local >= 0 && local < currentFunc->NumLocals) {
                    currentFunc->Instructions.push_back(makeStoreLocal(local));
                } else {
                    throw std::runtime_error("Local out of range.");
                }
            }

            if (currentToLower == "call") {
                std::string funcName = tokens[i + 1];
                currentFunc->Instructions.push_back(makeCall(funcName));
            }

            if (currentToLower == "ret") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::RET));
            }

            if (currentToLower == "ldarg") {
                int argNum = stoi(tokens[i + 1]);

                if (argNum >= 0 && argNum < currentFunc->NumArgs) {
                    currentFunc->Instructions.push_back(makeLoadArg(argNum));
                } else {
                    throw std::runtime_error("Argument out of range.");
                }
            }

            if (currentToLower == "br") {
                int target = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makeBr(target));
            }

            if (currentToLower == "beq") {
                int target = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makeInstWithInt(OpCodes::BEQ, target));
            }

            if (currentToLower == "bne") {
                int target = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makeInstWithInt(OpCodes::BNE, target));
            }

            if (currentToLower == "bgt") {
                int target = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makeInstWithInt(OpCodes::BGT, target));
            }

            if (currentToLower == "bge") {
                int target = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makeInstWithInt(OpCodes::BGE, target));
            }

            if (currentToLower == "blt") {
                int target = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makeInstWithInt(OpCodes::BLT, target));
            }

            if (currentToLower == "ble") {
                int target = stoi(tokens[i + 1]);
                currentFunc->Instructions.push_back(makeInstWithInt(OpCodes::BLE, target));
            }

            if (currentToLower == "newarr") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::NEW_ARRAY));
            }

            if (currentToLower == "stelem") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::STORE_ELEMENT));
            }

            if (currentToLower == "ldelem") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::LOAD_ELEMENT));
            }

            if (currentToLower == "ldlen") {
                currentFunc->Instructions.push_back(makeInstruction(OpCodes::LOAD_ARRAY_LENGTH));
            }
        }

        if (!isFuncBody) {
            if (!isFuncDef) {
                if (currentToLower == "func") {
                    isFuncDef = true;
                    funcName = tokens[i + 1];
                } else if (currentToLower == "{") {
                    isFuncBody = true;
                }
            } else {
                if (isFuncParams) {
                    if (currentToLower == ")") {                        
                        auto returnType = TypeChecker::stringToType(tokens[i + 1]);
                        int numArgs = funcParams.size();

                        if (numArgs >= 0 && numArgs <= 4) {
                            //Create a new function        
                            Function* newFunc = new Function;
                            newFunc->Name = funcName;

                            newFunc->NumArgs = numArgs;
                            newFunc->Arguments = funcParams;
                            newFunc->ReturnType = returnType;

                            newFunc->NumLocals = numLocals;
                            program.Functions[funcName] = newFunc;

                            currentFunc = newFunc;
                        } else {
                            throw std::runtime_error("Maximum four arguments are supported.");
                        }

                        isFuncParams = false;
                        isFuncDef = false;
                        funcParams = {};
                        funcName = "";
                    } else {
                        funcParams.push_back(TypeChecker::stringToType(currentToLower));
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

        if (mainFunc->Arguments.size() != 0 || mainFunc->ReturnType != Types::Int) {
           throw std::runtime_error("The main function must have the following signature: 'func main() Int'"); 
        }
    } else {
        throw std::runtime_error("The main function must be defined.");
    }
}