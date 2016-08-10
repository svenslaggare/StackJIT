#include "helpers.h"

namespace stackjit {
	std::int64_t Helpers::getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> timePoint) {
		auto end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - timePoint).count();
	}

	void Helpers::pushArray(std::vector<unsigned char>& dest, const std::vector<unsigned char>& values) {
		for (auto current : values) {
			dest.push_back(current);
		}
	}

	bool Helpers::validCharValue(int value) {
		return value >= -128 && value < 128;
	}

	std::vector<std::string> Helpers::splitString(std::string str, std::string delimiter) {
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
