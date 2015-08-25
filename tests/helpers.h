#pragma once
#include <string>
#include <vector>

//Contains helper methods for tests
namespace Helpers {
	std::vector<std::string> splitString(std::string str, std::string delimiter) {
		std::vector<std::string> parts;

		std::size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			parts.push_back(token);
			str.erase(0, pos + delimiter.length());
		}

		parts.push_back(str);

		return parts;
	}
}