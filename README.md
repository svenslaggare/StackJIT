[![Linux Build Status](https://travis-ci.org/svenslaggare/StackJIT.svg?branch=master)](https://travis-ci.org/svenslaggare/StackJIT) [![Windows Build Status](https://ci.appveyor.com/api/projects/status/nqt3cks6w2kqfny8?svg=true)](https://ci.appveyor.com/project/svenslaggare/stackjit)
StackJIT
========
Simple multi-platform virtual machine for a stack-based assembler language, featuring a JIT compiler, GC and object system.

## Running
To run the VM, supply a program via stdin:
```
./stackjit < programs/basic/program.txt
```

### Options
* `-d` or `--debug`: Enables debugging.
* `-ogc` or `--output-generated-code`: Outputs the generated machine code. The output can be viewed using _objdump_: `objdump -D -M intel -b binary -mi386 -Mx86-64 <file name>`.
* `-t` or `--test`: Enables test mode, which loads test related libraries.
* `-ngc` or `--no-gc`: Disables garbage collection. The GC can still be used by calling the runtime function.
* `-i <library file>`: Loads a library.

## Supported platforms
Supports Linux x64 and Windows x64.

## Build
### Linux
Requirments:
* C++11 compiler.
* [CXXTest](http://cxxtest.com/) for tests.

To build:
```
make all
```
To run tests:
```
make test
```

### Windows
Requirements:
* Visual Studio 2015.
* CMake.
* [CXXTest](http://cxxtest.com/) for tests.

The following command installs CxxTest:
```
git clone -q --branch=master https://github.com/svenslaggare/CxxTest.git C:\CXXTest
set PATH=%PATH%;C:\CXXTest\bin
```

To create the solution file run:
```
mkdir Windows
cd Windows
cmake -G "Visual Studio 14 2015 Win64" ..\
```

## Documentation
See the [documentation folder](https://github.com/svenslaggare/StackJIT/tree/master/documentation).
