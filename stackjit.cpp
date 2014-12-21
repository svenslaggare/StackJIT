#include <iostream>
#include <vector>
#include <string.h>
#include <sys/mman.h>

#include "amd64.h"
#include "program.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "codegenerator.h"
#include "vmstate.h"

//The global state for the VM
VMState vmState;

int main(int argc, char* argv[]) {
    Program program;

    for (int i = 1; i < argc; i++) {
        std::string switchStr = argv[i];

        if (switchStr == "-d" || switchStr == "-debug") {
            vmState.enableDebug = true;
        }

        if (switchStr == "-nd") {
            vmState.enableDebug = false;
        }

        if (switchStr == "-ptc") {
            vmState.printTypeChecking = true;
        }

        if (switchStr == "-psf") {
            vmState.printStackFrame = true;
        }

        if (switchStr == "-ogc") {
            vmState.outputGeneratedCode = true;
        }
    }

    addStandardLibrary(vmState);

    //Tokenize the input
    auto tokens = Parser::tokenize(std::cin);

    //Parse it
    Parser::parseTokens(tokens, vmState, program);

    //Generate a function for the instructions
    int (*programPtr)() = CodeGenerator::generateProgram(program, vmState);

    if (vmState.enableDebug) {
        std::cout << "Program output:" << std::endl;
    }

    //Execute the program
    int res = programPtr();

    if (vmState.enableDebug) {
        std::cout << "Return value: " << std::endl;
    }

    std::cout << res << std::endl;

    //Free objects
    for (auto obj : vmState.getObjects()) {
        if (vmState.enableDebug) {
            //std::cout << "Freed object (" << obj->getSize() << " bytes) at 0x" << std::hex << (long)(obj->getHandle()) << std::dec << std::endl;
        }

        obj->deleteHandle();
        delete obj;
    }

    //Unmap function code memory
    for (auto funcEntry : vmState.functionTable) {
        auto func = funcEntry.second;

        //Defined function have size > 0
        if (func.functionSize() > 0) {
            munmap((unsigned char*)func.entryPoint(), func.functionSize());
        }
    }

    return 0;
}