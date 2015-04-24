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

	binder.define(FunctionDefinition("rt.print", { intType }, voidType, (long)(&print)));
	binder.define(FunctionDefinition("rt.println", { intType }, voidType, (long)(printlnInt)));
	binder.define(FunctionDefinition("rt.println", { floatType }, voidType, (long)(printlnFloat)));
	binder.define(FunctionDefinition("rt.printchar", { charType }, voidType, (long)(&printchar)));

	//Math
	binder.define(FunctionDefinition("rt.abs", { intType }, intType, (long)(&NativeLibrary::abs)));
	binder.define(FunctionDefinition("rt.sqrt", { floatType }, floatType, (long)(&sqrtf)));
	binder.define(FunctionDefinition("rt.sin", { floatType }, floatType, (long)(&sinf)));
	binder.define(FunctionDefinition("rt.cos", { floatType }, floatType, (long)(&cosf)));
}