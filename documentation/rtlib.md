Runtime library
==============

The runtime library consists of three parts:

* Runtime functions invoked by the VM.
* Native functions exposed to programs.
* Managed functions loaded by the VM.

### Runtime functions
The runtime functions are functions such as invoking the garbage collector, creating objects, arrays and other low level functions. These functions can not be called by user programs.

### Native functions
The native functions are implemented in the VM and are exposed as normal functions.

### Managed functions
The managed functions either wraps runtime functions or provide implementation in managed code for runtime functions.

## List of functions

### I/O
* `std.print(Int) Void`: Prints an int followed to standard output.
* `std.print(Float) Void`: Prints a float followed to standard output.
* `std.print(Bool) Void`: Prints a bool followed to standard output.
* `std.print(Char) Void`: Prints the given char to standard output.
* `std.println(Int) Void`: Prints an int followed by a line break to standard output.
* `std.println(Float) Void`: Prints a float followed by a line break to standard output.
* `std.println(Bool) Void`: Prints a bool followed by a line break to standard output.
* `std.println(Char) Void`: Prints a char followed by a line break to standard output
* `std.println(Ref.Array[Char]) Void`: Prints the given char array followed by a new line.

### Math
* `std.math.abs(Int) Int`: Computes the absolute value.
* `std.math.sqrt(Float) Float`: Computes the square root.
* `std.math.sin(Float) Float`: The sine function.
* `std.math.cos(Float) Float`: The cosine function.

### System
* `std.gc.collect() Void`: Invokes the garbage collector.

## List of classes

### std.String
An immutable string.

__Fields__
* `chars Ref.Array[Char]`: The underlying char array.

__Member functions__
* `length() Int`: Returns the length of the string.
* `charAt(Int) Char`: Returns the character at the given index.
* `concat(Ref.Class.std.String) Ref.Class.std.String`: Concatenates the current string with the given string, returning a new string.
