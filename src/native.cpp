#include "native.h"
#include "vmstate.h"
#include "typechecker.h"
#include "type.h"

#include <iostream>
#include <math.h> 

void NativeLibrary::print(int x) {
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

void NativeLibrary::add(VMState& vmState) {
	auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));
	auto floatType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Float));
	auto charType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
	auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

	auto& binder = vmState.binder();

	//Print
	void(*printlnInt)(int) = &println;
	void(*printlnFloat)(float) = &println;

	binder.define(FunctionDefinition("std.print", { intType }, voidType, (long)(&print)));
	binder.define(FunctionDefinition("std.println", { intType }, voidType, (long)(printlnInt)));
	binder.define(FunctionDefinition("std.println", { floatType }, voidType, (long)(printlnFloat)));
	binder.define(FunctionDefinition("std.printchar", { charType }, voidType, (long)(&printchar)));

	//Math
	binder.define(FunctionDefinition("std.math.abs", { intType }, intType, (long)(&NativeLibrary::abs)));
	binder.define(FunctionDefinition("std.math.sqrt", { floatType }, floatType, (long)(&sqrtf)));
	binder.define(FunctionDefinition("std.math.sin", { floatType }, floatType, (long)(&sinf)));
	binder.define(FunctionDefinition("std.math.cos", { floatType }, floatType, (long)(&cosf)));
}