cmake_minimum_required(VERSION 3.3)
project(StackJIT)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

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
        src/core/function.cpp
        src/core/function.h
        src/runtime/gc.cpp
        src/runtime/gc.h
        src/core/instruction.cpp
        src/core/instruction.h
        src/compiler/jit.cpp
        src/compiler/jit.h
        src/loader/loader.cpp
        src/loader/loader.h
        src/compiler/memory.h
        src/compiler/memory.cpp
        src/runtime/native.cpp
        src/runtime/native.h
        src/loader/parser.cpp
        src/loader/parser.h
        src/runtime/runtime.cpp
        src/runtime/runtime.h
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
        src/type/objectref.hpp
        src/runtime/stackframe.h
        src/runtime/stackframe.cpp
        src/core/instructionset.h
        src/helpers.h
        src/helpers.cpp
        src/test/test.h
        src/test/test.cpp
        src/compiler/exceptions.h
        src/compiler/exceptions.cpp
        src/runtime/callstack.h
        src/runtime/callstack.cpp
        src/linux/callingconvention.h
        src/linux/callingconvetion.cpp
        src/windows/callingconvention.h
        src/windows/callingconvetion.cpp
        src/bytecodegenerator.h
        src/bytecodegenerator.cpp
        src/loader/imageloader.h
        src/loader/imageloader.cpp
        src/core/functionsignature.cpp
        src/core/functionsignature.h
        src/compiler/compilationdata.cpp
        src/compiler/compilationdata.h
        src/loader/imagecontainer.cpp
        src/loader/imagecontainer.h
        src/compiler/allocator.h
        src/linux/allocator.cpp
        src/windows/allocator.cpp
        src/runtime/managedheap.cpp
        src/runtime/managedheap.h
        src/compiler/amd64assembler.cpp
        src/compiler/amd64assembler.h
        src/runtime/native/stringref.cpp
        src/runtime/native/stringref.h)

# Project structure for VS
SOURCE_GROUP(base REGULAR_EXPRESSION "src/(.*)\\.((cpp)|(h))")
SOURCE_GROUP(core REGULAR_EXPRESSION "src/core/(.*)")
SOURCE_GROUP(compiler REGULAR_EXPRESSION "src/compiler/(.*)")
SOURCE_GROUP(loader REGULAR_EXPRESSION "src/loader/(.*)")
SOURCE_GROUP(runtime REGULAR_EXPRESSION "src/runtime/(.*)")
SOURCE_GROUP(type REGULAR_EXPRESSION "src/type/(.*)")
SOURCE_GROUP(test REGULAR_EXPRESSION "src/test/(.*)")
SOURCE_GROUP(windows REGULAR_EXPRESSION "src/windows/(.*)")
SOURCE_GROUP(linux REGULAR_EXPRESSION "src/linux/(.*)")

add_executable(stackjit ${SOURCE_FILES} src/stackjit.cpp)

# StackAssembler
set(STACK_ASSEMBLER_SOURCE_FILES
    "assembler/src/assembler.cpp"
    "assembler/src/assembler.h"
    "assembler/src/bytecodegenerator.cpp"
    "assembler/src/bytecodegenerator.h"
    "assembler/src/imageloader.cpp"
    "assembler/src/imageloader.h"
    "assembler/src/parser.cpp"
    "assembler/src/parser.h")

add_executable(stackasm ${STACK_ASSEMBLER_SOURCE_FILES} assembler/src/stackasm.cpp)

# Build the runtime library
set(RUNTIME_LIBRARY_FOLDER rtlib)
file(GLOB RUNTIME_LIBRARY_FILES ${RUNTIME_LIBRARY_FOLDER}/*.sbc)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(RUNTIME_LIBRARY Debug/${RUNTIME_LIBRARY_FOLDER}/rtlib.simg)

    add_custom_command(
        OUTPUT ${RUNTIME_LIBRARY}
        COMMAND stackasm ${RUNTIME_LIBRARY_FILES} -o ${RUNTIME_LIBRARY}
        VERBATIM)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(RUNTIME_LIBRARY ${RUNTIME_LIBRARY_FOLDER}/rtlib.simg)

    add_custom_command(
            OUTPUT ${RUNTIME_LIBRARY}
            COMMAND ./stackasm ${RUNTIME_LIBRARY_FILES} -o ${RUNTIME_LIBRARY}
            VERBATIM)
endif()

add_custom_target(BuildRuntimeLibrary ALL DEPENDS ${RUNTIME_LIBRARY} stackasm)

# Tests
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

find_package(CxxTest)
if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()

    CXXTEST_ADD_TEST(tests-basic-vm test-vm-basic-runner.cpp ${TESTS_DIR}/vm-basic-test.h)
    add_dependencies(tests-basic-vm BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-array test-vm-array-runner.cpp ${TESTS_DIR}/vm-array-test.h)
    add_dependencies(tests-vm-array BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-attributes test-vm-attributes-runner.cpp ${TESTS_DIR}/vm-attributes-test.h)
    add_dependencies(tests-vm-attributes BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-branch test-vm-branch-runner.cpp ${TESTS_DIR}/vm-branch-test.h)
    add_dependencies(tests-vm-branch BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-calling test-vm-calling-runner.cpp ${TESTS_DIR}/vm-calling-test.h)
    add_dependencies(tests-vm-calling BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-class test-vm-class-runner.cpp ${TESTS_DIR}/vm-class-test.h)
    add_dependencies(tests-vm-class BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-comparison test-vm-comparison-runner.cpp ${TESTS_DIR}/vm-comparison-test.h)
    add_dependencies(tests-vm-comparison BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-exception test-vm-exception-runner.cpp ${TESTS_DIR}/vm-exception-test.h)
    add_dependencies(tests-vm-exception BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-library test-vm-library-runner.cpp ${TESTS_DIR}/vm-library-test.h)
    add_dependencies(tests-vm-library BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-rtlib test-vm-rtlib-runner.cpp ${TESTS_DIR}/vm-rtlib-test.h)
    add_dependencies(tests-vm-rtlib BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-string test-vm-string-runner.cpp ${TESTS_DIR}/vm-string-test.h)
    add_dependencies(tests-vm-string BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-verifier test-vm-verifier-runner.cpp ${TESTS_DIR}/vm-verifier-test.h)
    add_dependencies(tests-vm-verifier BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-vm-gc test-vm-gc-runner.cpp ${TESTS_DIR}/vm-gc-test.h)
    add_dependencies(tests-vm-gc BuildRuntimeLibrary stackjit)

    CXXTEST_ADD_TEST(tests-amd64 test-amd64-runner.cpp ${TESTS_DIR}/amd64-test.h src/compiler/amd64.cpp src/compiler/amd64.h src/helpers.h src/helpers.cpp)
endif()
