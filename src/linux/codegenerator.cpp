#ifdef __unix__
#include "../compiler/x64/oscodegenerator.h"
#include "../compiler/x64/amd64assembler.h"
#include "callingconvention.h"
#include "../helpers.h"
#include "../runtime/runtime.h"

namespace stackjit {
	std::size_t OSCodeGenerator::generateCompileCall(const CallingConvention& callingConvention,
													 Amd64Assembler& assembler,
													 ManagedFunction& function,
													 const FunctionDefinition& funcToCall) {
		std::size_t callIndex;
		std::size_t checkEndIndex;

		assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)&function);  //The current function
		assembler.moveInt(RegisterCallArguments::Arg1, 0); //Offset of the call
		callIndex = assembler.data().size() - sizeof(int);
		assembler.moveInt(RegisterCallArguments::Arg2, (int)assembler.data().size()); //The offset for this check
		assembler.moveInt(RegisterCallArguments::Arg3, 0); //The end of the this check
		checkEndIndex = assembler.data().size() - sizeof(int);
		assembler.moveLong(RegisterCallArguments::Arg4,	(PtrValue)(&funcToCall)); //The function to compile

		assembler.moveLong(Registers::AX, (PtrValue)&Runtime::compileFunction);
		assembler.call(Registers::AX);

		Helpers::setValue(assembler.data(), checkEndIndex, (int)assembler.data().size());
		return callIndex;
	}
}
#endif