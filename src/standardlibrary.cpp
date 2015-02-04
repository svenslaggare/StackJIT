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

void StandardLibrary::printfln(float x) {
	std::cout << x << std::endl;
}

void StandardLibrary::printchar(int x) {
	std::cout << (char)x;
}

void StandardLibrary::add(VMState& vmState) {
	auto intType = vmState.findType(TypeSystem::primitiveTypeName(PrimitiveTypes::Integer));
	auto floatType = vmState.findType(TypeSystem::primitiveTypeName(PrimitiveTypes::Float));
	auto voidType = vmState.findType(TypeSystem::primitiveTypeName(PrimitiveTypes::Void));

	auto& binder = vmState.binder();
	binder.define(FunctionDefinition("abs", { intType }, intType, (long)(&abs)));
	binder.define(FunctionDefinition("print", { intType }, voidType, (long)(&print)));
	binder.define(FunctionDefinition("println", { intType }, voidType, (long)(&println)));
	binder.define(FunctionDefinition("println", { floatType }, voidType, (long)(&printfln)));
	binder.define(FunctionDefinition("printchar", { intType }, voidType, (long)(&printchar)));

	// vmState.functionTable["abs"] = FunctionDefinition("abs", { intType }, intType, (long)(&abs));
	// vmState.functionTable["print"] = FunctionDefinition("print", { intType }, voidType, (long)(&print));
	// vmState.functionTable["println"] = FunctionDefinition("println", { intType }, voidType, (long)(&println));
	// vmState.functionTable["printfln"] = FunctionDefinition("printfln", { floatType }, voidType, (long)(&printfln));
	// vmState.functionTable["printchar"] = FunctionDefinition("printchar", { intType }, voidType, (long)(&printchar));
}