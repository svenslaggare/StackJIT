cmake_minimum_required(VERSION 3.3)
project(StackJIT)

add_definitions(-DUSE_CMAKE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(SOURCE_FILES
        src/bytecode/bytecodegenerator.cpp
        src/bytecode/bytecodegenerator.h
        src/bytecode/bytecodeparser.cpp
        src/bytecode/bytecodeparser.h
        src/compiler/allocator.h
        src/compiler/binder.cpp
        src/compiler/binder.h
        src/compiler/callingconvention.h
        src/compiler/jit.cpp
        src/compiler/jit.h
        src/compiler/memory.cpp
        src/compiler/memory.h
        src/compiler/x64/amd64.cpp
        src/compiler/x64/amd64.h
        src/compiler/x64/amd64assembler.cpp
        src/compiler/x64/amd64assembler.h
        src/compiler/x64/codegenerator.cpp
        src/compiler/x64/codegenerator.h
        src/compiler/x64/compilationdata.cpp
        src/compiler/x64/compilationdata.h
        src/compiler/x64/exceptions.cpp
        src/compiler/x64/exceptions.h
        src/core/function.cpp
        src/core/function.h
        src/core/functionsignature.cpp
        src/core/functionsignature.h
        src/core/instruction.cpp
        src/core/instruction.h
        src/core/instructionset.h
        src/executionengine.cpp
        src/executionengine.h
        src/helpers.cpp
        src/helpers.h
        src/linux/allocator.cpp
        src/linux/callingconvention.h
        src/linux/callingconvetion.cpp
        src/linux/codegenerator.cpp
        src/linux/runtime.cpp
        src/loader/classloader.cpp
        src/loader/classloader.h
        src/loader/functionloader.cpp
        src/loader/functionloader.h
        src/loader/imagecontainer.cpp
        src/loader/imagecontainer.h
        src/loader/imagegenerator.cpp
        src/loader/imagegenerator.h
        src/loader/imageloader.cpp
        src/loader/imageloader.h
        src/loader/loader.cpp
        src/loader/loader.h
        src/loader/loaderhelpers.cpp
        src/loader/loaderhelpers.h
        src/loader/verifier.cpp
        src/loader/verifier.h
        src/runtime/callstack.cpp
        src/runtime/callstack.h
        src/runtime/gc.cpp
        src/runtime/gc.h
        src/runtime/gcgeneration.cpp
        src/runtime/gcgeneration.h
        src/runtime/managedheap.cpp
        src/runtime/managedheap.h
        src/runtime/native.cpp
        src/runtime/native.h
        src/runtime/native/stringref.cpp
        src/runtime/native/stringref.h
        src/runtime/runtime.cpp
        src/runtime/runtime.h
        src/runtime/stackframe.cpp
        src/runtime/stackframe.h
        src/stackjit.h
        src/test/test.cpp
        src/test/test.h
        src/type/classmetadata.cpp
        src/type/classmetadata.h
        src/type/objectref.cpp
        src/type/objectref.h
        src/type/objectref.hpp
        src/type/type.cpp
        src/type/type.h
        src/type/typeprovider.cpp
        src/type/typeprovider.h
        src/vmstate.cpp
        src/vmstate.h
        src/windows/allocator.cpp
        src/windows/callingconvention.h
        src/windows/callingconvetion.cpp
        src/windows/codegenerator.cpp
        src/windows/runtime.cpp
)

add_executable(stackjit ${SOURCE_FILES} src/stackjit.cpp)

# Project structure for VS
SOURCE_GROUP(base REGULAR_EXPRESSION "src/(.*)\\.((cpp)|(h))")
SOURCE_GROUP(core REGULAR_EXPRESSION "src/core/(.*)")
SOURCE_GROUP(compiler REGULAR_EXPRESSION "src/compiler/(.*)")
SOURCE_GROUP(loader REGULAR_EXPRESSION "src/loader/(.*)")
SOURCE_GROUP(runtime REGULAR_EXPRESSION "src/runtime/(.*)")
SOURCE_GROUP(type REGULAR_EXPRESSION "src/type/(.*)")
SOURCE_GROUP(bytecode REGULAR_EXPRESSION "src/bytecode/(.*)")
SOURCE_GROUP(test REGULAR_EXPRESSION "src/test/(.*)")
SOURCE_GROUP(windows REGULAR_EXPRESSION "src/windows/(.*)")
SOURCE_GROUP(linux REGULAR_EXPRESSION "src/linux/(.*)")

# StackAssembler
set(STACK_ASSEMBLER_SOURCE_FILES
        assembler/src/assembler.cpp
        assembler/src/assembler.h
        assembler/src/bytecodegenerator.cpp
        assembler/src/bytecodegenerator.h
        assembler/src/imageloader.cpp
        assembler/src/imageloader.h
        assembler/src/loader.cpp
        assembler/src/loader.h
        assembler/src/bytecodeparser.cpp
        assembler/src/bytecodeparser.h)

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
            COMMAND mkdir -p rtlib
            COMMAND ./stackasm ${RUNTIME_LIBRARY_FILES} -o ${CMAKE_BINARY_DIR}/${RUNTIME_LIBRARY}
            VERBATIM)
