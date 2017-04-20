#pragma once
#include "compiler/x64/amd64.h"
#include <vector>
#include <chrono>
#include <functional>

namespace stackjit {
	//Contains helper methods
	namespace Helpers {
		//Sets the value in the given byte vector starting at the given index
		template<typename T>
		void setValue(BytePtr source, std::size_t startIndex, T value);

		//Sets the value in the given byte vector starting at the given index
		template<typename T>
		void setValue(std::vector<unsigned char>& source, std::size_t startIndex, T value);

		//Returns the duration since the given time point
		std::int64_t getDuration(std::chrono::time_point<std::chrono::high_resolution_clock> timePoint);

		//Pushes the given array
		void pushArray(std::vector<unsigned char>& dest, const std::vector<unsigned char>& values);

		//Indicates if the given value fits in a char
		bool validCharValue(int value);

		//Splits the given string
		std::vector<std::string> splitString(std::string str, std::string delimiter);

		//Joins the given values using the given separator
		template <class T>
		std::string join(const std::vector<T>& values, std::function<std::string(T)> toString, std::string sep) {
			bool isFirst = true;
			std::string str = "";

			for (auto val : values) {
				if (!isFirst) {
					str += sep;
				} else {
					isFirst = false;
				}

				str += toString(val);
			}

			return str;
		}
	}

	template<typename T>
	void Helpers::setValue(BytePtr source, std::size_t startIndex, T value) {
		auto bytePtr = reinterpret_cast<BytePtr>(&value);
		for (std::size_t i = 0; i < sizeof(T); i++) {
			source[startIndex + i] = bytePtr[i];
		}
	}

	template<typename T>
	void Helpers::setValue(std::vector<unsigned char>& source, std::size_t startIndex, T value) {
		setValue(source.data(), startIndex, value);
	}
}
