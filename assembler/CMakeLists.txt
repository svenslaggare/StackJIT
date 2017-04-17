cmake_minimum_required(VERSION 3.3)
project(StackAssembler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/stackasm.cpp
        src/parser.cpp
        src/parser.h
        src/assembler.cpp
        src/assembler.h
        src/bytecodegenerator.cpp
        src/bytecodegenerator.h
        src/bytecodeparser.cpp
        src/bytecodeparser.h
        src/imageloader.cpp
        src/imageloader.h)
add_executable(StackAssembler ${SOURCE_FILES})