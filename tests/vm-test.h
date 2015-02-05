#include <stdio.h>
#include <string>
#include <iostream>
#include <cxxtest/TestSuite.h>

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

std::string invokeVM(std::string programName) {
	std::string invokePath = "../StackJIT/stackjit -nd < programs/" + programName + ".txt";
	return executeCmd(invokePath.data());
}

class VMTestSuite : public CxxTest::TestSuite {
public:
    void testBasic() {
        TS_ASSERT_EQUALS(invokeVM("program1"), "100\n");
        TS_ASSERT_EQUALS(invokeVM("program2"), "3\n");
        TS_ASSERT_EQUALS(invokeVM("program3"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("program4"), "21\n");
        TS_ASSERT_EQUALS(invokeVM("program5"), "4\n");
        TS_ASSERT_EQUALS(invokeVM("program6"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("program7"), "5\n");
        TS_ASSERT_EQUALS(invokeVM("program8"), "10\n9\n8\n7\n6\n5\n4\n3\n2\n1\n0\n");
    }
};