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

class AssemblerTestSuite : public CxxTest::TestSuite {
public:
	void testCase1() {
		TS_ASSERT_EQUALS(invokeAsm("test1"), readFile("test1"));
	}

	void testCase2() {
		TS_ASSERT_EQUALS(invokeAsm("test2"), readFile("test2"));
	}

	void testCase3() {
		TS_ASSERT_EQUALS(invokeAsm("test3"), readFile("test3"));
	}

	void testCase4() {
		TS_ASSERT_EQUALS(invokeAsm("test4"), readFile("test4"));
	}

	void testCase5() {
		TS_ASSERT_EQUALS(invokeAsm("test5"), "The function 'test(Int)' is already defined.\n");
	}

	void testCase6() {
		TS_ASSERT_EQUALS(invokeAsm("test6"), readFile("test6"));
	}

	void testCase7() {
		TS_ASSERT_EQUALS(invokeAsm("test6"), readFile("test6"));
	}
};