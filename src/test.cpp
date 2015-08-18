#include "test.h"
#include "vmstate.h"

int fibonacci(int n) {
	if (n <= 1) {
		return n;
	} else {
		return fibonacci(n - 2) + fibonacci(n - 1);
	}
}

void TestLibrary::add(VMState& vmState) {
	auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));

	auto& binder = vmState.binder();

	binder.define(FunctionDefinition("rt.test.fib", { intType }, intType, (unsigned char*)(&fibonacci)));
}