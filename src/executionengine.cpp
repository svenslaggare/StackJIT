#include "executionengine.h"
#include "vmstate.h"
#include "binder.h"
#include "assembly.h"
#include "function.h"
#include "typechecker.h"
#include "type.h"

#include <iostream>
#include <stdexcept>

ExecutionEngine::ExecutionEngine(VMState& vmState)
	: mVMState(vmState), mJIT(vmState) {

}

EntryPointFunction ExecutionEngine::entryPoint() const {
    if (mVMState.binder().isDefined("main()") > 0) {
        return (EntryPointFunction)(mVMState.binder()["main()"].entryPoint());
    } else {
        throw std::runtime_error("No entry point has been defined.");
    }
}

void ExecutionEngine::loadAssembly(Assembly& assembly) {
	//Add the functions to the func table
    for (auto currentFunc : assembly.functions) {
        auto func = currentFunc.second;
        FunctionDefinition funcDef(
            func->name(),
            func->arguments(),
            func->returnType(),
            0, 0, func->isMemberFunction());

        auto& binder = mVMState.binder();
        binder.define(funcDef);
    }

    if (assembly.type() == AssemblyType::PROGRAM) {
        if (assembly.functions.count("main()") > 0) {
            auto mainFunc = assembly.functions["main()"];

            if (mainFunc->arguments().size() != 0 || !TypeSystem::isPrimitiveType(mainFunc->returnType(), PrimitiveTypes::Integer)) {
               throw std::runtime_error("The main function must have the following signature: 'main() Int'"); 
            }
        } else {
            throw std::runtime_error("The main function must be defined.");
        }
    }

    //Generate instructions for all functions
    for (auto currentFunc : assembly.functions) {
        auto func = currentFunc.second;

        //Type check the function
        TypeChecker::typeCheckFunction(*func, mVMState, mVMState.enableDebug && mVMState.printTypeChecking);

        auto funcPtr = mJIT.generateFunction(func);

        if (mVMState.enableDebug) {
            std::cout << "Defined function '" << func->name() << "' at 0x" << std::hex << (long)funcPtr << std::dec << "." << std::endl;
        }

        auto signature = mVMState.binder().functionSignature(func->name(), func->arguments());

        //Set the entry point & size for the function
        mVMState.binder().getFunction(signature).setFunctionBody((long)funcPtr, func->generatedCode.size());
    }

    //Fix unresolved calls
    mJIT.resolveCallTargets();
}

void ExecutionEngine::beginExecution() {
    mJIT.makeExecutable();
}