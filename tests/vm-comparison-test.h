#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests comparison
 */
class VMComparisonTestSuite : public CxxTest::TestSuite {
public:
	//Test with int types
	void testInt() {
		TS_ASSERT_EQUALS(invokeVM("comparison/int_eq"), "0\n1\n0\n4711\n");
		TS_ASSERT_EQUALS(invokeVM("comparison/int_ne"), "1\n0\n1\n4711\n");

		TS_ASSERT_EQUALS(invokeVM("comparison/int_ge"), "0\n1\n1\n4711\n");
		TS_ASSERT_EQUALS(invokeVM("comparison/int_gt"), "0\n0\n1\n4711\n");

		TS_ASSERT_EQUALS(invokeVM("comparison/int_le"), "1\n1\n0\n4711\n");
		TS_ASSERT_EQUALS(invokeVM("comparison/int_lt"), "1\n0\n0\n4711\n");
	}

	//Tests with float type
	void testFloat() {
		TS_ASSERT_EQUALS(invokeVM("comparison/float_eq"), "0\n1\n0\n4711\n");
		TS_ASSERT_EQUALS(invokeVM("comparison/float_ne"), "1\n0\n1\n4711\n");

		TS_ASSERT_EQUALS(invokeVM("comparison/float_ge"), "0\n1\n1\n4711\n");
		TS_ASSERT_EQUALS(invokeVM("comparison/float_gt"), "0\n0\n1\n4711\n");

		TS_ASSERT_EQUALS(invokeVM("comparison/float_le"), "1\n1\n0\n4711\n");
		TS_ASSERT_EQUALS(invokeVM("comparison/float_lt"), "1\n0\n0\n4711\n");
	}

	//Tests with ref type
	void testRef() {
		TS_ASSERT_EQUALS(invokeVM("comparison/ref_eq"), "false\ntrue\nfalse\nfalse\n0\n");
		TS_ASSERT_EQUALS(invokeVM("comparison/ref_ne"), "true\nfalse\ntrue\ntrue\n0\n");
	}

	//Tests with large stack frame
	void testLargeStackFrame() {
		TS_ASSERT_EQUALS(invokeVM("comparison/largestackframe"), "0\n1\n0\n4711\n");
	}
};