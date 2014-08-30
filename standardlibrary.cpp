#include <iostream>

#include "standardlibrary.h"
#include "stackjit.h"
#include "typechecker.h"

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
	vmState.FunctionTable["abs"] = FunctionDefinition({ Types::Int }, Types::Int, (long)(&std_abs));
	vmState.FunctionTable["print"] = FunctionDefinition({ Types::Int }, Types::Void, (long)(&std_print));
	vmState.FunctionTable["println"] = FunctionDefinition({ Types::Int }, Types::Void, (long)(&std_println));
}