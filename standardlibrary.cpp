#include "standardlibrary.h"
#include <iostream>

int vm_abs(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

int vm_print(int x) {
	std::cout << x;
	return 0;
}

int vm_println(int x) {
	std::cout << x << std::endl;
	return 0;
}

void addStandardLibrary(std::map<std::string, long>& callTable) {
	callTable["abs"] = (long)(&vm_abs);
	callTable["print"] = (long)(&vm_print);
	callTable["println"] = (long)(&vm_println);
}