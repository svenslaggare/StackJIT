#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <cxxtest/TestSuite.h>
#include <cstdio>
#include <vector>

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
std::string executable = "StackAsm.exe";
std::string programsPath = "../../../" + "programs";
#else
std::string executable = "./stackasm";
std::string programsPath = "programs";
#endif

//Invokes the assembler with the given program
std::string invokeAsm(std::string programName) {
	std::string tmpName = std::to_string(std::time(nullptr)) + ".simg";
	executeCmd((executable + " -o " + tmpName + " " + programsPath + "/" + programName + ".txt 2>&1").data());
	std::string returnData = executeCmd((executable + " -d " + tmpName + " 2>&1").data());
	std::remove(tmpName.data());
	return returnData;
}

//Reads the content of the given file
std::string readFile(std::string programName) {
	std::ifstream file(programsPath + "/" + programName + ".txt");
	std::string content = "";

	std::string line;
	while (!file.eof()) {
		std::getline(file, line);
		content += line + "\n";
	}

	return content;
}

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

//Splits the given string into parts
std::vector<std::string> splitParts(std::string str) {
	std::vector<std::string> parts;
	std::string part;
	int body = 0;

	for (auto& line : splitString(str, "\n")) {
		if (line == "{") {
			body++;
		} else if (line == "}") {
			body--;
		}

		if (line == "" && body == 0) {
			parts.push_back(part);
			part.clear();
		}

		part += line + "\n";
	}

	parts.push_back(part);
	return parts;
}

std::string joinParts(std::vector<std::string> parts) {
	//Sort parts
	std::sort(parts.begin(), parts.end());

	//Join
	std::string str = "";

	bool isFirst = true;
	for (auto& part : parts) {
		if (!isFirst) {
			str += "\n";
		} else {
			isFirst = false;
		}

		str += part;
	}

	return str;
}

#define ASM_ASSERT_EQUALS(x, y) TS_ASSERT_EQUALS(joinParts(splitParts(x)), joinParts(splitParts(y)))

class AssemblerTestSuite : public CxxTest::TestSuite {
public:
	void testCase1() {
		ASM_ASSERT_EQUALS(invokeAsm("test1"), readFile("test1"));
	}

	void testCase2() {
		ASM_ASSERT_EQUALS(invokeAsm("test2"), readFile("test2"));
	}

	void testCase3() {
		ASM_ASSERT_EQUALS(invokeAsm("test3"), readFile("test3"));
	}

	void testCase4() {
		ASM_ASSERT_EQUALS(invokeAsm("test4"), readFile("test4"));
	}

	void testCase5() {
		ASM_ASSERT_EQUALS(invokeAsm("test5"), "The function 'test(Int)' is already defined.\n");
	}

	void testCase6() {
		ASM_ASSERT_EQUALS(invokeAsm("test6"), readFile("test6"));
	}

	void testCase7() {
		ASM_ASSERT_EQUALS(invokeAsm("test6"), readFile("test6"));
	}
};