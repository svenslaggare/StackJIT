#include <iostream>

#include "standardlibrary.h"
#include "stackjit.h"
#include "typechecker.h"
#include "type.h"

int std_abs(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

void std_print(int x) {
	std::cout << x;
}

void std_println(int x) {
	std::cout << x << std::endl;
}

void addStandardLibrary(VMState& vmState) {
	auto intType = vmState.getType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Integer));
	auto voidType = vmState.getType(TypeSystem::getPrimitiveTypeName(PrimitiveTypes::Void));

	vmState.FunctionTable["abs"] = FunctionDefinition({ intType }, intType, (long)(&std_abs));
	vmState.FunctionTable["print"] = FunctionDefinition({ intType }, voidType, (long)(&std_print));
	vmState.FunctionTable["println"] = FunctionDefinition({ intType }, voidType, (long)(&std_println));
}