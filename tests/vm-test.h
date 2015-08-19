#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <cxxtest/TestSuite.h>

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

//Invokes the VM with the given program
std::string invokeVM(std::string programName, std::string options = "--no-gc") {
    #if USE_VALGRIND
	std::string invokePath = "valgrind -q --error-exitcode=1 ../StackJIT/stackjit " + options + " < programs/" + programName + ".txt 2>&1";
	#else
        #if defined(_WIN64) || defined(__MINGW32__)
        std::string invokePath = "StackJIT.exe " + options + " < ../../../programs/" + programName + ".txt 2>&1";
        #else
        std::string invokePath = "../StackJIT/stackjit " + options + " < programs/" + programName + ".txt 2>&1";
        #endif
    #endif

	return executeCmd(invokePath.data());
}

static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

//Strips error messages of unnecessary information
std::string stripErrorMessage(std::string errorMessage) {
#if defined(_WIN64) || defined(__MINGW32_)
    return errorMessage;
#else
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

    return rtrim(ltrim(stripedString));
#endif
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
    }

    void testString() {
        TS_ASSERT_EQUALS(invokeVM("string/char1"), "A\n0\n");
        //TS_ASSERT_EQUALS(invokeVM("string/loadstring"), "Hello, World!\n0\n");
    }

    void testArray() {
        TS_ASSERT_EQUALS(invokeVM("array/program1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program2"), "4\n1337\n");
        TS_ASSERT_EQUALS(invokeVM("array/program3"), "1337\n4\n0\n");

        TS_ASSERT_EQUALS(invokeVM("array/largearray1"), "1337\n");

        //TS_ASSERT_EQUALS(invokeVM("array/nested"), "4\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program1")), "what():  2: Arrays of type 'Void' is not allowed.");
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

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program1")), "what():  \'Point\' is not a defined class.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program2")), "what():  2: \'Point\' is not a class type.");

        TS_ASSERT_EQUALS(invokeVM("class/constructor1"), "1\n2\n0\n");
        TS_ASSERT_EQUALS(invokeVM("class/constructor2"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("class/constructor3"), "21\n");

        TS_ASSERT_EQUALS(invokeVM("class/largeclass1"), "1337\n");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_constructor1")), "what():  Constructors must have return type 'Void'.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_constructor2")), "what():  1: The constructor \'Point::.constructor(Ref.Class.Point)\' is not defined.");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_memberfunction1")), "what():  Null reference error.");
    }

    void testException() {
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref1")), "what():  Null reference error.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref2")), "what():  Null reference error.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref3")), "what():  Null reference error.");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck")), "what():  Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck2")), "what():  Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck3")), "what():  Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck4")), "what():  Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck5")), "what():  Array index is out of bounds.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck6")), "what():  Array index is out of bounds.");

        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/invalidarraycreation")), "what():  The length of the array must be >= 0.");
    }

    void testGC() {
		//Without GC enabled
        TS_ASSERT_EQUALS(invokeVM("gc/program1"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program2"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program3"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program4"), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program5"), "0\n");

		//With GC enabled
        TS_ASSERT_EQUALS(invokeVM("gc/program1", ""), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program2", ""), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program3", ""), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program4", ""), "0\n");
        TS_ASSERT_EQUALS(invokeVM("gc/program5", ""), "0\n");
    }

    void testFunction() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/no_main")), "what():  The main function must be defined.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_main")), "what():  The main function must have the following signature: 'main() Int'.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_main2")), "what():  The main function must have the following signature: 'main() Int'.");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/already_defined")), "what():  The function 'test()' is already defined.");

		TS_ASSERT_EQUALS(invokeVM("function/overload"), "0\n");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_overload")), "what():  The function 'test(Int)' is already defined.");
    }

    void testInvalid() {
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/void_local")), "what():  1: Locals of 'Void' type are not allowed.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/empty_func")), "what():  1: Empty functions are not allowed.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/not_end_in_return")), "what():  1: Functions must end with a 'RET' instruction.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/branch_target")), "what():  1: Invalid jump target (4).");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/untyped_local1")), "what():  1: Cannot load untyped local (0).");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/untyped_local2")), "what():  1: Local 0 is not typed.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/return_type1")), "what():  Expected 'Int' as return type.");
        TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/return_type2")), "what():  Expected 'Int' as return type.");
    }

    void testLibrary() {
        #if defined(_WIN64) || defined(__MINGW32__)
		std::string baseDir = "../../../";
		std::string programsPath = baseDir + "programs";
		#else
        std::string baseDir = "";
        std::string programsPath = "programs";
		#endif

        TS_ASSERT_EQUALS(invokeVM("rtlib/program1", "--no-gc -i " + baseDir + "rtlib/rtlib.sbc"), "0.909297\n5\n0\n");

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program1", "--no-gc -i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib2.txt"),
			"1337:4711\n0\n");

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program1", "--no-gc -i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib1.txt"),
			"1337:4711\n0\n");

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program2",
			"--no-gc -i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib3.txt"),
				"1337:4711\n0\n");

		TS_ASSERT_EQUALS(invokeVM(
			"libraries/program2",
			"--no-gc -i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib2.txt"),
				"1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
            "--no-gc -i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib2.txt"),
                "1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
            "--no-gc -i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib1.txt"),
                "1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
            "--no-gc -i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib1.txt -i " + programsPath + "/libraries/lib3.txt"),
                "1337:4711\n0\n");

        TS_ASSERT_EQUALS(invokeVM(
            "libraries/program2",
            "--no-gc -i " + programsPath + "/libraries/lib2.txt -i " + programsPath + "/libraries/lib3.txt -i " + programsPath + "/libraries/lib1.txt"),
                "1337:4711\n0\n");
    }

    void testAttributes() {
        TS_ASSERT_EQUALS(invokeVM("attributes/func1"), "12\n");
        TS_ASSERT_EQUALS(invokeVM("attributes/struct1"), "0\n");
    }

    void testLazy() {
        TS_ASSERT_EQUALS(invokeVM("lazy/onlymain", "-lc 1"), "1337\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/mainwithcall", "-lc 1"), "15\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/mainwith2calls", "-lc 1"), "25\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/callchainwithoutpatching", "-lc 1"), "25\n");
        TS_ASSERT_EQUALS(invokeVM("lazy/loop", "-lc 1"), "0\n");
    }
};