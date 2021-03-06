#pragma once
#ifdef __unix__
#include "../compiler/x64/amd64.h"

namespace stackjit {
	//The register for function arguments
	namespace RegisterCallArguments {
		const Registers Arg0 = Registers::DI;
		const Registers Arg1 = Registers::SI;
		const Registers Arg2 = Registers::DX;
		const Registers Arg3 = Registers::CX;
		const ExtendedRegisters Arg4 = ExtendedRegisters::R8;
		const ExtendedRegisters Arg5 = ExtendedRegisters::R9;

		const Registers ReturnValue = Registers::AX;
	}

	namespace FloatRegisterCallArguments {
		const FloatRegisters Arg0 = FloatRegisters::XMM0;
		const FloatRegisters Arg1 = FloatRegisters::XMM1;
		const FloatRegisters Arg2 = FloatRegisters::XMM2;
		const FloatRegisters Arg3 = FloatRegisters::XMM3;
		const FloatRegisters Arg4 = FloatRegisters::XMM4;
		const FloatRegisters Arg5 = FloatRegisters::XMM5;
		const FloatRegisters Arg6 = FloatRegisters::XMM6;
		const FloatRegisters Arg7 = FloatRegisters::XMM7;

		const FloatRegisters ReturnValue = FloatRegisters::XMM0;
	}
}
#endif
