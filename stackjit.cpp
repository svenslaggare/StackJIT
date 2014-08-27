#include <iostream>
#include <vector>
#include <string.h>
#include <sys/mman.h>

#include "stackjit.h"
#include "program.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "codegenerator.h"

int main(int argc, char* argv[]) {
    VMState vmState;
    Program program;

    addStandardLibrary(vmState.FunctionTable);

    //Tokenize the input
    auto tokens = Parser::tokenize(std::cin);

    //Parse it
    Parser::parseTokens(tokens, program);

    //Generate a function for the instructions
    int (*programPtr)() = CodeGenerator::generateProgram(program, vmState);

    if (ENABLE_DEBUG) {
        std::cout << "Program output:" << std::endl;
    }

    //Execute the program
    int res = programPtr();

    if (ENABLE_DEBUG) {
        std::cout << "Return value: " << std::endl;
    }

    std::cout << res << std::endl;

    return 0;
}

void rt_printStackFrame(long* basePtr, Function* func) {
    int numArgs = func->NumArgs;
    int numLocals = func->NumLocals;

    std::cout << "----Start StackFrame----" << std::endl;
    std::cout << "Func: " << func->Name << std::endl;
    std::cout << "Num args: " << numArgs << std::endl;
    std::cout << "Num locals: " << numLocals << std::endl;

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;

    if (numArgs > 0) {
        std::cout << std::endl;
        std::cout << "Args: " << std::endl;
        for (int i = 0; i < numArgs; i++) {
            std::cout << i << ": " << argsStart[-i] << std::endl;
        }
    }

    std::cout << std::endl;

    std::cout << "Locals: " << std::endl;
    for (int i = 0; i < numLocals; i++) {
        std::cout << i << ": " << localsStart[-i] << std::endl;
    }
    std::cout << "----End StackFrame----" << std::endl;
}