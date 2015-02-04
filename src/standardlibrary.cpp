#include <iostream>

#include "standardlibrary.h"
#include "vmstate.h"
#include "typechecker.h"
#include "type.h"

int StandardLibrary::abs(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

void StandardLibrary::print(int x) {
	std::cout << x;
}

void StandardLibrary::println(int x) {
	std::cout << x << std::endl;
}

void StandardLibrary::println(float x) {
	std::cout << x << std::endl;
}

void StandardLibrary::printchar(int x) {
	std::cout << (char)x;
}

void StandardLibrary::add(VMState& vmState) {
	auto intType = vmState.findType(TypeSystem::primitiveTypeName(PrimitiveTypes::Integer));
	auto floatType = vmState.findType(TypeSystem::primitiveTypeName(PrimitiveTypes::Float));
	auto voidType = vmState.findType(TypeSystem::primitiveTypeName(PrimitiveTypes::Void));

	void(*printlnInt)(int) = &println;
	void(*printlnFloat)(float) = &println;

	auto& binder = vmState.binder();
	binder.define(FunctionDefinition("abs", { intType }, intType, (long)(&abs)));
	binder.define(FunctionDefinition("print", { intType }, voidType, (long)(&print)));
	binder.define(FunctionDefinition("println", { intType }, voidType, (long)(printlnInt)));
	binder.define(FunctionDefinition("println", { floatType }, voidType, (long)(printlnFloat)));
	binder.define(FunctionDefinition("printchar", { intType }, voidType, (long)(&printchar)));
}