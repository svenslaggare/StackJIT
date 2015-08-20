#include <iostream>
#include "test.h"
#include "vmstate.h"
#include "rtlibrary.h"

extern VMState vmState;

int fibonacci(int n) {
	if (n <= 1) {
		return n;
	} else {
		return fibonacci(n - 2) + fibonacci(n - 1);
	}
}

void printPoint(RawClassRef objRef) {
	if (objRef != nullptr) {
		//Obtain a reference to the structure
		auto pointRef = vmState.gc().getClassRef(objRef);

		auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));

		auto xField = pointRef.getField<int>("x", intType);
		auto yField = pointRef.getField<int>("y", intType);

		std::cout << *xField.value() << ":" << *yField.value() << std::endl;
	} else {
		Runtime::nullReferenceError();
	}
}

void printString(RawArrayRef objRef) {
	if (objRef != nullptr) {
		//Obtain a reference to the array
		auto arrayRef = vmState.gc().getArrayRef<char>(objRef);

		for (int i = 0; i < arrayRef.length(); i++) {
			auto elementRef = arrayRef.getElement(i);
			std::cout << *elementRef.value();
		}

		std::cout << std::endl;
	} else {
		Runtime::nullReferenceError();
	}
}

void TestLibrary::add(VMState& vmState) {
	auto& binder = vmState.binder();
	auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));
	auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

	binder.define(FunctionDefinition("rt.test.fib", { intType }, intType, (unsigned char*)(&fibonacci)));

	auto pointType = vmState.typeProvider().makeType("Ref.Class.Point");
	if (pointType != nullptr) {
		binder.define(FunctionDefinition("rt.test.println", { pointType }, voidType, (unsigned char*)(&printPoint)));
	}

	auto charArrayType = vmState.typeProvider().makeType("Ref.Array[Char]");
	binder.define(FunctionDefinition("rt.test.println", { charArrayType }, voidType, (unsigned char*)(&printString)));
}