Runtime library
============

The runtime library consists of three parts:

* Runtime functions invoked by the VM.
* Native functions exposed to programs.
* Managed functions loaded by the VM.

###Runtime functions###
The runtime functions are functions such as invoking the garbage collector, creating objects, arrays and other low level functions. These functions can not be called by user programs.

###Native functions###
The native functions are implemented in the VM and are exposed as normal functions.

###Managed functions###
The managed functions either wraps runtime and native functions or provide implementation in managed code for runtime functions.

##Callable runtime functions##
* `std.print(Int) Void`: Prints an int followed to standard output.
* `std.print(Float) Void`: Prints a float followed to standard output.
* `std.println(Int) Void`: Prints an int followed by a line break to standard output.
* `std.println(Float) Void`: Prints a float followed by a line break to standard output.
* `std.printchar(Char) Void`: Prints the given character.
* `std.println(Ref.Array[Char]) Void`: Prints the given string followed by a new line.
* `std.gc.collect() Void`: Invokes the garbage collector.
* `std.math.abs(Int) Int`: Computes the absolute value.
* `std.math.sqrt(Float) Float`: Computes the square root.
* `std.math.sin(Float) Float`: The sine function.
* `std.math.cos(Float) Float`: The cosine function.
