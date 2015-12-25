#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests loading libraries
 */
class VMLibraryTestSuite : public CxxTest::TestSuite {
public:
	//Tests loading
	void testLoading() {
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
};