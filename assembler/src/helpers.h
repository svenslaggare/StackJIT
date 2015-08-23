#pragma once
#include "parser.h"

//Contains helpers
namespace Helpers {
	//Returns the signature for the given function
	std::string getSignature(const AssemblyParser::Function& function);
};