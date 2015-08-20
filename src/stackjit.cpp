#include "loader.h"
#include "vmstate.h"
#include "executionengine.h"
#include <iostream>
#include <fstream>
#include <chrono>

#if defined(_WIN64) || defined(__MINGW32__)
#include <Windows.h>
#else
#include <unistd.h>
#endif

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
			vmState.printFunctionGeneration = true;
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

		if (switchStr == "-nrl" || switchStr == "--no-rtlib") {
			vmState.loadRuntimeLibrary = false;
			continue;
		}

		if (switchStr == "-t" || switchStr == "--test") {
			vmState.testMode = true;
			continue;
		}

		if (switchStr == "-i") {
			int next = i + 1;

			if (next < argc) {
				//Load the library
				engine.loadLibrary(argv[next]);
				i++;
			} else {
				std::cout << "Expected a library file after '-i' option." << std::endl;
			}

			continue;
		}

		std::cout << "Unhandled option: " << switchStr << std::endl;
	}
}

//Returns the duration since the given time point
std::int64_t getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> timePoint) {
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - timePoint).count();
}

std::string getExecutableDir() {
	const int bufferSize = 1024;

#if defined(_WIN64) || defined(__MINGW32__)
	char buffer[MAX_PATH];
	int bytes = GetModuleFileNameA(nullptr, buffer, MAX_PATH);

	//To remove the name
	buffer[bytes - 12] = '\0';

	return std::string(buffer);
#else
        char buffer[bufferSize];
	char szTmp[32];
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = std::min((int)readlink(szTmp, buffer, bufferSize), bufferSize - 1);

	if (bytes >= 0) {
		buffer[bytes] = '\0';
	}

	//To remove the name
	buffer[bytes - 8] = '\0';

	return std::string(buffer);
#endif
}

int main(int argc, char* argv[]) {
	try {
		auto start = std::chrono::high_resolution_clock::now();
		auto& engine = vmState.engine();

		engine.setBaseDir(getExecutableDir());

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
