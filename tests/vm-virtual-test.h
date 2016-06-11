#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests virtual functions
 */
class VMVirtualTestSuite : public CxxTest::TestSuite {
public:
	void testSimple() {
		TS_ASSERT_EQUALS(invokeVM("virtual/simple1"), "36\n");
		TS_ASSERT_EQUALS(invokeVM("virtual/simple2"), "288\n");
		TS_ASSERT_EQUALS(invokeVM("virtual/loop"), "0\n");
	}

	void testInheritance() {
		TS_ASSERT_EQUALS(invokeVM("virtual/inheritance1", ""), "A\nB\nB\nB\n0\n");
	}
};