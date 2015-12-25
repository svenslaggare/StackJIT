#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests classes
 */
class VMClassTestSuite : public CxxTest::TestSuite {
public:
	//Tests basic
	void testBasic() {
		TS_ASSERT_EQUALS(invokeVM("class/program1"), "1337\n");
		TS_ASSERT_EQUALS(invokeVM("class/program2"), "4\n4711\n");
		TS_ASSERT_EQUALS(invokeVM("class/program3"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("class/program4"), "1337:4711\n0\n");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program1")), "\'Point\' is not a defined class.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program2")), "1: \'Point\' is not a class type.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program3")), "There exists no type called 'Ref.Point'.");

		TS_ASSERT_EQUALS(invokeVM("class/largeclass1"), "1337\n");
	}

	//Tests with nested and recursive classes
	void testNested() {

		TS_ASSERT_EQUALS(invokeVM("class/recursiveclass1"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("class/classwithclass1"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("class/classwithclass2"), "0\n");
	}

	//Tests member functions
	void testMemberFunction() {
		TS_ASSERT_EQUALS(invokeVM("class/memberfunction1"), "3.60555\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/memberfunction2"), "5\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/memberfunction3"), "2.5\n5.5\n0\n");
	}

	//Tests constructors
	void testConstructor() {
		TS_ASSERT_EQUALS(invokeVM("class/constructor1"), "1\n2\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/constructor2"), "15\n");
		TS_ASSERT_EQUALS(invokeVM("class/constructor3"), "21\n");

		TS_ASSERT_EQUALS(stripErrorMessage(
							 invokeVM("class/invalid_constructor1")),
						 "Constructors must have return type 'Void'.");

		TS_ASSERT_EQUALS(stripErrorMessage(
							 invokeVM("class/invalid_constructor2")),
						 "0: The constructor \'Point::.constructor(Ref.Point)\' is not defined.");
	}

	//Tests null
	void testNull() {
		TS_ASSERT_EQUALS(invokeVM("class/null1"), "true\nfalse\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/null2"), "true\nfalse\n0\n");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_memberfunction1")), "Error: Null reference.");
	}

	//Tests access modifiers
	void testAccess() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/callingprivate1")), "1: Cannot call private function 'Point::length(Ref.Point)'.");
		TS_ASSERT_EQUALS(invokeVM("class/callingprivate2"), "0\n");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/accessingprivate1")), "1: Cannot read from private field 'x' of class 'Point'.");
		TS_ASSERT_EQUALS(invokeVM("class/accessingprivate2"), "0\n");
	}
};