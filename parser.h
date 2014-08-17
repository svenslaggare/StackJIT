#pragma once
#include <vector>
#include <map>
#include <string>

struct Instruction;
struct Function;
struct Program;

//The parser
namespace Parser {
	//Tokenizes from the given stream
	std::vector<std::string> tokenize(std::istream& stream);
	
	//Parses the given tokens
	void parseTokens(const std::vector<std::string>& tokens, Program& program);
}