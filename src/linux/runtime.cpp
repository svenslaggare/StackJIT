#ifdef __unix__
#include <unistd.h>
#include <iostream>
#include <fstream>

namespace stackjit {
	/**
	 * Provides implementation of Linux specific runtime functions
	 */
	namespace Runtime {
		std::string getExecutableDir() {
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
		}
	}
}
#endif