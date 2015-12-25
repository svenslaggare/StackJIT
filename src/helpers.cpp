#include "helpers.h"

std::int64_t Helpers::getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> timePoint) {
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - timePoint).count();
}