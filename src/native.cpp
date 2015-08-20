#include "native.h"
#include "vmstate.h"
#include "verifier.h"
#include "rtlibrary.h"
#include "function.h"
#include <iostream>
#include <math.h>
#include <string.h>

extern VMState vmState;

void NativeLibrary::print(int x) {
	std::cout << x;
}

void NativeLibrary::print(float x) {
	std::cout << x;
}

void NativeLibrary::print(bool x) {
	if (x) {
		std::cout << "true";
	} else {
		std::cout << "false";
	}
}


void NativeLibrary::println(int x) {
	std::cout << x << std::endl;
}

void NativeLibrary::println(float x) {
	std::cout << x << std::endl;
}

void NativeLibrary::println(bool x) {
	print(x);
	std::cout << std::endl;
}

void NativeLibrary::println(char x) {
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

StringRef::StringRef(RawClassRef stringRef) {
	auto charsField = (char**)(stringRef + sCharsFieldOffset);
	ArrayRef<char> charsArray((unsigned char*)(*charsField));
	mChars = charsArray.elementsPtr();
	mLength = charsArray.length();
}

//Returns the char at the given index
char StringRef::charAt(int index) {
	return mChars[index];
}

//Returns the length of the string
int StringRef::length() const {
	return mLength;
}

std::size_t StringRef::sCharsFieldOffset;

void StringRef::initialize(VMState& vmState) {
	auto& classMetadata = vmState.classProvider().getMetadata("std.String");
	sCharsFieldOffset = classMetadata.fields().at("chars").offset();
}

bool NativeLibrary::stringEquals(RawClassRef str1, RawClassRef str2) {
	if (str1 == nullptr || str2 == nullptr) {
		return false;
	}

	if (str1 == str2) {
		return true;
	}

	//Get references to the instances
	StringRef str1Ref(str1);
	StringRef str2Ref(str2);

	if (str1Ref.length() != str2Ref.length()) {
		return false;
	}

	for (int i = 0; i < str1Ref.length(); i++) {
		if (str1Ref.charAt(i) != str2Ref.charAt(i)) {
			return false;
		}
	}

	return true;
}

void NativeLibrary::add(VMState& vmState) {
	auto intType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Integer));
	auto floatType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Float));
	auto charType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
	auto boolType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Bool));
	auto voidType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Void));

	auto& binder = vmState.binder();

	//Print
	void(*printInt)(int) = &NativeLibrary::print;
	void(*printFloat)(float) = &NativeLibrary::print;
	void(*printBool)(bool) = &NativeLibrary::print;

	void(*printlnInt)(int) = &NativeLibrary::println;
	void(*printlnFloat)(float) = &NativeLibrary::println;
	void(*printlnBool)(bool) = &NativeLibrary::println;
	void(*printlnChar)(char) = &NativeLibrary::println;

	//IO
	binder.define(FunctionDefinition("std.print", { intType }, voidType, (unsigned char*)(printInt)));
	binder.define(FunctionDefinition("std.print", { floatType }, voidType, (unsigned char*)(printFloat)));
	binder.define(FunctionDefinition("std.print", { boolType }, voidType, (unsigned char*)(printBool)));

	binder.define(FunctionDefinition("std.println", { intType }, voidType, (unsigned char*)(printlnInt)));
	binder.define(FunctionDefinition("std.println", { floatType }, voidType, (unsigned char*)(printlnFloat)));
	binder.define(FunctionDefinition("std.println", { boolType }, voidType, (unsigned char*)(printlnBool)));
	binder.define(FunctionDefinition("std.println", { charType }, voidType, (unsigned char*)(printlnChar)));

	binder.define(FunctionDefinition("std.printchar", { charType }, voidType, (unsigned char*)(&printchar)));

	//Math
	binder.define(FunctionDefinition("std.math.abs", { intType }, intType, (unsigned char*)(&abs)));
	binder.define(FunctionDefinition("std.math.sqrt", { floatType }, floatType, (unsigned char*)(&sqrtf)));
	binder.define(FunctionDefinition("std.math.sin", { floatType }, floatType, (unsigned char*)(&sinf)));
	binder.define(FunctionDefinition("std.math.cos", { floatType }, floatType, (unsigned char*)(&cosf)));

	//String
	auto stringType = vmState.typeProvider().makeType("Ref.Class.std.String");
	if (stringType != nullptr) {
		StringRef::initialize(vmState);
		binder.define(FunctionDefinition("std.equals", { stringType, stringType }, boolType, (unsigned char*)(&stringEquals)));
	}
}