#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests strings
 */
class VMStringTestSuite : public CxxTest::TestSuite {
public:
	//Tests chars
	void testChar() {
		TS_ASSERT_EQUALS(invokeVM("string/char1"), "A\n0\n");
	}

	//Tests creating using ldstr instruction
	void testCreate() {
		TS_ASSERT_EQUALS(invokeVM("string/loadstring", ""), "Hello, World!\n0\n");
	}

	//Tests constructor
	void testConstructor() {
		TS_ASSERT_EQUALS(invokeVM("string/constructor1", ""), "KBCD\nABCD\n0\n");
	}
};