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
* `-nd` or `--no-debug`: Disables debugging.
* `-ptc` or `--print-type-checking`: Prints the type checking for functions. Requires debugging to be enabled.
* `-psf` or `--print-stack-frame`: Prints info about a stack frame before a functions returns. Requires debugging to be enabled..
* `-ogc` or `--output-generated-code`: Outputs the generated machine code for the functions. The output can be viewed using _objdump_: `objdump -D -M intel -b binary -mi386 -Mx86-64 <file name>`.
* `-ngc` or `--no-gc`: Disables garbage collection. The GC can still be used by the explicit instruction.
* `-i <library file>`: Loads a library.

##Build##
At the moment, the VM only works properly when compiled with G++. Using Clang++ gives strange errors when using the GC.

To build:
```
make all
```
To run tests (requires [CXXTest](http://cxxtest.com/)):
```
make test
```

##Supported platforms##
Supports Linux x64. The VM has only been tested on Linux Mint 17.

##Documentation##
See the [documentation folder](https://github.com/svenslaggare/StackJIT/tree/master/documentation) for documentation about the features of the VM.
