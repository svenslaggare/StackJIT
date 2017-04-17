#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <string>

//Contains helper methods for tests
namespace Helpers {
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
	#else
	const std::string executable = "./stackjit";
	#endif

	const std::string programsPath = "programs";


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