#pragma once
#ifdef __unix__
#include "../amd64.h"

//The register for function arguments
namespace RegisterCallArguments {
	const Registers Arg0 = Registers::DI;
	const Registers Arg1 = Registers::SI;
	const Registers Arg2 = Registers::DX;
	const Registers Arg3 = Registers::CX;
	const NumberedRegisters Arg4 = NumberedRegisters::R8;
	const NumberedRegisters Arg5 = NumberedRegisters::R9;
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
}
#endif