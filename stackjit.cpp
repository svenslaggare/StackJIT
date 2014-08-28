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

VMState vmState;

int main(int argc, char* argv[]) {
    Program program;

    addStandardLibrary(vmState);

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

    //Free objects
    for (auto obj : vmState.Objects) {
        if (ENABLE_DEBUG) {
            std::cout << "Freed object at 0x" << std::hex << (long)obj << std::endl;
        }
        delete[] obj;
    }

    //Unmapped func memory
    for (auto funcEntry : vmState.FunctionTable) {
        auto func = funcEntry.second;

        //Defined function have size > 0
        if (func.FunctionSize > 0) {
            munmap((unsigned char*)func.EntryPoint, func.FunctionSize);
        }
    }

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

long rt_newArray(int size) {
    unsigned char* arrayPtr = new unsigned char[(size + 1) * sizeof(int)] { 0 };

    //Add the array to the list of objects
    vmState.Objects.push_back(arrayPtr);

    //Set the size of the array
    IntToBytes converter;
    converter.IntValue = size;
    arrayPtr[0] = converter.ByteValues[0];
    arrayPtr[1] = converter.ByteValues[1];
    arrayPtr[2] = converter.ByteValues[2];
    arrayPtr[3] = converter.ByteValues[3];

    return (long)arrayPtr;
}

void rt_runtimeError(std::string errorMessage) {
    throw std::runtime_error(errorMessage);
}

void rt_arrayOutOfBoundsError() {
    rt_runtimeError("Array index is out of bounds.");
}