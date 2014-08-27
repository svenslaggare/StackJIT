#include <iostream>

#include "standardlibrary.h"

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

void addStandardLibrary(std::map<std::string, long>& callTable) {
	callTable["abs"] = (long)(&std_abs);
	callTable["print"] = (long)(&std_print);
	callTable["println"] = (long)(&std_println);
}