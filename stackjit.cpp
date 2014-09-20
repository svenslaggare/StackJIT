#include <iostream>
#include <vector>
#include <string.h>
#include <sys/mman.h>

#include "amd64.h"
#include "stackjit.h"
#include "program.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "codegenerator.h"
#include "objects.h"
#include "type.h"
#include "vmstate.h"

//The global state for the VM
VMState vmState;

int main(int argc, char* argv[]) {
    Program program;

    addStandardLibrary(vmState);

    //Tokenize the input
    auto tokens = Parser::tokenize(std::cin);

    //Parse it
    Parser::parseTokens(tokens, vmState, program);

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

    //Free objects
    for (auto obj : vmState.Objects) {
        if (ENABLE_DEBUG) {
            std::cout << "Freed object at 0x" << std::hex << (long)(obj.getHandle()) << std::dec << std::endl;
        }

        obj.deleteHandle();
    }

    //Unmap function code memory
    for (auto funcEntry : vmState.FunctionTable) {
        auto func = funcEntry.second;

        //Defined function have size > 0
        if (func.functionSize() > 0) {
            munmap((unsigned char*)func.entryPoint(), func.functionSize());
        }
    }

    return 0;
}