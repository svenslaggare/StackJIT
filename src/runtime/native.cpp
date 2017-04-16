#include "native.h"
#include "../vmstate.h"
#include "runtime.h"
#include "../core/function.h"
#include "native/stringref.h"
#include <iostream>
#include <math.h>
#include <string.h>

namespace stackjit {
	void NativeLibrary::print(int x) {
		Runtime::standardOutputStream() << x;
	}

	void NativeLibrary::print(float x) {
		Runtime::standardOutputStream() << x;
	}

	void NativeLibrary::print(bool x) {
		if (x) {
			Runtime::standardOutputStream() << "true";
		} else {
			Runtime::standardOutputStream() << "false";
		}
	}

	void NativeLibrary::print(char x) {
		Runtime::standardOutputStream() << x;
	}

	void NativeLibrary::println(int x) {
		Runtime::standardOutputStream() << x << std::endl;
	}

	void NativeLibrary::println(float x) {
		Runtime::standardOutputStream() << x << std::endl;
	}

	void NativeLibrary::println(bool x) {
		print(x);
		Runtime::standardOutputStream() << std::endl;
	}

	void NativeLibrary::println(char x) {
		Runtime::standardOutputStream() << x << std::endl;
	}

	void NativeLibrary::println(RawArrayRef rawArrayRef) {
		if (rawArrayRef != nullptr) {
			ArrayRef<char> arrayRef(rawArrayRef);
			for (int i = 0; i < arrayRef.length(); i++) {
				Runtime::standardOutputStream() << arrayRef.getElement(i);
			}

			Runtime::standardOutputStream() << std::endl;
		} else {
			Runtime::nullReferenceError();
		}
	}

	int NativeLibrary::abs(int x) {
	    if (x < 0) {
	        return -x;
	    } else {
	        return x;
	    }
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
		auto charArrayType = vmState.typeProvider().makeType(TypeSystem::arrayTypeName(charType));

		auto& binder = vmState.binder();

		//IO
		void(*printInt)(int) = &NativeLibrary::print;
		void(*printFloat)(float) = &NativeLibrary::print;
		void(*printBool)(bool) = &NativeLibrary::print;
		void(*printChar)(char) = &NativeLibrary::print;

		void(*printlnInt)(int) = &NativeLibrary::println;
		void(*printlnFloat)(float) = &NativeLibrary::println;
		void(*printlnBool)(bool) = &NativeLibrary::println;
		void(*printlnChar)(char) = &NativeLibrary::println;
		void(*printlnCharArray)(RawArrayRef) = &NativeLibrary::println;

		binder.define(FunctionDefinition("std.print", { intType }, voidType, (BytePtr)(printInt)));
		binder.define(FunctionDefinition("std.print", { floatType }, voidType, (BytePtr)(printFloat)));
		binder.define(FunctionDefinition("std.print", { boolType }, voidType, (BytePtr)(printBool)));
		binder.define(FunctionDefinition("std.print", { charType }, voidType, (BytePtr)(printChar)));

		binder.define(FunctionDefinition("std.println", { intType }, voidType, (BytePtr)(printlnInt)));
		binder.define(FunctionDefinition("std.println", { floatType }, voidType, (BytePtr)(printlnFloat)));
		binder.define(FunctionDefinition("std.println", { boolType }, voidType, (BytePtr)(printlnBool)));
		binder.define(FunctionDefinition("std.println", { charType }, voidType, (BytePtr)(printlnChar)));
		binder.define(FunctionDefinition("std.println", { charArrayType }, voidType, (BytePtr)(printlnCharArray)));

		//Math
		binder.define(FunctionDefinition("std.math.abs", { intType }, intType, (BytePtr)(&abs)));
		binder.define(FunctionDefinition("std.math.sqrt", { floatType }, floatType, (BytePtr)(&sqrtf)));
		binder.define(FunctionDefinition("std.math.sin", { floatType }, floatType, (BytePtr)(&sinf)));
		binder.define(FunctionDefinition("std.math.cos", { floatType }, floatType, (BytePtr)(&cosf)));

		//String
		auto stringType = vmState.typeProvider().makeType(TypeSystem::stringTypeName);
		if (stringType != nullptr) {
			StringRef::initialize(vmState);
			binder.define(FunctionDefinition("std.equals", { stringType, stringType }, boolType, (BytePtr)(&stringEquals)));
		}
	}
}
