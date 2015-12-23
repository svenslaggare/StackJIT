#include "helpers.h"

void Helpers::setInt(std::vector<unsigned char>& source, std::size_t startIndex, int value) {
	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		source[startIndex + i] = converter.byteValues[i];
	}
}

void Helpers::setInt(unsigned char* source, std::size_t startIndex, int value) {
	IntToBytes converter;
	converter.intValue = value;

	for (std::size_t i = 0; i < sizeof(int); i++) {
		source[startIndex + i] = converter.byteValues[i];
	}
}

void Helpers::setLong(std::vector<unsigned char>& source, std::size_t startIndex, long value) {
	LongToBytes converter;
	converter.longValue = value;

	for (std::size_t i = 0; i < sizeof(long); i++) {
		source[startIndex + i] = converter.byteValues[i];
	}
}

void Helpers::setLong(unsigned char* source, std::size_t startIndex, long value) {
	LongToBytes converter;
	converter.longValue = value;

	for (std::size_t i = 0; i < sizeof(long); i++) {
		source[startIndex + i] = converter.byteValues[i];
	}
}

void Helpers::setPointer(std::vector<unsigned char>& source, std::size_t startIndex, unsigned char* value) {
	PtrToBytes converter;
	converter.ptrValue = value;

	for (std::size_t i = 0; i < sizeof(unsigned char*); i++) {
		source[startIndex + i] = converter.byteValues[i];
	}
}

void Helpers::setPointer(unsigned char* source, std::size_t startIndex, unsigned char* value) {
	PtrToBytes converter;
	converter.ptrValue = value;

	for (std::size_t i = 0; i < sizeof(unsigned char*); i++) {
		source[startIndex + i] = converter.byteValues[i];
	}
}

std::int64_t Helpers::getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> timePoint) {
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - timePoint).count();
}