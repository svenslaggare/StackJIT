#pragma once
#include "compiler/amd64.h"
#include <vector>
#include <chrono>

//Contains helper methods
namespace Helpers {
	//Sets the integer in the given byte vector starting at the given index
	void setInt(std::vector<unsigned char>& source, std::size_t startIndex, int value);
	void setInt(unsigned char* source, std::size_t startIndex, int value);

	//Sets the long in the given byte vector starting at the given index
	void setLong(std::vector<unsigned char>& source, std::size_t startIndex, long value);
	void setLong(unsigned char* source, std::size_t startIndex, long value);

	//Sets the pointer in the given byte vector starting at the given index
	void setPointer(std::vector<unsigned char>& source, std::size_t startIndex, unsigned char* value);
	void setPointer(unsigned char* source, std::size_t startIndex, unsigned char* value);

	//Returns the duration since the given time point
	std::int64_t getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> timePoint);
}