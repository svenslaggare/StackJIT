#pragma once
#include "compiler/amd64.h"
#include <vector>
#include <chrono>

//Contains helper methods
namespace Helpers {
	//Sets the value in the given byte vector starting at the given index
	template<typename T>
	void setValue(std::vector<unsigned char>& source, std::size_t startIndex, T value);

	template<typename T>
	void setValue(unsigned char* source, std::size_t startIndex, T value);

	//Returns the duration since the given time point
	std::int64_t getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> timePoint);
}

template<typename T>
void Helpers::setValue(std::vector<unsigned char>& source, std::size_t startIndex, T value) {
	auto bytePtr = reinterpret_cast<unsigned char*>(&value);
	for (std::size_t i = 0; i < sizeof(T); i++) {
		source[startIndex + i] = bytePtr[i];
	}
}

template<typename T>
void Helpers::setValue(unsigned char* source, std::size_t startIndex, T value) {
	auto bytePtr = reinterpret_cast<unsigned char*>(&value);
	for (std::size_t i = 0; i < sizeof(T); i++) {
		source[startIndex + i] = bytePtr[i];
	}
}