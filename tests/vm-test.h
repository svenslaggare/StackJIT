#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <cxxtest/TestSuite.h>
#include <regex>
#include "helpers.h"

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
std::string executable = "StackJIT.exe";
std::string baseDir = "../../../";
std::string programsPath = baseDir + "programs";
#else
std::string executable = "./stackjit";
std::string baseDir = "";
std::string programsPath = "programs";
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

//Contains info about an GC
struct GC {
    std::string funcName;
    int instructionIndex;
    std::vector<std::size_t> deallocatedObjects;

    bool hasDeallocated(std::size_t obj) {
        for (auto current : deallocatedObjects) {
            if (current == obj) {
                return true;
            }
        }

        return false;
    }
};

//Holds all data for a GC test
struct GCTest {
    std::vector<std::size_t> allocatedObjects;
    std::vector<GC> collections;
};

//Parses the GC data
std::string parseGCData(std::string data, GCTest& gcTest) {
    gcTest = {};

    //Split into lines
    auto lines = Helpers::splitString(data, "\n");
    GC currentGC;
    bool hasFound = false;

    std::regex gcStartRegex("Start GC in func (.*) \\((.*)\\)", std::regex_constants::ECMAScript);
    std::regex gcEndRegex("End GC", std::regex_constants::ECMAScript);
    std::regex allocatedObjectRegex("Allocated ((object)|(array)) \\(.*\\) at (.*)", std::regex_constants::ECMAScript);
    std::regex deallocatedObjectRegex("Deleted object: (.*):", std::regex_constants::ECMAScript);
    std::regex programOutputRegex("Program output:", std::regex_constants::ECMAScript);
    std::regex returnValueRegex("Return value.*", std::regex_constants::ECMAScript);
    std::regex loadTimeRegex("Load time.*", std::regex_constants::ECMAScript);

    std::string output = "";
    for (auto line : lines) {
        if (line == "") {
            continue;
        }

        std::smatch match;
        if (std::regex_search(line, match, gcStartRegex)) {
            currentGC = {};
            currentGC.funcName = match[1];
            currentGC.instructionIndex = std::stoi(match[2]);
            hasFound = true;
        } else if (std::regex_search(line, gcEndRegex)) {
            gcTest.collections.push_back(currentGC);
        } else if (std::regex_search(line, match, allocatedObjectRegex)) {
            gcTest.allocatedObjects.push_back(std::stoull(match[4], nullptr, 16));
        } else if (std::regex_search(line, match, deallocatedObjectRegex)) {
            currentGC.deallocatedObjects.push_back(std::stoull(match[1], nullptr, 16));
        } else if (std::regex_search(line, programOutputRegex)
                   || std::regex_search(line, returnValueRegex)
                   || std::regex_search(line, loadTimeRegex)) {
            //Skip these lines
        } else {
            output += line + "\n";
        }
    }

    return output;
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
        TS_ASSERT_EQUALS(invokeVM("basic/program14"), "2\n");
        TS_ASSERT_EQUALS(invokeVM("basic/program15"), "-2\n");

        TS_ASSERT_EQUALS(invokeVM("basic/recursion1"), "21\n");
		TS_ASSERT_EQUALS(invokeVM("basic/duplicate1"), "10\n");
    }

	void testStack() {
		TS_ASSERT_EQUALS(invokeVM("stack/call_preserve_stack"), "17\n");
		TS_ASSERT_EQUALS(invokeVM("stack/float_alignment"), "13\n13\n13\n0\n");
		TS_ASSERT_EQUALS(invokeVM("stack/largestackframe1"), "55\n");
		TS_ASSERT_EQUALS(invokeVM("stack/largestackframe2"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("stack/largestackframe3"), "0\n");
	}

    void testCall() {
        TS_ASSERT_EQUALS(invokeVM("calling/arg1"), "4\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg2"), "9\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg2_2"), "7\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg3"), "12\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg4"), "14\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg5"), "20\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg6"), "27\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg7"), "35\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg7_2"), "1337\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg8"), "44\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg8_2"), "7\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg8_3"), "6\n7\n0\n");
		TS_ASSERT_EQUALS(invokeVM("calling/arg9"), "54\n");
		TS_ASSERT_EQUALS(invokeVM("calling/arg10"), "65\n");

        TS_ASSERT_EQUALS(invokeVM("calling/arg1_float"), "4\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg2_float"), "9\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg3_float"), "12\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg4_float"), "14\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg5_float"), "20\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg6_float"), "27\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg6_float_2"), "6\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg7_float"), "35\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg7_float_2"), "1337\n0\n");
		TS_ASSERT_EQUALS(invokeVM("calling/arg8_float"), "44\n0\n");
		TS_ASSERT_EQUALS(invokeVM("calling/arg9_float"), "54\n0\n");

        TS_ASSERT_EQUALS(invokeVM("calling/arg6_float_and_int"), "27\n0\n");
        TS_ASSERT_EQUALS(invokeVM("calling/arg6_float_and_int_2"), "27\n0\n");
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

        TS_ASSERT_EQUALS(invokeVM("comparison/ref_eq"), "false\ntrue\nfalse\nfalse\n0\n");
        TS_ASSERT_EQUALS(invokeVM("comparison/ref_ne"), "true\nfalse\ntrue\ntrue\n0\n");

        TS_ASSERT_EQUALS(invokeVM("comparison/largestackframe"), "0\n1\n0\n4711\n");
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

        TS_ASSERT_EQUALS(invokeVM("branch/ref_eq1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("branch/ref_eq2"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/ref_eq3"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("branch/ref_ne1"), "1\n");
        TS_ASSERT_EQUALS(invokeVM("branch/ref_ne2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("branch/ref_ne3"), "1\n");
    }

    void testString() {
        TS_ASSERT_EQUALS(invokeVM("string/char1"), "A\n0\n");
        TS_ASSERT_EQUALS(invokeVM("string/loadstring", ""), "Hello, World!\n0\n");
        TS_ASSERT_EQUALS(invokeVM("string/constructor1", ""), "KBCD\nABCD\n0\n");
    }

    void testArray() {
        TS_ASSERT_EQUALS(invokeVM("array/program1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program2"), "4\n1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program3"), "1337\n4\n0\n");

        TS_ASSERT_EQUALS(invokeVM("array/largearray1"), "1337\n");

        TS_ASSERT_EQUALS(invokeVM("array/nested"), "4\n");

        TS_ASSERT_EQUALS(invokeVM("array/intarray"), "1\n2\n3\n4\n0\n");
        TS_ASSERT_EQUALS(invokeVM("array/floatarray"), "1.5\n2.5\n3.5\n4.5\n0\n");
        TS_ASSERT_EQUALS(invokeVM("array/boolarray"), "false\ntrue\nfalse\ntrue\n0\n");
        TS_ASSERT_EQUALS(invokeVM("array/refarray"), "1:2\n2:3\n3:4\n4:5\n0\n");
        TS_ASSERT_EQUALS(invokeVM("array/chararray"), "A\nB\nC\nD\n0\n");
        TS_ASSERT_EQUALS(invokeVM("array/refwithnullarray", ""), "1:2\n2:3\n3:4\nnull\n0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program1")), "1: Arrays of type 'Void' is not allowed.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program2")), "1: 'RT' is not a valid type.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program3")), "5: There exists no type 'RT'.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program4")), "6: There exists no type 'RT'.");
    }

    void testClasses() {
        TS_ASSERT_EQUALS(invokeVM("class/program1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("class/program2"), "4\n4711\n");
        TS_ASSERT_EQUALS(invokeVM("class/program3"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("class/program4"), "1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM("class/recursiveclass1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("class/classwithclass1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("class/classwithclass2"), "0\n");

        TS_ASSERT_EQUALS(invokeVM("class/memberfunction1"), "3.60555\n0\n");
        TS_ASSERT_EQUALS(invokeVM("class/memberfunction2"), "5\n0\n");
        TS_ASSERT_EQUALS(invokeVM("class/memberfunction3"), "2.5\n5.5\n0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program1")), "\'Point\' is not a defined class.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program2")), "1: \'Point\' is not a class type.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program3")), "There exists no type called 'Ref.Point'.");

        TS_ASSERT_EQUALS(invokeVM("class/constructor1"), "1\n2\n0\n");
        TS_ASSERT_EQUALS(invokeVM("class/constructor2"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("class/constructor3"), "21\n");

        TS_ASSERT_EQUALS(invokeVM("class/largeclass1"), "1337\n");

        TS_ASSERT_EQUALS(invokeVM("class/null1"), "true\nfalse\n0\n");
        TS_ASSERT_EQUALS(invokeVM("class/null2"), "true\nfalse\n0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(
            invokeVM("class/invalid_constructor1")),
            "Constructors must have return type 'Void'.");

        TS_ASSERT_EQUALS(stripErrorMessage(
			invokeVM("class/invalid_constructor2")),
			"0: The constructor \'Point::.constructor(Ref.Point)\' is not defined.");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_memberfunction1")), "Error: Null reference.");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/callingprivate1")), "1: Cannot call private function 'Point::length(Ref.Point)'.");
        TS_ASSERT_EQUALS(invokeVM("class/callingprivate2"), "0\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/accessingprivate1")), "1: Cannot read from private field 'x' of class 'Point'.");
        TS_ASSERT_EQUALS(invokeVM("class/accessingprivate2"), "0\n");
    }

    void testException() {
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref1")), "Error: Null reference.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref2")), "Error: Null reference.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref3")), "Error: Null reference.");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck")), "Error: Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck2")), "Error: Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck3")), "Error: Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck4")), "Error: Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck5")), "Error: Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck6")), "Error: Array index is out of bounds.");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/invalidarraycreation")), "Error: The length of the array must be >= 0.");
    }

    void testGCExplicit() {
        std::string options = "-d --print-alloc --print-dealloc --print-gc-period --allocs-before-gc 0 --no-gc --no-rtlib";
        GCTest gcTest;

        TS_ASSERT_EQUALS(
            parseGCData(invokeVM("gc/callstack1", options), gcTest),
            "0\n");

        TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 3);
        TS_ASSERT_EQUALS(gcTest.collections.size(), 2);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);
        TS_ASSERT_EQUALS(gcTest.collections.at(1).deallocatedObjects.size(), 3);
        TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(0)), true);
        TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
        TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(2)), true);

        TS_ASSERT_EQUALS(
            parseGCData(invokeVM("gc/alive_on_stack1", options), gcTest),
            "0\n");

        TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 2);
        TS_ASSERT_EQUALS(gcTest.collections.size(), 3);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);
        TS_ASSERT_EQUALS(gcTest.collections.at(1).deallocatedObjects.size(), 1);
        TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
        TS_ASSERT_EQUALS(gcTest.collections.at(2).deallocatedObjects.size(), 1);
        TS_ASSERT_EQUALS(gcTest.collections.at(2).hasDeallocated(gcTest.allocatedObjects.at(0)), true);

        TS_ASSERT_EQUALS(
            parseGCData(invokeVM("gc/locals1", options), gcTest),
            "0\n");

        TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 2);
        TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);

        TS_ASSERT_EQUALS(
            parseGCData(invokeVM("gc/locals2", options), gcTest),
            "0\n");

        TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 3);
        TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 2);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(0)), true);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(1)), true);

        TS_ASSERT_EQUALS(
            parseGCData(invokeVM("gc/ref_elements", options), gcTest),
            "0\n");

        TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 4);
        TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);

        TS_ASSERT_EQUALS(
            parseGCData(invokeVM("gc/ref_fields", options), gcTest),
            "0\n");

        TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 2);
        TS_ASSERT_EQUALS(gcTest.collections.size(), 3);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);
        TS_ASSERT_EQUALS(gcTest.collections.at(1).deallocatedObjects.size(), 0);
        TS_ASSERT_EQUALS(gcTest.collections.at(2).deallocatedObjects.size(), 0);
    }

    void testGCImplicit() {
        TS_ASSERT_EQUALS(invokeVM("gc/callstack1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/alive_on_stack1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/locals1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/locals2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/ref_elements"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/ref_fields"), "0\n")

        std::string options = "-d --print-alloc --print-dealloc --print-gc-period --no-rtlib";
        GCTest gcTest;

        TS_ASSERT_EQUALS(
            parseGCData(invokeVM("gc/gctime", options + " --allocs-before-gc 2"), gcTest),
            "0\n");

        TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 4);
        TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 2);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(0)), true);
        TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
    }

    void testFunction() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/no_main")), "The main function must be defined.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_main")), "The main function must have the following signature: 'main() Int'.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_main2")), "The main function must have the following signature: 'main() Int'.");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/already_defined")), "The function 'test()' is already defined.");

		TS_ASSERT_EQUALS(invokeVM("function/overload"), "0\n");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_overload")), "The function 'test(Int)' is already defined.");
    }

    void testInvalid() {
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/void_local")), "0: Locals of 'Void' type are not allowed.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/empty_func")), "0: Empty functions are not allowed.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/not_end_in_return")), "0: Functions must end with the 'RET' instruction.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/branch_target")), "0: Invalid jump target (4).");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/untyped_local1")), "0: Cannot load untyped local (0).");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/untyped_local2")), "0: Local 0 is not typed.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/return_type1")), "Expected 'Int' as return type.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/return_type2")), "Expected 'Int' as return type.");
    }

    void testLibrary() {
		std::string options = "--no-rtlib --allocs-before-gc 0 ";

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program1", options + "-i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib2.txt"),
			"1337:4711\n0\n");

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program1", options + "-i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib1.txt"),
			"1337:4711\n0\n");

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program2",
			options + "-i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib3.txt"),
			"1337:4711\n0\n");

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program2",
			options + "-i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib2.txt"),
			"1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
			options + "-i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib2.txt"),
            "1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
			options + "-i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib1.txt"),
            "1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
			options + "-i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib3.txt"),
			"1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
			options + "-i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib1.txt"),
            "1337:4711\n0\n");
    }

    void testRuntimeLibrary() {
        TS_ASSERT_EQUALS(invokeVM("rtlib/program1", ""), "0.909297\n5\n0\n");

        TS_ASSERT_EQUALS(invokeVM("rtlib/string1", ""), "Hello, World!\n0\n");
        TS_ASSERT_EQUALS(invokeVM("rtlib/string2", ""), "true\n0\n");
        TS_ASSERT_EQUALS(invokeVM("rtlib/string3", ""), "false\n0\n");
        TS_ASSERT_EQUALS(invokeVM("rtlib/string4", ""), "false\n0\n");
        TS_ASSERT_EQUALS(invokeVM("rtlib/string4", ""), "false\n0\n");
        TS_ASSERT_EQUALS(invokeVM("rtlib/string5", ""), "false\n0\n");
        TS_ASSERT_EQUALS(invokeVM("rtlib/string6", ""), "false\n0\n");
    }

    void testNative() {
        TS_ASSERT_EQUALS(invokeVM("native/arrayref1", "--no-rtlib --test"), "ABCD\n0\n");
        TS_ASSERT_EQUALS(invokeVM("native/structref1", "--no-rtlib --test"), "1337:4711\n0\n");
    }

    void testAttributes() {
        TS_ASSERT_EQUALS(invokeVM("attributes/func1"), "12\n");
        TS_ASSERT_EQUALS(invokeVM("attributes/struct1"), "0\n");
    }

    void testLazy() {
        TS_ASSERT_EQUALS(invokeVM("lazy/onlymain", "--no-rtlib -lc 1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/mainwithcall", "--no-rtlib -lc 1"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/mainwith2calls", "--no-rtlib -lc 1"), "25\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/callchainwithoutpatching", "--no-rtlib -lc 1"), "25\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/loop", "--no-rtlib -lc 1"), "0\n");
    }
};
