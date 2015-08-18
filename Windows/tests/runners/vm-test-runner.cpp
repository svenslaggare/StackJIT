/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_VMTestSuite_init = false;
#include "C:\Users\Anton Jansson\Documents\GitHub\StackJIT\tests\vm-test.h"

static VMTestSuite suite_VMTestSuite;

static CxxTest::List Tests_VMTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_VMTestSuite( "../../tests/vm-test.h", 82, "VMTestSuite", suite_VMTestSuite, Tests_VMTestSuite );

static class TestDescription_suite_VMTestSuite_testBasic : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testBasic() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 84, "testBasic" ) {}
 void runTest() { suite_VMTestSuite.testBasic(); }
} testDescription_suite_VMTestSuite_testBasic;

static class TestDescription_suite_VMTestSuite_testStack : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testStack() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 104, "testStack" ) {}
 void runTest() { suite_VMTestSuite.testStack(); }
} testDescription_suite_VMTestSuite_testStack;

static class TestDescription_suite_VMTestSuite_testCall : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testCall() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 112, "testCall" ) {}
 void runTest() { suite_VMTestSuite.testCall(); }
} testDescription_suite_VMTestSuite_testCall;

static class TestDescription_suite_VMTestSuite_testComparison : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testComparison() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 144, "testComparison" ) {}
 void runTest() { suite_VMTestSuite.testComparison(); }
} testDescription_suite_VMTestSuite_testComparison;

static class TestDescription_suite_VMTestSuite_testBranch : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testBranch() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 166, "testBranch" ) {}
 void runTest() { suite_VMTestSuite.testBranch(); }
} testDescription_suite_VMTestSuite_testBranch;

static class TestDescription_suite_VMTestSuite_testString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testString() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 208, "testString" ) {}
 void runTest() { suite_VMTestSuite.testString(); }
} testDescription_suite_VMTestSuite_testString;

static class TestDescription_suite_VMTestSuite_testArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testArray() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 213, "testArray" ) {}
 void runTest() { suite_VMTestSuite.testArray(); }
} testDescription_suite_VMTestSuite_testArray;

static class TestDescription_suite_VMTestSuite_testClasses : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testClasses() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 225, "testClasses" ) {}
 void runTest() { suite_VMTestSuite.testClasses(); }
} testDescription_suite_VMTestSuite_testClasses;

static class TestDescription_suite_VMTestSuite_testFunction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testFunction() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 285, "testFunction" ) {}
 void runTest() { suite_VMTestSuite.testFunction(); }
} testDescription_suite_VMTestSuite_testFunction;

static class TestDescription_suite_VMTestSuite_testInvalid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testInvalid() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 296, "testInvalid" ) {}
 void runTest() { suite_VMTestSuite.testInvalid(); }
} testDescription_suite_VMTestSuite_testInvalid;

static class TestDescription_suite_VMTestSuite_testLibrary : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testLibrary() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 307, "testLibrary" ) {}
 void runTest() { suite_VMTestSuite.testLibrary(); }
} testDescription_suite_VMTestSuite_testLibrary;

static class TestDescription_suite_VMTestSuite_testAttributes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testAttributes() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 351, "testAttributes" ) {}
 void runTest() { suite_VMTestSuite.testAttributes(); }
} testDescription_suite_VMTestSuite_testAttributes;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
