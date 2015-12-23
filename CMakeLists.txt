cmake_minimum_required(VERSION 3.3)
project(StackJIT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/compiler/amd64.cpp
        src/compiler/amd64.h
        src/compiler/binder.cpp
        src/compiler/binder.h
        src/compiler/callingconvention.h
        src/compiler/codegenerator.cpp
        src/compiler/codegenerator.h
        src/executionengine.cpp
        src/executionengine.h
        src/function.cpp
        src/function.h
        src/runtime/gc.cpp
        src/runtime/gc.h
        src/instructions.cpp
        src/instructions.h
        src/compiler/jit.cpp
        src/compiler/jit.h
        src/loader/loader.cpp
        src/loader/loader.h
        src/compiler/memory.h
        src/runtime/native.cpp
        src/runtime/native.h
        src/type/objects.cpp
        src/type/objects.h
        src/loader/parser.cpp
        src/loader/parser.h
        src/runtime/rtlibrary.cpp
        src/runtime/rtlibrary.h
        src/stackjit.cpp
        src/stackjit.h
        src/type/classmetadata.cpp
        src/type/classmetadata.h
        src/type/type.cpp
        src/type/type.h
        src/loader/verifier.cpp
        src/loader/verifier.h
        src/type/typeprovider.cpp
        src/type/typeprovider.h
        src/vmstate.cpp
        src/vmstate.h
        src/type/objectref.h
        src/type/objectref.cpp
        src/runtime/stackframe.h
        src/runtime/stackframe.cpp
        src/instructionset.h
        src/helpers.h
        src/helpers.cpp
        src/test/test.h
        src/test/test.cpp
        src/compiler/exceptions.h
        src/compiler/exceptions.cpp
        src/runtime/callstack.h
        src/runtime/callstack.cpp
        src/linux/memory.cpp
        src/linux/callingconvention.h
        src/linux/callingconvetion.cpp
        src/windows/memory.cpp
        src/windows/callingconvention.h
        src/windows/callingconvetion.cpp
        src/bytecodegenerator.h
        src/bytecodegenerator.cpp
        src/loader/imageloader.h
        src/loader/imageloader.cpp
        src/functionsignature.cpp
        src/functionsignature.h
        src/compiler/compilationdata.cpp
        src/compiler/compilationdata.h
        src/loader/imagecontainer.cpp
        src/loader/imagecontainer.h)

add_executable(stackjit ${SOURCE_FILES})

# Tests
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

find_package(CxxTest)
if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()
    CXXTEST_ADD_TEST(tests-vm test-vm-runner.cpp ${TESTS_DIR}/vm-test.h ${SOURCE_FILES})
    CXXTEST_ADD_TEST(tests-amd64 test-amd64-runner.cpp ${TESTS_DIR}/amd64-test.h ${SOURCE_FILES})
endif()
