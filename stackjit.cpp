#include <iostream>
#include <vector>
#include <string.h>
#include <sys/mman.h>

#include "stackjit.h"
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

    //Execute the program
    if (ENABLE_DEBUG) {
        std::cout << "Program output: " << std::endl;
    }

    std::cout << programPtr() << std::endl;

    if (ENABLE_DEBUG) {
        std::cout << std::endl;
        std::cout << "Locals: " << std::endl;

        for (int i = 0; i < NUM_LOCALS; i++) {
            std::cout << i << ": " << vmState.Locals[i] << std::endl;
        }
    }

    for (auto func : program.Functions) {
        delete func.second.Instructions;
    }

    return 0;
}