Runtime library
============

The runtime library consists of three parts:

* Runtime functions invoked by the VM.
* Native functions exposed to programs.
* Managed functions loaded by the VM.

###Runtime functions###
The runtime functions are functions such as invoking the garbage collector, creating objects, arrays and other low level functions. These functions can not be called by user programs.

###Native functions###
The native functions are implemented in the VM and are prefixed by "rt". These functions _should_ not be called, since there name may change in the future.

##Managed functions##
The managed functions either wraps runtime and native functions or provide implementation in managed code for runtime functions. These functions are prefixed by "std".

List of managed functions:
* `std::println(Int) Void`: Prints an int followed by a line break to standard output.
* `std.println(Float) Void`: Prints a float followed by a line break to standard output.
* `std.printchar(Char) Void`: Prints the given character.
* `std.println(Ref.Array[Char]) Void`: Prints the given string followed by a new line.
* `std.gc.collect() Void`: Invokes the garbage collector.
* `std.math.abs(Int) Int`: Computes the absolute function.
* `std.math.sqrt(Float) Float`: Computes the square root.
* `std.math.sin(Float) Float`: Computes the sine function.
* `std.math.cos(Float) Float`: Computes the cosine function.
