#if defined(_WIN64) || defined(__MINGW32__)
#include <string>
#include <Windows.h>

namespace stackjit {
	/**
	 * Provides implementation of Linux specific runtime functions
	 */
	namespace Runtime {
		std::string getExecutableDir() {
			char buffer[MAX_PATH];
			int bytes = GetModuleFileNameA(nullptr, buffer, MAX_PATH);

			//Remove the name
			buffer[bytes - 12] = '\0';
			return std::string(buffer);
		}
	}
}
#endif