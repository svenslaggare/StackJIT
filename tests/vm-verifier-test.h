#include <cxxtest/TestSuite.h>
#include "helpers.h"

using namespace Helpers;

/**
 * Tests the verifier
 */
class VMTestSuite : public CxxTest::TestSuite {
public:
	//Tests invalid functions
	void testFunction() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/no_main")), "The main function must be defined.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_main")), "The main function must have the signature: 'main() Int' but got 'main(Int) Int'.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_main2")), "The main function must have the signature: 'main() Int' but got 'main() Void'.");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/already_defined")), "The function 'test()' is already defined.");

		TS_ASSERT_EQUALS(invokeVM("function/overload"), "0\n");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("function/invalid_overload")), "The function 'test(Int)' is already defined.");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/empty_func")), "test() @ 0: Empty functions are not allowed.");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/not_end_in_return")), "main() @ 0: Functions must end with the 'RET' instruction.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/return_type1")), "Expected 'Int' as the return type.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/return_type2")), "Expected 'Int' as the return type.");

		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/non_virtual_func1")), "main() @ 1: Non virtual member functions must be called with the 'CALLINST' instruction.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/non_virtual_func2")), "main() @ 1: Virtual member functions must be called with the 'CALLVIRT' instruction.");
	}

	//Test invalid locals
	void testLocals() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/void_local")), "main() @ 0: Locals of 'Void' type are not allowed.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/untyped_local2")), "main() @ 0: Local 0 is not typed.");
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/untyped_local1")), "main() @ 0: Cannot load untyped local (0).");
	}

	//Tests branches
	void testBranch() {
		TS_ASSERT_EQUALS(stripErrorMessage(invokeVM("invalid/branch_target")), "main() @ 0: Invalid jump target (4).");
	}
};