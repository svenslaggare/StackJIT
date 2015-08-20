#include "assembly.h"
#include "loader.h"
#include "native.h"
#include "test.h"
#include "vmstate.h"
#include "executionengine.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>

//The global state for the VM
VMState vmState;

//Parses the options
void handleOptions(int argc, char* argv[], ExecutionEngine& engine) {
	for (int i = 1; i < argc; i++) {
		std::string switchStr = argv[i];

		if (switchStr == "-d" || switchStr == "--debug") {
			vmState.enableDebug = true;
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

		if (switchStr == "-pfg" || switchStr == "--print-function-generation") {
			vmState.outputGeneratedCode = true;
			continue;
		}

		if (switchStr == "-plp" || switchStr == "--print-lazy-patching") {
			vmState.printLazyPatching = true;
			continue;
		}

		if (switchStr == "-lc" || switchStr == "--lazy-compile") {
			int next = i + 1;

			if (next < argc) {
				vmState.lazyJIT = std::string(argv[next]) == "1";
				i++;
			} else {
				std::cout << "Expected value after '" << switchStr << "' option." << std::endl;
			}

			continue;
		}

		if (switchStr == "-ngc" || switchStr == "--no-gc") {
			vmState.disableGC = true;
			continue;
		}

		if (switchStr == "-t" || switchStr == "--test") {
			TestLibrary::add(vmState);
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

//Returns the duration since last
std::int64_t getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> start) {
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main(int argc, char* argv[]) {
	try {
		auto start = std::chrono::high_resolution_clock::now();
		auto& engine = vmState.engine();
		NativeLibrary::add(vmState);

		//Handle options
		handleOptions(argc, argv, engine);

		//Load the program
		auto program = new AssemblyParser::Assembly;
		Loader::load(std::cin, vmState, *program);
		engine.loadAssembly(*program, AssemblyType::Program);

		if (!vmState.lazyJIT) {
			//Compile all functions to native code
			engine.compile();
		}
		else {
			//Load definitions
			engine.loadDefinitions();

			//Compile the entry point
			engine.compileFunction("main()");
		}

		//Execute the program
		if (vmState.enableDebug) {
			std::cout << "Load time: " << getDuration(start) << " ms." << std::endl;
			std::cout << "Program output:" << std::endl;
		}

		auto programPtr = engine.entryPoint();

		start = std::chrono::high_resolution_clock::now();
		int res = programPtr();

		if (vmState.enableDebug) {
			std::cout << "Return value (executed for " << getDuration(start) << " ms): " << std::endl;
		}

		std::cout << res << std::endl;
		return 0;
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}
