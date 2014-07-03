#include <iostream>
#include <vector>
#include <string.h>
#include <sys/mman.h>

#include "stackjit.h"
#include "instructions.h"
#include "parser.h"
#include "standardlibrary.h"
#include "codegenerator.h"

bool enableDebug = true;

int main(int argc, char* argv[]) {
    std::vector<Instruction> input;
    std::vector<unsigned char> generatedCode;

    VMState vmState;
    addStandardLibrary(vmState.CallTable);

    //Tokenize the input
    auto tokens = tokenizeInput();

    //Parse it
    parseTokens(tokens, vmState.CallTable, input);

    //Generate a function for the instructions
    int (*program)() = generateFunction(input, vmState);

    //Execute the program
    if (enableDebug) {
        std::cout << "Program output: " << std::endl;
    }

    std::cout << program() << std::endl;

    if (enableDebug) {
        std::cout << std::endl;
        std::cout << "Locals: " << std::endl;

        for (int i = 0; i < NUM_LOCALS; i++) {
            std::cout << i << ": " << vmState.Locals[i] << std::endl;
        }
    }

    return 0;
}