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
//	auto floatType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Float));
//	auto charType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
//	auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

	auto& binder = vmState.binder();

	binder.define(FunctionDefinition("rt.test.fib", { intType }, intType, (long)(&fibonacci)));
}