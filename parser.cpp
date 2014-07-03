#include <cctype>
#include <string>
#include <iostream>

#include "parser.h"
#include "instructions.h"

std::vector<std::string> tokenizeInput() {
    std::vector<std::string> tokens;
    std::string token;

    char c = ' ';

    while (true) {
        c = getchar();

        if (c == EOF) {
            break;
        }

        if (isspace(c)) {
            tokens.push_back(token);
            token = "";
        } else {
            token += c;
        }
    }

    tokens.push_back(token);

    return tokens;
}

std::string toLower(std::string str) {
    std::string newStr = "";
    int length = str.length();

    for (int i = 0; i < length; ++i) {
        newStr += std::tolower(str[i]);
    }

    return newStr;
}

void parseTokens(const std::vector<std::string>& tokens, Program& program) {
    bool isFunc = false;
    std::string funcName = "";
    std::vector<Instruction>* mainInstructions = new std::vector<Instruction>();
    std::vector<Instruction>* instructions = mainInstructions;

    for (int i = 0; i < tokens.size(); i++) {
        std::string current = tokens[i];
        std::string currentToLower = toLower(current);

        if (currentToLower == "push") {
            int value = stoi(tokens[i + 1]);
            instructions->push_back(makePushInt(value));
        }

        if (currentToLower == "add") {
            instructions->push_back(makeInstruction(OpCodes::ADD));
        }

        if (currentToLower == "sub") {
            instructions->push_back(makeInstruction(OpCodes::SUB));
        }

        if (currentToLower == "mul") {
            instructions->push_back(makeInstruction(OpCodes::MUL));
        }

        if (currentToLower == "ldloc") {
            int local = stoi(tokens[i + 1]);
            instructions->push_back(makeLoadLocal(local));
        }

        if (currentToLower == "stloc") {
            int local = stoi(tokens[i + 1]);
            instructions->push_back(makeStoreLocal(local));
        }

        if (currentToLower == "call") {
            std::string funcName = tokens[i + 1];
            int numArgs = stoi(tokens[i + 2]);

            instructions->push_back(makeCall(funcName, numArgs));
            // if (program.CallTable.count(funcName) > 0) {
            //     instructions->push_back(makeCall(funcName, numArgs));
            // } else {
            //     throw std::string("Function '" + funcName + "' not found.");
            // }
        }

        if (!isFunc) {
            if (currentToLower == "func") {
                isFunc = true;
                funcName = tokens[i + 1];
                instructions = new std::vector<Instruction>();
            }
        } else {
            if (currentToLower == "endfunc") {
                isFunc = false;
                program.Functions[funcName] = instructions;
                instructions = mainInstructions;
                //std::cout << "Defined function: " << funcName << std::endl;
            }
        }
    }

    program.Functions["main"] = mainInstructions;
}