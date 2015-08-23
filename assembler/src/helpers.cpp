#include "helpers.h"

std::string Helpers::getSignature(const AssemblyParser::Function& function) {
	std::string signature = "";

	signature += function.name;
	signature += "(";

	bool isFirst = true;

	std::size_t start = 0;

	if (function.isMemberFunction) {
		start = 1;
	}

	for (std::size_t i = start; i < function.parameters.size(); i++) {
		auto param = function.parameters[i];
		if (!isFirst) {
			signature += " ";
		} else {
			isFirst = false;
		}

		signature += param;
	}

	signature += ")";

	return signature;
}