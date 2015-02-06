#include <stdio.h>
#include <string>
#include <iostream>
#include <cxxtest/TestSuite.h>

//Executes the given command
std::string executeCmd(const char* cmd) {
    auto pipe = popen(cmd, "r");

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

    pclose(pipe);
    return result;
}

//Invokes the VM with the given program
std::string invokeVM(std::string programName, std::string options = "-nd -nogc") {
	std::string invokePath = "../StackJIT/stackjit " + options + " < programs/" + programName + ".txt 2>&1";
	return executeCmd(invokePath.data());
}

//Strips error messages of unnecessary information
std::string stripErrorMessage(std::string errorMessage) {
    std::string delimiter = "\n";
    std::size_t pos = 0;
    std::string token;

    std::string stripedString = "";

    int line = 0;

    while ((pos = errorMessage.find(delimiter)) != std::string::npos) {
        token = errorMessage.substr(0, pos);
        errorMessage.erase(0, pos + delimiter.length());

        if (line != 0 && errorMessage.length() > 0) {
            stripedString += token + "\n";
        }

        line++;
    }

    return stripedString;
}

class VMTestSuite : public CxxTest::TestSuite {
public:
    void testBasic() {
        TS_ASSERT_EQUALS(invokeVM("basic/program1"), "100\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program2"), "3\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program3"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program4"), "21\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program5"), "4\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program6"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program7"), "5\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program8"), "10\n9\n8\n7\n6\n5\n4\n3\n2\n1\n0\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program9"), "5\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program10"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program11"), "60.48\n0\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program12"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program13"), "4711\n13.37\n1\n0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("basic/invalid_program1")), "  what():  1: Locals of 'Void' type are not allowed.\n");
    }

    void testArray() {
        TS_ASSERT_EQUALS(invokeVM("array/program1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program2"), "4\n1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program3"), "1337\n4\n0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program1")), "  what():  2: Array of type 'Void' is not allowed.\n");
    }

    void testStruct() {
        TS_ASSERT_EQUALS(invokeVM("struct/program1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("struct/program2"), "4\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("struct/program3"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("struct/program4"), "0\n");
    }

    void testGC() {
        TS_ASSERT_EQUALS(invokeVM("gc/program1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program3"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program4"), "0\n");
    }
};