#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

#include "amd64.h"
#include "program.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "codegenerator.h"
#include "vmstate.h"
#include "objects.h"

//The global state for the VM
VMState vmState;

int main(int argc, char* argv[]) {
    Program program;

    //Options
    for (int i = 1; i < argc; i++) {
        std::string switchStr = argv[i];
        bool handled = false;

        if (switchStr == "-d" || switchStr == "-debug") {
            vmState.enableDebug = true;
            handled = true;
        }

        if (switchStr == "-nd") {
            vmState.enableDebug = false;
            handled = true;
        }

        if (switchStr == "-ptc") {
            vmState.printTypeChecking = true;
            handled = true;
        }

        if (switchStr == "-psf") {
            vmState.printStackFrame = true;
            handled = true;
        }

        if (switchStr == "-ogc") {
            vmState.outputGeneratedCode = true;
            handled = true;
        }

        if (switchStr == "-nogc") {
            vmState.disableGC = true;
            handled = true;
        }

        if (!handled) {
            std::cout << "Unhandled option: " << switchStr << std::endl;
        }
    }

    StandardLibrary::add(vmState);

    //Tokenize the input
    auto tokens = Parser::tokenize(std::cin);
    // std::ifstream fileStream("programs/program21.txt");
    // auto tokens = Parser::tokenize(fileStream);

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

    return 0;
}