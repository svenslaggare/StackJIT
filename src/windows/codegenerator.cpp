#if defined(_WIN64) || defined(__MINGW32__)
#include "../compiler/oscodegenerator.h"
#include "../compiler/amd64assembler.h"
#include "callingconvention.h"
#include "../helpers.h"
#include "../runtime/runtime.h"

namespace stackjit {
	std::size_t OSCodeGenerator::generateCompileCall(const CallingConvention& callingConvention,
													 Amd64Assembler& assembler,
													 ManagedFunction& function,
													 const FunctionDefinition& funcToCall) {
		char shadowStackSize = (char)callingConvention.calculateShadowStackSize();
		std::size_t callIndex;
		std::size_t checkEndIndex;

		assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)&function); //The current function
		assembler.moveInt(RegisterCallArguments::Arg1, 0); //Offset of the call
		callIndex = assembler.data().size() - sizeof(int);
		assembler.moveInt(RegisterCallArguments::Arg2, (int)assembler.data().size()); //The offset for this check
		assembler.moveInt(RegisterCallArguments::Arg3, 0); //The end of the this check
		checkEndIndex = assembler.data().size() - sizeof(int);

		//The function to compile
		assembler.sub(Registers::SP, 8); //Alignment
		assembler.moveLong(ExtendedRegisters::R10, (PtrValue)(&funcToCall));
		assembler.push(ExtendedRegisters::R10);
		assembler.sub(Registers::SP, shadowStackSize); //Shadow space

		assembler.moveLong(Registers::AX, (PtrValue)&Runtime::compileFunction);
		assembler.call(Registers::AX);
		assembler.add(Registers::SP, 16 + shadowStackSize); //Used stack

		Helpers::setValue(assembler.data(), checkEndIndex, (int)assembler.data().size());
		return callIndex;
	}
}
#endif