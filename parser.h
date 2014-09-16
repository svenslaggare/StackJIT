#pragma once
#include <vector>
#include <map>
#include <string>

struct Instruction;
struct Function;
struct Program;
class VMState;

//The parser
namespace Parser {
	//Tokenizes from the given stream
	std::vector<std::string> tokenize(std::istream& stream);
	
	//Parses the given tokens
	void parseTokens(const std::vector<std::string>& tokens, VMState& vmState, Program& program);
}