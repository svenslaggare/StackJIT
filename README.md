StackJIT
========

A simple JIT compiler for a stack-based VM.
<br>
The JIT part is based on a blog entry by [Josh Haberman](http://blog.reverberate.org/2012/12/hello-jit-world-joy-of-simple-jits.html).

###Branches###
Only branches within the current function is supported.

###Locals###
The VM supports per stack-frame locals. Currently the number of
locals per frame is hardcoded to four (indexed 0-3).

###Types###
The VM supports the given types: Array references and integers (32 bits). Currently, types other
than int are only supported within method body which means that only ints can be arguments to functions
and return values. This will be fixed in the future. The types are checked at code generation.

###Function calls###
Both native and user defined functions can be called. The arguments are popped from
the evaluation stack where the top operand is the last argument and so on. Only 4 arguments are supported.

###Functions###
Functions can be defined using the following syntax:
```
func <name> <numargs>
<function body>
endfunc
```
There is no "return" instruction atm, but all functions must end with _one_
operand at the evaluation stack which will be the return value.
Functions not enclosed within a function definition is automatically added
to the 'main' function which is the entry point for the program.
The returned value will be the output for the program.

##Instruction set##
* `PUSH <value>`: Pushes a 32-bits integer to the evaluation stack.
* `ADD`: Pops two operands, adds them and pushes the result to the evaluation stack.
* `SUB`: Pops two operands, subtracts the second one from the one and pushes the result to the evaluation stack.
* `MUL`: Pops two operands, multiplies them and pushes the result to the evaluation stack.
* `DIV`: Pops two operands, divides the first one with the second one and pushes the result to the evaluation stack.
* `LDLOC <local>`: Pushes the given local to the evaluation stack.
* `STLOC <local>`: Pops the top operand and stores it in the given local.
* `CALL <name>`: Calls the given function. The arguments are popped from the evaluation stack.
* `LDARG <arg>`: Loads the given function argument and pushes it to the evaluation stack.
* `BR <target>`: Branches to target.
* `BEQ <target>`: Pops two operands, compares them and jump to target if equal.
* `BNE <target>`: Pops two operands, compares them and jump to target if not equal.
* `BGT <target>`: Pops two operands, compares them and jump to target if greater than.
* `BGE <target>`: Pops two operands, compares them and jump to target if greater or equal than.
* `BLT <target>`: Pops two operands, compares them and jump to target if less than.
* `BLE <target>`: Pops two operands, compares them and jump to target if less or equal than.
* `NEWARR`: Pops the size of the array and creates a new array and pushes the reference on the stack.
* `STELEM`: Pops the value, index and array reference from the stack and stores the value in the array.
* `LDELEM`: Pops the ndex and array reference from the stack and loads the given element from the array.

##Platforms##
Supports Linux x64.
<br>
Tested on Linux Mint 16 & 17 64-bits.
