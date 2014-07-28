#include <cctype>
#include <string>
#include <iostream>

#include "parser.h"
#include "instructions.h"

std::vector<std::string> Parser::tokenize(std::istream& stream) {
    std::vector<std::string> tokens;
    std::string token;

    char c;
    while (stream.get(c)) {
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
    std::string newStr { "" };
    int length = str.length();

    for (int i = 0; i < length; i++) {
        newStr += std::tolower(str[i]);
    }

    return newStr;
}

void Parser::parseTokens(const std::vector<std::string>& tokens, Program& program) {
    bool isFunc = false;
    std::string funcName = "";
    int funcArgs = 0;

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

        if (currentToLower == "div") {
            instructions->push_back(makeInstruction(OpCodes::DIV));
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
        }

        if (currentToLower == "ldarg") {
            int argNum = stoi(tokens[i + 1]);
            instructions->push_back(makeLoadArg(argNum));
        }

        if (!isFunc) {
            if (currentToLower == "func") {
                isFunc = true;
                funcName = tokens[i + 1];
                funcArgs = stoi(tokens[i + 2]);

                instructions = new std::vector<Instruction>();
            }
        } else {
            if (currentToLower == "endfunc") {
                isFunc = false;

                DefinedFunction newFunc;
                newFunc.NumArgs = funcArgs;
                newFunc.Instructions = instructions;

                program.Functions[funcName] = newFunc;
                instructions = mainInstructions;
            }
        }
    }

    //Create the main function
    DefinedFunction mainFunc;
    mainFunc.NumArgs = 0;
    mainFunc.Instructions = mainInstructions;
    program.Functions["main"] = mainFunc;
}