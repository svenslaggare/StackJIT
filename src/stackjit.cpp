#include "assembly.h"
#include "loader.h"
#include "parser.h"
#include "native.h"
#include "vmstate.h"
#include "executionengine.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <chrono>

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
                
                libraries.emplace_back(AssemblyType::Library);
                auto& lib = libraries[libraries.size() - 1];
                Loader::load(fileStream, vmState, lib);

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

    //Load the program
    Assembly program(AssemblyType::Program);
    Loader::load(std::cin, vmState, program);

    //Generate a function for the instructions
    engine.loadAssembly(program);
    auto programPtr = engine.entryPoint();

    if (vmState.enableDebug) {
        std::cout << "Program output:" << std::endl;
    }

    //Execute the program
    auto start = std::chrono::high_resolution_clock::now();

    engine.beginExecution();
    int res = programPtr();

    if (vmState.enableDebug) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Return value (executed " << duration << " ms): " << std::endl;
    }

    std::cout << res << std::endl;

    return 0;
}
