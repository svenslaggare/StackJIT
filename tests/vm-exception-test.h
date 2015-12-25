#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests exceptions
 */
class VMExceptionTestSuite : public CxxTest::TestSuite {
public:
	//Tests null ref
	void testNullRef() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref1")), "Error: Null reference.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref2")), "Error: Null reference.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/nullref3")), "Error: Null reference.");
	}

	//Tests bounds check
	void testBoundsCheck() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck")), "Error: Array index is out of bounds.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck2")), "Error: Array index is out of bounds.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck3")), "Error: Array index is out of bounds.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck4")), "Error: Array index is out of bounds.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck5")), "Error: Array index is out of bounds.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/boundscheck6")), "Error: Array index is out of bounds.");
	}

	//Tests invalid array creation
	void testInvalidArrayCreation() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("exception/invalidarraycreation")), "Error: The length of the array must be >= 0.");
	}
};