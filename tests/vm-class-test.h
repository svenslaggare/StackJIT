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
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_program2")), "main() @ 1: \'Point\' is not a class type.");
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

		TS_ASSERT_EQUALS(
			stripErrorMessage(invokeVM("class/invalid_constructor1")),
			"Constructors must have return type 'Void'.");

		TS_ASSERT_EQUALS(
			stripErrorMessage(invokeVM("class/invalid_constructor2")),
			"main() @ 0: The constructor \'Point::.constructor()\' is not defined.");

		TS_ASSERT_EQUALS(
			stripErrorMessage(invokeVM("class/invalid_constructor3")),
			"main() @ 3: Cannot call constructor 'Point2D::.constructor(Int Int)'.");
	}

	//Tests null
	void testNull() {
		TS_ASSERT_EQUALS(invokeVM("class/null1"), "true\nfalse\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/null2"), "true\nfalse\n0\n");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_memberfunction1")), "Error: Null reference.");
	}

	//Tests access modifiers
	void testAccess() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/callingprivate1")), "main() @ 1: Cannot call private function 'Point::length()'.");
		TS_ASSERT_EQUALS(invokeVM("class/callingprivate2"), "0\n");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/accessingprivate1")), "main() @ 1: Cannot read from private field 'x' of class 'Point'.");
		TS_ASSERT_EQUALS(invokeVM("class/accessingprivate2"), "0\n");
	}

	//Tests inheritance
	void testInheritance() {
		TS_ASSERT_EQUALS(invokeVM("class/inheritance1", "--allocs-before-gc 0"), "A\nA\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/inheritance2", "--allocs-before-gc 0"), "2\n4\n6\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/inheritance3", "--allocs-before-gc 0"), "2\n4\n0\n");
		TS_ASSERT_EQUALS(invokeVM("class/inheritance4", "--allocs-before-gc 0"), "1\n2\n3\n0\n");

		TS_ASSERT_EQUALS(
			stripErrorMessage(invokeVM("class/invalid_inheritance1")),
			"Self inheritance is not allowed (Point3D).");

		TS_ASSERT_EQUALS(
			stripErrorMessage(invokeVM("class/invalid_inheritance2")),
			"Mutual inheritance is not allowed (Point2D, Point3D).");

		TS_ASSERT_EQUALS(
			stripErrorMessage(invokeVM("class/invalid_inheritance3")),
			"Point3D::.constructor(Int Int Int) @ 3: Cannot call constructor 'Point2D::.constructor(Int Int)'.");
	}

	//Tests invalid field
	void testInvalidFields() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_field1")), "main() @ 1: There exists no field 'x' in the 'Point2D' class.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_field2")), "main() @ 2: There exists no field 'x' in the 'Point2D' class.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_field3")), "The field 'x' is already defined in the class 'Point2D'.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("class/invalid_field4")), "The field 'x' is already defined in the class 'Point3D'.");
	}
};