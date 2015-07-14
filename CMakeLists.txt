cmake_minimum_required(VERSION 3.2)
project(StackJIT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/amd64.cpp
    src/amd64.h
    src/assembly.cpp
    src/assembly.h
    src/binder.cpp
    src/binder.h
    src/callingconvention.h
    src/codegenerator.cpp
    src/codegenerator.h
    src/executionengine.cpp
    src/executionengine.h
    src/function.cpp
    src/function.h
    src/gc.cpp
    src/gc.h
    src/instructions.cpp
    src/instructions.h
    src/jit.cpp
    src/jit.h
    src/linux.cpp
    src/linux.h
    src/loader.cpp
    src/loader.h
    src/memory.h
    src/native.cpp
    src/native.h
    src/objects.cpp
    src/objects.h
    src/parser.cpp
    src/parser.h
    src/rtlibrary.cpp
    src/rtlibrary.h
    src/stackjit.cpp
    src/stackjit.h
    src/structmetadata.cpp
    src/structmetadata.h
    src/type.cpp
    src/type.h
    src/typechecker.cpp
    src/typechecker.h
    src/typeprovider.cpp
    src/typeprovider.h
    src/vmstate.cpp
    src/vmstate.h
    src/objectref.h
    src/objectref.cpp
    src/stackframe.h
    src/stackframe.cpp
    tests/runners/amd64test_runner.cpp
    tests/runners/vmtest_runner.cpp
    tests/amd64-test.h
    tests/vm-test.h)

add_executable(stackjit ${SOURCE_FILES})
