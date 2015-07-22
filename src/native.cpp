#include "native.h"
#include "vmstate.h"
#include "typechecker.h"
#include "rtlibrary.h"
#include "function.h"
#include <iostream>
#include <math.h>

extern VMState vmState;

void NativeLibrary::print(int x) {
	std::cout << x;
}

void NativeLibrary::print(float x) {
	std::cout << x;
}

void NativeLibrary::println(int x) {
	std::cout << x << std::endl;
}

void NativeLibrary::println(float x) {
	std::cout << x << std::endl;
}

void NativeLibrary::printchar(char x) {
	std::cout << x;
}

int NativeLibrary::abs(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
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

void NativeLibrary::add(VMState& vmState) {
	auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));
	auto floatType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Float));
	auto charType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
	auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

	auto& binder = vmState.binder();

	//Print
	void(*printInt)(int) = &NativeLibrary::print;
	void(*printFloat)(float) = &NativeLibrary::print;
	void(*printlnInt)(int) = &NativeLibrary::println;
	void(*printlnFloat)(float) = &NativeLibrary::println;

	binder.define(FunctionDefinition("std.print", { intType }, voidType, (long)(printInt)));
	binder.define(FunctionDefinition("std.print", { floatType }, voidType, (long)(printFloat)));
	binder.define(FunctionDefinition("std.println", { intType }, voidType, (long)(printlnInt)));
	binder.define(FunctionDefinition("std.println", { floatType }, voidType, (long)(printlnFloat)));
	binder.define(FunctionDefinition("std.printchar", { charType }, voidType, (long)(&printchar)));

	//Math
	binder.define(FunctionDefinition("std.math.abs", { intType }, intType, (long)(&abs)));
	binder.define(FunctionDefinition("std.math.sqrt", { floatType }, floatType, (long)(&sqrtf)));
	binder.define(FunctionDefinition("std.math.sin", { floatType }, floatType, (long)(&sinf)));
	binder.define(FunctionDefinition("std.math.cos", { floatType }, floatType, (long)(&cosf)));

//	auto pointType = vmState.typeProvider().makeType("Ref.Class.Point");
//	binder.define(FunctionDefinition("rt.println", { pointType }, voidType, (long)(&printPoint)));

	auto charArrayType = vmState.typeProvider().makeType("Ref.Array[Char]");
	binder.define(FunctionDefinition("rt.println", { charArrayType }, voidType, (long)(&printString)));
}