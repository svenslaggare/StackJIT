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
bool suite_AssemblerTestSuite_init = false;
#include "/home/antjans/Code/StackJIT/assembler/tests/assembler-test.h"

static AssemblerTestSuite suite_AssemblerTestSuite;

static CxxTest::List Tests_AssemblerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AssemblerTestSuite( "tests/assembler-test.h", 71, "AssemblerTestSuite", suite_AssemblerTestSuite, Tests_AssemblerTestSuite );

static class TestDescription_suite_AssemblerTestSuite_testCase1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AssemblerTestSuite_testCase1() : CxxTest::RealTestDescription( Tests_AssemblerTestSuite, suiteDescription_AssemblerTestSuite, 73, "testCase1" ) {}
 void runTest() { suite_AssemblerTestSuite.testCase1(); }
} testDescription_suite_AssemblerTestSuite_testCase1;

static class TestDescription_suite_AssemblerTestSuite_testCase2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AssemblerTestSuite_testCase2() : CxxTest::RealTestDescription( Tests_AssemblerTestSuite, suiteDescription_AssemblerTestSuite, 77, "testCase2" ) {}
 void runTest() { suite_AssemblerTestSuite.testCase2(); }
} testDescription_suite_AssemblerTestSuite_testCase2;

static class TestDescription_suite_AssemblerTestSuite_testCase3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AssemblerTestSuite_testCase3() : CxxTest::RealTestDescription( Tests_AssemblerTestSuite, suiteDescription_AssemblerTestSuite, 81, "testCase3" ) {}
 void runTest() { suite_AssemblerTestSuite.testCase3(); }
} testDescription_suite_AssemblerTestSuite_testCase3;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
