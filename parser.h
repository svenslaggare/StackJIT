#pragma once
#include <vector>
#include <map>
#include <string>

struct Instruction;

std::vector<std::string> tokenizeInput();

void parseTokens(const std::vector<std::string>& tokens, std::map<std::string, long>& callTable, std::vector<Instruction>& instructions);