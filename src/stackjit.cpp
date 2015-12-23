#include "loader.h"
#include "vmstate.h"
#include "executionengine.h"
#include "helpers.h"
#include "rtlibrary.h"
#include <iostream>
#include <fstream>
#include <chrono>

#if defined(_WIN64) || defined(__MINGW32__)
#include <Windows.h>
#else
#include <unistd.h>
#endif

//Parses the options
std::string handleOptions(int argc, char* argv[], ExecutionEngine& engine) {
	std::string program = "";
	auto& vmState = Runtime::vmState;

	for (int i = 1; i < argc; i++) {
		std::string switchStr = argv[i];

		if (switchStr == "-d" || switchStr == "--debug") {
			vmState.enableDebug = true;
			continue;
		}

		if (switchStr == "-ogc" || switchStr == "--output-generated-code") {
			vmState.outputGeneratedCode = true;
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

		if (switchStr == "-im" || switchStr == "--image-mode") {
			vmState.imageMode = true;
			continue;
		}

		if (switchStr == "--allocs-before-gc") {
			int next = i + 1;

			if (next < argc) {
				vmState.allocationsBeforeGC = std::stoi(argv[next]);
				i++;
			} else {
				std::cout << "Expected an number after the '--allocs-before-gc' option." << std::endl;
			}

			continue;
		}

		if (switchStr == "-psf" || switchStr == "--print-stack-frame") {
			vmState.printStackFrame = true;
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

		if (switchStr == "--print-gc-period") {
			vmState.printGCPeriod = true;
			continue;
		}

		if (switchStr == "--print-gc-stats") {
			vmState.printGCStats = true;
			continue;
		}

		if (switchStr == "--print-alive-objects") {
			vmState.printAliveObjects = true;
			continue;
		}

		if (switchStr == "--print-gc-stack-trace") {
			vmState.printGCStackTrace = true;
			continue;
		}

		if (switchStr == "--print-alloc") {
			vmState.printAllocation = true;
			continue;
		}

		if (switchStr == "--print-dealloc") {
			vmState.printDeallocation = true;
			continue;
		}

		if (switchStr == "-i") {
			int next = i + 1;

			if (next < argc) {
				engine.loadAssembly(argv[next]);
				i++;
			} else {
				std::cout << "Expected a library file after '-i' option." << std::endl;
			}

			continue;
		}

		if (switchStr.find(".simg") != std::string::npos) {
			program = switchStr;
			continue;
		}

		std::cout << "Unhandled option: " << switchStr << std::endl;
	}

	return program;
}

//Returns the directory of the executing VM
std::string getExecutableDir() {
#if defined(_WIN64) || defined(__MINGW32__)
	char buffer[MAX_PATH];
	int bytes = GetModuleFileNameA(nullptr, buffer, MAX_PATH);

	//Remove the name
	buffer[bytes - 12] = '\0';

	return std::string(buffer);
#else
	const int bufferSize = 512;
	char buffer[bufferSize];
	char temp[32];
	sprintf(temp, "/proc/%d/exe", getpid());
	int bytes = std::min((int)readlink(temp, buffer, bufferSize), bufferSize - 1);

	if (bytes >= 0) {
		buffer[bytes] = '\0';
	}

	//Remove the name
	buffer[bytes - 8] = '\0';

	return std::string(buffer);
#endif
}

int main(int argc, char* argv[]) {
	try {
		auto& vmState = Runtime::vmState;
		auto start = std::chrono::high_resolution_clock::now();
		auto& engine = vmState.engine();

		engine.setBaseDir(getExecutableDir());

		//Handle options
		auto programPath = handleOptions(argc, argv, engine);
		vmState.gc().initialize();

		//Load the program
		if (vmState.imageMode) {
			engine.loadAssembly(programPath, AssemblyType::Program);
		} else {
			AssemblyParser::Assembly program;
			Loader::load(std::cin, vmState, program);
			engine.loadAssembly(program, AssemblyType::Program);
		}

		if (!vmState.lazyJIT) {
			//Compile all functions
			engine.compile();
		} else {
			//Load definitions
			engine.load();

			//Compile the entry point
			engine.compileFunction("main()");
		}

		//Execute the program
		if (vmState.enableDebug) {
			std::cout << "Load time: " << Helpers::getDuration(start) << " ms." << std::endl;
			std::cout << "Program output:" << std::endl;
		}

		auto programPtr = engine.entryPoint();

		start = std::chrono::high_resolution_clock::now();
		int res = programPtr();

		if (vmState.enableDebug) {
			std::cout << "Return value (executed for " << Helpers::getDuration(start) << " ms): " << std::endl;
		}

		std::cout << res << std::endl;
		return 0;
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}
