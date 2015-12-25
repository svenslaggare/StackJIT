#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests functions in the runtime library
 */
class VMRuntimeLibraryTestSuite : public CxxTest::TestSuite {
public:
	/**
	 * Tests functions from the runtime library
	 */
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

	/*
	 * Tests functions defined in native code
	 */
	void testNative() {
		TS_ASSERT_EQUALS(invokeVM("native/arrayref1", "--no-rtlib --test"), "ABCD\n0\n");
		TS_ASSERT_EQUALS(invokeVM("native/structref1", "--no-rtlib --test"), "1337:4711\n0\n");
	}
};