endif()

add_custom_target(BuildRuntimeLibrary ALL DEPENDS ${RUNTIME_LIBRARY} stackasm)
add_dependencies(stackjit BuildRuntimeLibrary)

# Build the embeddable VM
add_library(stackjitvm STATIC ${SOURCE_FILES})

# Tests
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Move tests files to build dir
file(GLOB_RECURSE TEST_FILES programs/*.txt)

foreach (_currentFile ${TEST_FILES})
    file(RELATIVE_PATH relativePath ${CMAKE_CURRENT_SOURCE_DIR} ${_currentFile})
    configure_file(${_currentFile} ${CMAKE_CURRENT_BINARY_DIR}/${relativePath} COPYONLY)
endforeach()

find_package(CxxTest)
if(CXXTEST_FOUND)
    add_custom_target(
            check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
            ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()

    CXXTEST_ADD_TEST(tests-basic-vm test-vm-basic-runner.cpp ${TESTS_DIR}/vm-basic-test.h)
    add_dependencies(tests-basic-vm stackjit)

    CXXTEST_ADD_TEST(tests-vm-array test-vm-array-runner.cpp ${TESTS_DIR}/vm-array-test.h)
    add_dependencies(tests-vm-array stackjit)

    CXXTEST_ADD_TEST(tests-vm-attributes test-vm-attributes-runner.cpp ${TESTS_DIR}/vm-attributes-test.h)
    add_dependencies(tests-vm-attributes stackjit)

    CXXTEST_ADD_TEST(tests-vm-branch test-vm-branch-runner.cpp ${TESTS_DIR}/vm-branch-test.h)
    add_dependencies(tests-vm-branch stackjit)

    CXXTEST_ADD_TEST(tests-vm-calling test-vm-calling-runner.cpp ${TESTS_DIR}/vm-calling-test.h)
    add_dependencies(tests-vm-calling stackjit)

    CXXTEST_ADD_TEST(tests-vm-comparison test-vm-comparison-runner.cpp ${TESTS_DIR}/vm-comparison-test.h)
    add_dependencies(tests-vm-comparison stackjit)

    CXXTEST_ADD_TEST(tests-vm-class test-vm-class-runner.cpp ${TESTS_DIR}/vm-class-test.h)
    add_dependencies(tests-vm-class stackjit)

    CXXTEST_ADD_TEST(tests-vm-virtual test-vm-virtual-runner.cpp ${TESTS_DIR}/vm-virtual-test.h)
    add_dependencies(tests-vm-virtual stackjit)

    CXXTEST_ADD_TEST(tests-vm-exception test-vm-exception-runner.cpp ${TESTS_DIR}/vm-exception-test.h)
    add_dependencies(tests-vm-exception stackjit)

    CXXTEST_ADD_TEST(tests-vm-library test-vm-library-runner.cpp ${TESTS_DIR}/vm-library-test.h)
    add_dependencies(tests-vm-library stackjit)

    CXXTEST_ADD_TEST(tests-vm-rtlib test-vm-rtlib-runner.cpp ${TESTS_DIR}/vm-rtlib-test.h)
    add_dependencies(tests-vm-rtlib stackjit)

    CXXTEST_ADD_TEST(tests-vm-string test-vm-string-runner.cpp ${TESTS_DIR}/vm-string-test.h)
    add_dependencies(tests-vm-string stackjit)

    CXXTEST_ADD_TEST(tests-vm-verifier test-vm-verifier-runner.cpp ${TESTS_DIR}/vm-verifier-test.h)
    add_dependencies(tests-vm-verifier stackjit)

    CXXTEST_ADD_TEST(tests-vm-gc test-vm-gc-runner.cpp ${TESTS_DIR}/vm-gc-test.h src/helpers.h src/helpers.cpp)
    add_dependencies(tests-vm-gc stackjit)

    CXXTEST_ADD_TEST(tests-amd64 test-amd64-runner.cpp ${TESTS_DIR}/amd64-test.h src/compiler/x64/amd64.cpp src/compiler/x64/amd64.h src/helpers.h src/helpers.cpp)
endif()
