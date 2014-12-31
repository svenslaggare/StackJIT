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

float addFloat(float x, float y) {
	std::cout << "x: " << x << " y: " << y << std::endl;
	return x + y;
}

float printFloat(float x) {
	std::cout << x << std::endl;
	return x;
}

void StandardLibrary::add(VMState& vmState) {
	auto intType = vmState.findType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer));
	auto floatType = vmState.findType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Float));
	auto voidType = vmState.findType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Void));

	vmState.functionTable["abs"] = FunctionDefinition({ intType }, intType, (long)(&abs));
	vmState.functionTable["print"] = FunctionDefinition({ intType }, voidType, (long)(&print));
	vmState.functionTable["println"] = FunctionDefinition({ intType }, voidType, (long)(&println));
	vmState.functionTable["printfln"] = FunctionDefinition({ floatType }, voidType, (long)(&printfln));
	vmState.functionTable["printchar"] = FunctionDefinition({ intType }, voidType, (long)(&printchar));

	vmState.functionTable["addFloat"] = FunctionDefinition({ floatType, floatType }, floatType, (long)(&addFloat));
	vmState.functionTable["printFloat"] = FunctionDefinition({ floatType }, floatType, (long)(&printFloat));
}