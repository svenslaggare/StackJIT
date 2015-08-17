#include "helpers.h"
#include "amd64.h"

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
	IntToBytes converter;
	converter.intValue = value;

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