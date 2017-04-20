#pragma once
#if defined(_WIN64) || defined(__MINGW32__)
#include "../compiler/x64/amd64.h"

namespace stackjit {
	//The register for function arguments
	namespace RegisterCallArguments {
		const Registers Arg0 = Registers::CX;
		const Registers Arg1 = Registers::DX;
		const ExtendedRegisters Arg2 = ExtendedRegisters::R8;
		const ExtendedRegisters Arg3 = ExtendedRegisters::R9;

		const Registers ReturnValue = Registers::AX;
	}

	namespace FloatRegisterCallArguments {
		const FloatRegisters Arg0 = FloatRegisters::XMM0;
		const FloatRegisters Arg1 = FloatRegisters::XMM1;
		const FloatRegisters Arg2 = FloatRegisters::XMM2;
		const FloatRegisters Arg3 = FloatRegisters::XMM3;

		const FloatRegisters ReturnValue = FloatRegisters::XMM0;
	}
}
#endif
