#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

#include "assembly.h"
#include "parser.h"
#include "native.h"
#include "vmstate.h"
#include "executionengine.h"

//The global state for the VM
VMState vmState;

int main(int argc, char* argv[]) {
    std::vector<Assembly> libraries;
    auto& engine = vmState.engine();
    NativeLibrary::add(vmState);

    //Options
    for (int i = 1; i < argc; i++) {
        std::string switchStr = argv[i];
        bool handled = false;

        if (switchStr == "-d" || switchStr == "--debug") {
            vmState.enableDebug = true;
            continue;
        }

        if (switchStr == "-nd" || switchStr == "--no-debug") {
            vmState.enableDebug = false;
            continue;
        }

        if (switchStr == "-ptc" || switchStr == "--print-type-checking") {
            vmState.printTypeChecking = true;
            continue;
        }

        if (switchStr == "-psf" || switchStr == "--print-stack-frame") {
            vmState.printStackFrame = true;
            continue;
        }

        if (switchStr == "-ogc" || switchStr == "--output-generated-code") {
            vmState.outputGeneratedCode = true;
            continue;
        }

        if (switchStr == "-ngc" || switchStr == "--no-gc") {
            vmState.disableGC = true;
            continue;
        }

        if (switchStr == "-i") {
            int next = i + 1;

            if (next < argc) {
                //Load the library
                std::string libraryPath = argv[next];
                std::ifstream fileStream(libraryPath);

                if (!fileStream.is_open()) {
                    std::cout << "Could not load library '" << libraryPath << "'." << std::endl;
                }

                auto tokens = Parser::tokenize(fileStream);
                libraries.emplace_back(AssemblyType::LIBRARY);
                auto& lib = libraries[libraries.size() - 1];

                Parser::parseTokens(tokens, vmState, lib);
                engine.loadAssembly(lib);
                i++;
            } else {
                std::cout << "Expected a path after '-i' option." << std::endl;
            }

            continue;
        }

        if (!handled) {
            std::cout << "Unhandled option: " << switchStr << std::endl;
        }
    }

    //Tokenize the input
    auto tokens = Parser::tokenize(std::cin);
    // std::ifstream fileStream("programs/program21.txt");
    // auto tokens = Parser::tokenize(fileStream);

    //Parse it
    Assembly program(AssemblyType::PROGRAM);
    Parser::parseTokens(tokens, vmState, program);

    //Generate a function for the instructions
    engine.loadAssembly(program);
    auto programPtr = engine.entryPoint();

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
