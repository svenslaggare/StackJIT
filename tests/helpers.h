#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <string>

//Contains helper methods for tests
namespace Helpers {
	//Splits the given string
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

	//Executes the given command
	std::string executeCmd(const char* cmd) {
		#if defined(_WIN64) || defined(__MINGW32__)
		auto pipe = _popen(cmd, "r");
		#else
		auto pipe = popen(cmd, "r");
		#endif

		if (!pipe) {
			return "ERROR";
		}

		char buffer[128];
		std::string result = "";
		while (!feof(pipe)) {
			if (fgets(buffer, 128, pipe) != nullptr) {
				result += buffer;
			}
		}

		#if defined(_WIN64) || defined(__MINGW32__)
		_pclose(pipe);
		#else
		pclose(pipe);
		#endif
		return result;
	}

	#if defined(_WIN64) || defined(__MINGW32__)
	const std::string executable = "Debug\\stackjit.exe";
	const std::string baseDir = "../";
	const std::string programsPath = baseDir + "programs";
	#else
	const std::string executable = "./stackjit";

	#if defined(USE_CMAKE)
	const std::string baseDir = "../";
	#else
	const std::string baseDir = "";
	#endif

	const std::string programsPath = baseDir + "programs";
	#endif

	//Invokes the VM with the given program
	std::string invokeVM(std::string programName, std::string options = "--no-rtlib --allocs-before-gc 0") {
		std::string valgrindExecutable = "";

		#if USE_VALGRIND
		valgrindExecutable = "valgrind -q --error-exitcode=1 ";
		#endif

		std::string invokePath =
			valgrindExecutable + executable + " " + options
			+ " < " + programsPath + "/" + programName + ".txt 2>&1";
		return executeCmd(invokePath.data());
	}

	//Strips error messages of unnecessary information
	std::string stripErrorMessage(std::string errorMessage) {
		return errorMessage.substr(0, errorMessage.length() - 1);
	}
}