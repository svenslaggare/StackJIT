#pragma once

#include <vector>
#include "amd64.h"

//Contains helper methods
namespace Helpers {
	//Sets the integer in the given byte vector starting at the given index
	void setInt(std::vector<unsigned char>& source, std::size_t startIndex, int value);
	void setInt(unsigned char* source, std::size_t startIndex, int value);

	//Sets the long in the given byte vector starting at the given index
	void setLong(std::vector<unsigned char>& source, std::size_t startIndex, long value);
	void setLong(unsigned char* source, std::size_t startIndex, long value);
}