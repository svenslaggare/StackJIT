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
#include <cxxtest/ParenPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ParenPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ParenPrinter >( tmp, argc, argv );
    return status;
}
bool suite_VMTestSuite_init = false;
#include "C:\Users\Anton Jansson\Documents\GitHub\StackJIT\tests\vm-test.h"

static VMTestSuite suite_VMTestSuite;

static CxxTest::List Tests_VMTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_VMTestSuite( "../../tests/vm-test.h", 140, "VMTestSuite", suite_VMTestSuite, Tests_VMTestSuite );

static class TestDescription_suite_VMTestSuite_testBasic : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testBasic() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 142, "testBasic" ) {}
 void runTest() { suite_VMTestSuite.testBasic(); }
} testDescription_suite_VMTestSuite_testBasic;

static class TestDescription_suite_VMTestSuite_testStack : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testStack() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 163, "testStack" ) {}
 void runTest() { suite_VMTestSuite.testStack(); }
} testDescription_suite_VMTestSuite_testStack;

static class TestDescription_suite_VMTestSuite_testCall : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testCall() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 171, "testCall" ) {}
 void runTest() { suite_VMTestSuite.testCall(); }
} testDescription_suite_VMTestSuite_testCall;

static class TestDescription_suite_VMTestSuite_testComparison : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testComparison() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 203, "testComparison" ) {}
 void runTest() { suite_VMTestSuite.testComparison(); }
} testDescription_suite_VMTestSuite_testComparison;

static class TestDescription_suite_VMTestSuite_testBranch : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testBranch() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 228, "testBranch" ) {}
 void runTest() { suite_VMTestSuite.testBranch(); }
} testDescription_suite_VMTestSuite_testBranch;

static class TestDescription_suite_VMTestSuite_testString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testString() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 278, "testString" ) {}
 void runTest() { suite_VMTestSuite.testString(); }
} testDescription_suite_VMTestSuite_testString;

static class TestDescription_suite_VMTestSuite_testArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testArray() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 284, "testArray" ) {}
 void runTest() { suite_VMTestSuite.testArray(); }
} testDescription_suite_VMTestSuite_testArray;

static class TestDescription_suite_VMTestSuite_testClasses : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testClasses() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 306, "testClasses" ) {}
 void runTest() { suite_VMTestSuite.testClasses(); }
} testDescription_suite_VMTestSuite_testClasses;

static class TestDescription_suite_VMTestSuite_testException : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testException() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 344, "testException" ) {}
 void runTest() { suite_VMTestSuite.testException(); }
} testDescription_suite_VMTestSuite_testException;

static class TestDescription_suite_VMTestSuite_testGCExplicit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testGCExplicit() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 359, "testGCExplicit" ) {}
 void runTest() { suite_VMTestSuite.testGCExplicit(); }
} testDescription_suite_VMTestSuite_testGCExplicit;

static class TestDescription_suite_VMTestSuite_testGCImplicit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testGCImplicit() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 424, "testGCImplicit" ) {}
 void runTest() { suite_VMTestSuite.testGCImplicit(); }
} testDescription_suite_VMTestSuite_testGCImplicit;

static class TestDescription_suite_VMTestSuite_testFunction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testFunction() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 446, "testFunction" ) {}
 void runTest() { suite_VMTestSuite.testFunction(); }
} testDescription_suite_VMTestSuite_testFunction;

static class TestDescription_suite_VMTestSuite_testInvalid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testInvalid() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 457, "testInvalid" ) {}
 void runTest() { suite_VMTestSuite.testInvalid(); }
} testDescription_suite_VMTestSuite_testInvalid;

static class TestDescription_suite_VMTestSuite_testLibrary : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testLibrary() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 468, "testLibrary" ) {}
 void runTest() { suite_VMTestSuite.testLibrary(); }
} testDescription_suite_VMTestSuite_testLibrary;

static class TestDescription_suite_VMTestSuite_testRuntimeLibrary : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testRuntimeLibrary() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 510, "testRuntimeLibrary" ) {}
 void runTest() { suite_VMTestSuite.testRuntimeLibrary(); }
} testDescription_suite_VMTestSuite_testRuntimeLibrary;

static class TestDescription_suite_VMTestSuite_testNative : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testNative() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 522, "testNative" ) {}
 void runTest() { suite_VMTestSuite.testNative(); }
} testDescription_suite_VMTestSuite_testNative;

static class TestDescription_suite_VMTestSuite_testAttributes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testAttributes() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 527, "testAttributes" ) {}
 void runTest() { suite_VMTestSuite.testAttributes(); }
} testDescription_suite_VMTestSuite_testAttributes;

static class TestDescription_suite_VMTestSuite_testLazy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VMTestSuite_testLazy() : CxxTest::RealTestDescription( Tests_VMTestSuite, suiteDescription_VMTestSuite, 532, "testLazy" ) {}
 void runTest() { suite_VMTestSuite.testLazy(); }
} testDescription_suite_VMTestSuite_testLazy;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
