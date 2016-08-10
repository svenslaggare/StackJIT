#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <cxxtest/TestSuite.h>
#include <regex>
#include "helpers.h"
#include "../src/helpers.h"

//Contains info about an GC
struct GC {
	std::string funcName;
	int instructionIndex;
	std::vector<std::size_t> deallocatedObjects;

	bool hasDeallocated(std::size_t obj) {
		for (auto current : deallocatedObjects) {
			if (current == obj) {
				return true;
			}
		}

		return false;
	}
};

//Holds all data for a GC test
struct GCTest {
	std::vector<std::size_t> allocatedObjects;
	std::vector<GC> collections;
};

//Parses the GC data
std::string parseGCData(std::string data, GCTest& gcTest) {
	gcTest = {};

	//Split into lines
	auto lines = stackjit::Helpers::splitString(data, "\n");
	GC currentGC;
	bool hasFound = false;

	std::regex gcStartRegex("Start GC in func (.*) \\((.*)\\)", std::regex_constants::ECMAScript);
	std::regex gcEndRegex("End GC", std::regex_constants::ECMAScript);
	std::regex allocatedObjectRegex("Allocated ((object)|(array)) \\(.*\\) at (.*)", std::regex_constants::ECMAScript);
	std::regex deallocatedObjectRegex("Deleted object: (.*):", std::regex_constants::ECMAScript);
	std::regex programOutputRegex("Program output:", std::regex_constants::ECMAScript);
	std::regex returnValueRegex("Return value.*", std::regex_constants::ECMAScript);
	std::regex loadTimeRegex("Load time.*", std::regex_constants::ECMAScript);

	std::string output = "";
	for (auto line : lines) {
		if (line == "") {
			continue;
		}

		std::smatch match;
		if (std::regex_search(line, match, gcStartRegex)) {
			currentGC = {};
			currentGC.funcName = match[1];
			currentGC.instructionIndex = std::stoi(match[2]);
			hasFound = true;
		} else if (std::regex_search(line, gcEndRegex)) {
			gcTest.collections.push_back(currentGC);
		} else if (std::regex_search(line, match, allocatedObjectRegex)) {
			gcTest.allocatedObjects.push_back(std::stoull(match[4], nullptr, 16));
		} else if (std::regex_search(line, match, deallocatedObjectRegex)) {
			currentGC.deallocatedObjects.push_back(std::stoull(match[1], nullptr, 16));
		} else if (std::regex_search(line, programOutputRegex)
				   || std::regex_search(line, returnValueRegex)
				   || std::regex_search(line, loadTimeRegex)) {
			//Skip these lines
		} else {
			output += line + "\n";
		}
	}

	return output;
}

using namespace Helpers;

/*
 * Tests the GC
 */
class VMGCTestSuite : public CxxTest::TestSuite {
public:
	std::string options = "-d --print-alloc --print-dealloc --print-gc-period --allocs-before-gc 0 --no-gc --no-rtlib";

	//Tests GC with refs on stack
	void testStack() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/callstack1", options), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 2);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);
		TS_ASSERT_EQUALS(gcTest.collections.at(1).deallocatedObjects.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(0)), true);
		TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
		TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(2)), true);

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/alive_on_stack1", options), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 2);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);
		TS_ASSERT_EQUALS(gcTest.collections.at(1).deallocatedObjects.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(1).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
		TS_ASSERT_EQUALS(gcTest.collections.at(2).deallocatedObjects.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(2).hasDeallocated(gcTest.allocatedObjects.at(0)), true);
	}

	//Tests GC with refs at locals
	void testLocals() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/locals1", options), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 2);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/locals2", options), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 2);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(0)), true);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
	}

	//Tests with ref elements
	void testRefElements() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/ref_elements", options), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 4);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);
	}

	//Tests with ref fields
	void testRefFields() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/ref_fields", options), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 2);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 0);
		TS_ASSERT_EQUALS(gcTest.collections.at(1).deallocatedObjects.size(), 0);
		TS_ASSERT_EQUALS(gcTest.collections.at(2).deallocatedObjects.size(), 0);
	}

	//Tests that the GC compacts
	void testCompact1() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/compact1", options), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 1);

		TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
		TS_ASSERT_EQUALS(gcTest.allocatedObjects[1], gcTest.allocatedObjects[2]);
	}

	//Tests that the root references are updated when the GC compacts
	void testRootRef() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/compact_update_root_ref", options), gcTest),
			"1337\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 2);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 1);
	}

	//Tests that the array references are updated when the GC compacts
	void testArraytRef() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/compact_update_array_ref", options), gcTest),
			"1337\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 1);
	}

	//Tests that the class references are updated when the GC compacts
	void testClassRef() {
		GCTest gcTest;

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/compact_update_class_ref", options), gcTest),
			"1337\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 3);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 1);
	}

	//Tests when the GC is run implicit
	void testGCImplicit() {
		GCTest gcTest;
		std::string options = "-d --print-alloc --print-dealloc --print-gc-period --no-rtlib";

		TS_ASSERT_EQUALS(invokeVM("gc/callstack1"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("gc/alive_on_stack1"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("gc/locals1"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("gc/locals2"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("gc/ref_elements"), "0\n");
		TS_ASSERT_EQUALS(invokeVM("gc/ref_fields"), "0\n")

		TS_ASSERT_EQUALS(
			parseGCData(invokeVM("gc/gctime", options + " --allocs-before-gc 2"), gcTest),
			"0\n");

		TS_ASSERT_EQUALS(gcTest.allocatedObjects.size(), 4);
		TS_ASSERT_EQUALS(gcTest.collections.size(), 1);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).deallocatedObjects.size(), 2);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(0)), true);
		TS_ASSERT_EQUALS(gcTest.collections.at(0).hasDeallocated(gcTest.allocatedObjects.at(1)), true);
	}
};
