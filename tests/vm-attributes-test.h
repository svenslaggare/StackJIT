#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

//Test attributes
class VMAttributesTestSuite : public CxxTest::TestSuite {
public:
	//Tests in functions
	void testFunc() {
		TS_ASSERT_EQUALS(invokeVM("attributes/func1"), "12\n");
	}

	//Tests in classes
	void testClass() {
		TS_ASSERT_EQUALS(invokeVM("attributes/class1"), "0\n");
	}
};