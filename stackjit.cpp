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

    //Generate the code for the program
    for (auto current : input) {
        generateCode(generatedCode, vmState, current);
    }

    generatedCode.push_back(0x58); //pop eax
    generatedCode.push_back(0xc3); //ret

    unsigned char* code = generatedCode.data();
    int length = generatedCode.size();

    // Allocate writable/executable memory.
    // Note: real programs should not map memory both writable
    // and executable because it is a security risk.
    void *mem = mmap(NULL, length, PROT_WRITE | PROT_EXEC,
        MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, code, length);

    //Convert the generated code to a function pointer
    int (*program)() = (int (*)())mem;

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