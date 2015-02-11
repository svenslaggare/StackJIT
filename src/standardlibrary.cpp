#include "standardlibrary.h"
#include "vmstate.h"
#include "typechecker.h"
#include "type.h"

#include <iostream>
#include <math.h> 

void StandardLibrary::print(int x) {
	std::cout << x;
}

void StandardLibrary::println(int x) {
	std::cout << x << std::endl;
}

void StandardLibrary::println(float x) {
	std::cout << x << std::endl;
}

void StandardLibrary::printchar(char x) {
	std::cout << x;
}

int StandardLibrary::abs(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

void StandardLibrary::add(VMState& vmState) {
	auto intType = vmState.findType(TypeSystem::toString(PrimitiveTypes::Integer));
	auto floatType = vmState.findType(TypeSystem::toString(PrimitiveTypes::Float));
	auto charType = vmState.findType(TypeSystem::toString(PrimitiveTypes::Char));
	auto voidType = vmState.findType(TypeSystem::toString(PrimitiveTypes::Void));

	auto& binder = vmState.binder();

	//Print
	void(*printlnInt)(int) = &println;
	void(*printlnFloat)(float) = &println;

	binder.define(FunctionDefinition("print", { intType }, voidType, (long)(&print)));
	binder.define(FunctionDefinition("println", { intType }, voidType, (long)(printlnInt)));
	binder.define(FunctionDefinition("println", { floatType }, voidType, (long)(printlnFloat)));
	binder.define(FunctionDefinition("printchar", { charType }, voidType, (long)(&printchar)));

	//Math
	binder.define(FunctionDefinition("abs", { intType }, intType, (long)(&StandardLibrary::abs)));
	binder.define(FunctionDefinition("sqrt", { floatType }, floatType, (long)(&sqrtf)));
	binder.define(FunctionDefinition("sin", { floatType }, floatType, (long)(&sinf)));
	binder.define(FunctionDefinition("cos", { floatType }, floatType, (long)(&cosf)));
}