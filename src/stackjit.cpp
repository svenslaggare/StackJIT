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

void handleOptions(int argc, char* argv[], ExecutionEngine& engine) {
	for (int i = 1; i < argc; i++) {
		std::string switchStr = argv[i];

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

				auto lib = new AssemblyParser::Assembly;
				Loader::load(fileStream, vmState, *lib);
				engine.loadAssembly(*lib, AssemblyType::Library);
				i++;
			} else {
				std::cout << "Expected a library file after '-i' option." << std::endl;
			}

			continue;
		}

		std::cout << "Unhandled option: " << switchStr << std::endl;
	}
}

int main(int argc, char* argv[]) {
    auto& engine = vmState.engine();
    NativeLibrary::add(vmState);

    //Handle options
	handleOptions(argc, argv, engine);

    //Load the program
	auto program = new AssemblyParser::Assembly;
    Loader::load(std::cin, vmState, *program);
    engine.loadAssembly(*program, AssemblyType::Program);

    if (vmState.enableDebug) {
        std::cout << "Program output:" << std::endl;
    }

	//Compile all functions to native code
	engine.compile();

    //Execute the program
	auto programPtr = engine.entryPoint();

	auto start = std::chrono::high_resolution_clock::now();
    int res = programPtr();

    if (vmState.enableDebug) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Return value (executed for " << duration << " ms): " << std::endl;
    }

    std::cout << res << std::endl;

    return 0;
}
