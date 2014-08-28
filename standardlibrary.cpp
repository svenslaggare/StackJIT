#include <iostream>

#include "standardlibrary.h"
#include "stackjit.h"

int std_abs(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

int std_print(int x) {
	std::cout << x;
	return x;
}

int std_println(int x) {
	std::cout << x << std::endl;
	return x;
}

void addStandardLibrary(VMState& vmState) {
	vmState.FunctionTable["abs"] = FunctionDefinition(1, (long)(&std_abs), 0);
	vmState.FunctionTable["print"] = FunctionDefinition(1, (long)(&std_print), 0);
	vmState.FunctionTable["println"] = FunctionDefinition(1, (long)(&std_println), 0);
}