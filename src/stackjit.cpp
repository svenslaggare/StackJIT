#include "loader/loader.h"
#include "vmstate.h"
#include "executionengine.h"
#include "helpers.h"
#include "runtime/runtime.h"
#include <iostream>
#include <fstream>
#include <chrono>

#if defined(_WIN64) || defined(__MINGW32__)
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace stackjit;

//The results of parsing the options
struct OptionsResult {
	VMStateConfig config;
	std::string program = "";
	std::vector<std::string> libraries;
};

//Parses the options
OptionsResult handleOptions(int argc, char* argv[]) {
	bool isFile = false;
	OptionsResult result;

	for (int i = 1; i < argc; i++) {
		std::string switchStr = argv[i];

		if (switchStr == "-d" || switchStr == "--debug") {
			result.config.enableDebug = true;
			continue;
		}

		if (switchStr == "-ogc" || switchStr == "--output-generated-code") {
			result.config.outputGeneratedCode = true;
			continue;
		}

		if (switchStr == "-lc" || switchStr == "--lazy-compile") {
			int next = i + 1;

			if (next < argc) {
				result.config.lazyJIT = std::string(argv[next]) == "1";
				i++;
			} else {
				std::cout << "Expected value after '" << switchStr << "' option." << std::endl;
			}

			continue;
		}

		if (switchStr == "-ngc" || switchStr == "--no-gc") {
			result.config.disableGC = true;
			continue;
		}

		if (switchStr == "-nrl" || switchStr == "--no-rtlib") {
			result.config.loadRuntimeLibrary = false;
			continue;
		}

		if (switchStr == "-t" || switchStr == "--test") {
			result.config.testMode = true;
			continue;
		}

		if (switchStr == "-im" || switchStr == "--image-mode") {
			result.config.programLoadMode = ProgramLoadMode::Image;
			continue;
		}

		if (switchStr == "-fm" || switchStr == "--file-mode") {
			result.config.programLoadMode = ProgramLoadMode::File;
			isFile = true;
			continue;
		}

		if (switchStr == "--allocs-before-gc") {
			int next = i + 1;

			if (next < argc) {
				result.config.allocationsBeforeGC = std::stoi(argv[next]);
				i++;
			} else {
				std::cout << "Expected an number after the '--allocs-before-gc' option." << std::endl;
			}

			continue;
		}

		if (switchStr == "-psf" || switchStr == "--print-stack-frame") {
			result.config.printStackFrame = true;
			continue;
		}

		if (switchStr == "-pfg" || switchStr == "--print-function-generation") {
			result.config.printFunctionGeneration = true;
			continue;
		}

		if (switchStr == "-plp" || switchStr == "--print-lazy-patching") {
			result.config.printLazyPatching = true;
			continue;
		}

		if (switchStr == "--print-gc-period") {
			result.config.printGCPeriod = true;
			continue;
		}

		if (switchStr == "--print-gc-stats") {
			result.config.printGCStats = true;
			continue;
		}

		if (switchStr == "--print-alive-objects") {
			result.config.printAliveObjects = true;
			continue;
		}

		if (switchStr == "--print-gc-stack-trace") {
			result.config.printGCStackTrace = true;
			continue;
		}

		if (switchStr == "--print-alloc") {
			result.config.printAllocation = true;
			continue;
		}

		if (switchStr == "--print-dealloc") {
			result.config.printDeallocation = true;
			continue;
		}

		if (switchStr == "--print-vtable") {
			result.config.printVirtualFunctionTableLayout = true;
			continue;
		}

		if (switchStr == "-i") {
			int next = i + 1;

			if (next < argc) {
				result.libraries.push_back(argv[next]);
				i++;
			} else {
				std::cout << "Expected a library file after '-i' option." << std::endl;
			}

			continue;
		}

		if (switchStr.find(".simg") != std::string::npos) {
			result.program = switchStr;
			continue;
		}

		if (isFile) {
			result.program = switchStr;
			isFile = false;
			continue;
		}

		std::cout << "Unhandled option: " << switchStr << std::endl;
	}

	return result;
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
		//Handle options
		auto options = handleOptions(argc, argv);

		VMState vmState(options.config);
		Runtime::initialize(&vmState);

		auto start = std::chrono::high_resolution_clock::now();
		auto& engine = vmState.engine();

		engine.setBaseDir(getExecutableDir());

		//Load the libraries
		for (auto& lib : options.libraries) {
			engine.loadAssembly(lib);
		}

		//Load the program
		switch (vmState.config.programLoadMode) {
			case ProgramLoadMode::Stdin: {
				AssemblyParser::Assembly program;
				Loader::load(std::cin, vmState, program);
				engine.loadAssembly(program, AssemblyType::Program);
				break;
			}
			case ProgramLoadMode::Image:
				engine.loadAssembly(options.program, AssemblyType::Program);
				break;
			case ProgramLoadMode::File: {
				std::ifstream file(options.program);
				if (file.is_open()) {
					AssemblyParser::Assembly program;
					Loader::load(file, vmState, program);
					engine.loadAssembly(program, AssemblyType::Program);
				} else {
					throw std::runtime_error("Could not load program.");
				}
				break;
			}
		}

		if (!vmState.config.lazyJIT) {
			//Compile all functions
			engine.compile();
		} else {
			//Load definitions
			engine.load();

			//Compile the entry point
			engine.compileFunction(stackjit::entryPointSignature);
		}

		//Execute the program
		if (vmState.config.enableDebug) {
			std::cout << "Load time: " << Helpers::getDuration(start) << " ms." << std::endl;
			std::cout << "Program output:" << std::endl;
		}

		auto programPtr = engine.entryPoint();

		start = std::chrono::high_resolution_clock::now();
		int res = programPtr();

		if (vmState.config.enableDebug) {
			std::cout << "Return value (executed for " << Helpers::getDuration(start) << " ms): " << std::endl;
		}

		std::cout << res << std::endl;
		return 0;
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}
