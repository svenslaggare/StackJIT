#pragma once
#include <vector>
#include <map>
#include <string>

struct Instruction;

struct Program {
    std::map<std::string, std::vector<Instruction>*> Functions;
    std::map<std::string, long> CallTable;
};

std::vector<std::string> tokenizeInput();

void parseTokens(const std::vector<std::string>& tokens, Program& program);