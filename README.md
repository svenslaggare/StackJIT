[![Build Status](https://travis-ci.org/svenslaggare/StackJIT.svg?branch=master)](https://travis-ci.org/svenslaggare/StackJIT)
StackJIT
========
A simple virtual machine for a stack-based assembler like language, featuring a JIT compiler, GC and object system.

##Running##
To run the VM, supply a program via stdin:
```
./stackjit < programs/basic/program.txt
```

###Options###
* `-d` or `--debug`: Enables debugging. This is the default mode.
* `-psf` or `--print-stack-frame`: Prints info about a stack frame before a functions returns. Requires debugging to be enabled.
* `-ogc` or `--output-generated-code`: Outputs the generated machine code for the functions. The output can be viewed using _objdump_: `objdump -D -M intel -b binary -mi386 -Mx86-64 <file name>`.
* `-pfg` or `--print-function-generation`: Prints status when functions are generated. Requires debugging to be enabled.
* `-plp` or `--print-lazy-patching`: Prints when lazy compiled functions that are called are patched. Requires debugging to be enabled.
* `-lc <enable>` or `--lazy-compile <enable>`: Enables lazy compilation of functions.
* `-t` or `--test`: Enables test mode, which loads test related libraries.
* `-ngc` or `--no-gc`: Disables garbage collection. The GC can still be used by calling the runtime function.
* `-i <library file>`: Loads a library.

##Build##
To build on Linux:
```
make all
```
To run tests (requires [CXXTest](http://cxxtest.com/)):
```
make test
```

To build on Windows:

Open the VS 2015 solution in the Windows folder.
The tests requires [CXXTest](http://cxxtest.com/), unpacked at `C:/CXXTest`.

##Supported platforms##
Supports Linux x64 and Windows 64. The VM has only been tested on Linux Mint 17 and Windows 7.

##Documentation##
See the [documentation folder](https://github.com/svenslaggare/StackJIT/tree/master/documentation) for documentation about the features of the VM.
