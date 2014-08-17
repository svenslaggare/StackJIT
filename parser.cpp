#include <cctype>
#include <string>
#include <iostream>

#include "parser.h"
#include "instructions.h"
#include "codegenerator.h"
#include "program.h"

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
    int numLocals = 4;

    //Create the main function
    Function* mainFunc = new Function;
    mainFunc->Name = "main";
    mainFunc->NumArgs = 0;
    mainFunc->NumLocals = 4;
    program.Functions["main"] = mainFunc;

    Function* currentFunc = mainFunc;

    for (int i = 0; i < tokens.size(); i++) {
        std::string current = tokens[i];
        std::string currentToLower = toLower(current);

        if (currentToLower == "push") {
            int value = stoi(tokens[i + 1]);
            currentFunc->Instructions.push_back(makePushInt(value));
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
            currentFunc->Instructions.push_back(makeLoadLocal(local));
        }

        if (currentToLower == "stloc") {
            int local = stoi(tokens[i + 1]);
            currentFunc->Instructions.push_back(makeStoreLocal(local));
        }

        if (currentToLower == "call") {
            std::string funcName = tokens[i + 1];
            int numArgs = stoi(tokens[i + 2]);
            currentFunc->Instructions.push_back(makeCall(funcName, numArgs));
        }

        if (currentToLower == "ldarg") {
            int argNum = stoi(tokens[i + 1]);
            currentFunc->Instructions.push_back(makeLoadArg(argNum));
        }

        if (!isFunc) {
            if (currentToLower == "func") {
                isFunc = true;
                funcName = tokens[i + 1];
                funcArgs = stoi(tokens[i + 2]);

                //Create a new function        
                Function* newFunc = new Function;
                newFunc->Name = funcName;
                newFunc->NumArgs = funcArgs;
                newFunc->NumLocals = numLocals;
                program.Functions[funcName] = newFunc;

                currentFunc = newFunc;
            }
        } else {
            if (currentToLower == "endfunc") {
                isFunc = false;
                currentFunc = mainFunc;
            }
        }
    }
}