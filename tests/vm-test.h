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

    void testCall() {
        TS_ASSERT_EQUALS(invokeVM("calling/arg1"), "4\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg2"), "9\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg3"), "12\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg4"), "14\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg5"), "20\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg6"), "27\n");

        TS_ASSERT_EQUALS(invokeVM("calling/arg1_float"), "4\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg2_float"), "9\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg3_float"), "12\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg4_float"), "14\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg5_float"), "20\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg6_float"), "27\n0\n");
    }

    void testComparison() {
        TS_ASSERT_EQUALS(invokeVM("comparison/int_eq"), "0\n1\n0\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("comparison/int_ne"), "1\n0\n1\n4711\n");

        TS_ASSERT_EQUALS(invokeVM("comparison/int_ge"), "0\n1\n1\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("comparison/int_gt"), "0\n0\n1\n4711\n");

        TS_ASSERT_EQUALS(invokeVM("comparison/int_le"), "1\n1\n0\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("comparison/int_lt"), "1\n0\n0\n4711\n");
        
        TS_ASSERT_EQUALS(invokeVM("comparison/float_eq"), "0\n1\n0\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("comparison/float_ne"), "1\n0\n1\n4711\n");

        TS_ASSERT_EQUALS(invokeVM("comparison/float_ge"), "0\n1\n1\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("comparison/float_gt"), "0\n0\n1\n4711\n");

        TS_ASSERT_EQUALS(invokeVM("comparison/float_le"), "1\n1\n0\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("comparison/float_lt"), "1\n0\n0\n4711\n");     
    }

    void testBranch() {
        TS_ASSERT_EQUALS(invokeVM("branch/int_eq"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_eq2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/int_ne"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_ne2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/int_gt"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_gt2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/int_ge"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_ge2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_ge3"), "1\n");

        TS_ASSERT_EQUALS(invokeVM("branch/int_lt"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_lt2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/int_le"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_le2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("branch/int_le3"), "1\n");
        
        TS_ASSERT_EQUALS(invokeVM("branch/float_eq"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_eq2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/float_ne"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_ne2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/float_gt"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_gt2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/float_ge"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_ge2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_ge3"), "1\n");

        TS_ASSERT_EQUALS(invokeVM("branch/float_lt"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_lt2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/float_le"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_le2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("branch/float_le3"), "1\n");        
    }

    void testString() {
        TS_ASSERT_EQUALS(invokeVM("string/char1"), "A\n0\n");
        TS_ASSERT_EQUALS(invokeVM("string/loadstring"), "Hello, World!\n0\n");
    }

    void testArray() {
        TS_ASSERT_EQUALS(invokeVM("array/program1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program2"), "4\n1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program3"), "1337\n4\n0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program1")), "  what():  2: Array of type 'Void' is not allowed.\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/boundscheck")), "  what():  Array index is out of bounds.\n");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/boundscheck2")), "  what():  Array index is out of bounds.\n");
    }

    void testStruct() {
        TS_ASSERT_EQUALS(invokeVM("struct/program1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("struct/program2"), "4\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("struct/program3"), "0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("struct/invalid_program1")), "  what():  1: 'Point' is not a defined type.\n");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("struct/invalid_program2")), "  what():  2: 'Point' is not a struct type.\n");
    }

    void testGC() {
        TS_ASSERT_EQUALS(invokeVM("gc/program1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program3"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program4"), "0\n");
    }
};