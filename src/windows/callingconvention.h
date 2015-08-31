#pragma once
#if defined(_WIN64) || defined(__MINGW32__)
#include "../amd64.h"

//The register for function arguments
namespace RegisterCallArguments {
	const Registers Arg0 = Registers::CX;
	const Registers Arg1 = Registers::DX;
	const NumberedRegisters Arg2 = NumberedRegisters::R8;
	const NumberedRegisters Arg3 = NumberedRegisters::R9;
}

namespace FloatRegisterCallArguments {
	const FloatRegisters Arg0 = FloatRegisters::XMM0;
	const FloatRegisters Arg1 = FloatRegisters::XMM1;
	const FloatRegisters Arg2 = FloatRegisters::XMM2;
	const FloatRegisters Arg3 = FloatRegisters::XMM3;
}
#endif
