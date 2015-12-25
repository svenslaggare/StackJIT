#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests arrays
 */
class VMArrayTestSuite : public CxxTest::TestSuite {
public:
	//Tests basic handling
	void testBasic() {
		TS_ASSERT_EQUALS(invokeVM("array/program1"), "1337\n");
		TS_ASSERT_EQUALS(invokeVM("array/program2"), "4\n1337\n");
		TS_ASSERT_EQUALS(invokeVM("array/program3"), "1337\n4\n0\n");

		TS_ASSERT_EQUALS(invokeVM("array/largearray1"), "1337\n");

		TS_ASSERT_EQUALS(invokeVM("array/nested"), "4\n");
	}

	//Tests with different types
	void testTypes() {
		TS_ASSERT_EQUALS(invokeVM("array/intarray"), "1\n2\n3\n4\n0\n");
		TS_ASSERT_EQUALS(invokeVM("array/floatarray"), "1.5\n2.5\n3.5\n4.5\n0\n");
		TS_ASSERT_EQUALS(invokeVM("array/boolarray"), "false\ntrue\nfalse\ntrue\n0\n");
		TS_ASSERT_EQUALS(invokeVM("array/refarray"), "1:2\n2:3\n3:4\n4:5\n0\n");
		TS_ASSERT_EQUALS(invokeVM("array/chararray"), "A\nB\nC\nD\n0\n");
		TS_ASSERT_EQUALS(invokeVM("array/refwithnullarray", ""), "1:2\n2:3\n3:4\nnull\n0\n");
	}

	//Tests with invalid usage
	void testInvalid() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program1")), "1: Arrays of type 'Void' is not allowed.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program2")), "1: 'RT' is not a valid type.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program3")), "5: There exists no type 'RT'.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("array/invalid_program4")), "6: There exists no type 'RT'.");
	}
};