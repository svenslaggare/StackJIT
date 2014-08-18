StackJIT
========

A simple JIT compiler for a stack-based VM.
<br>
The JIT part is based on a blog entry by [Josh Haberman](http://blog.reverberate.org/2012/12/hello-jit-world-joy-of-simple-jits.html).

###Execution###
All programs must always end with _one_ operand on the evaluation stack, which will be printed
to the stdout.

###Locals###
The VM supports per stack-frame locals. Currently the number of
locals per frame is hardcoded to four (indexed 0-3).

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

##Instruction set##
* `PUSH <value>`: Pushes a 32-bits integer to the evaluation stack.
* `ADD`: Pops two operands, adds them and pushes the result to the evaluation stack.
* `SUB`: Pops two operands, subtracts the second one from the one and pushes the result to the evaluation stack.
* `MUL`: Pops two operands, multiplies them and pushes the result to the evaluation stack.
* `DIV`: Pops two operands, divides the first one with the second one and pushes the result to the evaluation stack.
* `LDLOC <local>`: Pushes the given local to the evaluation stack.
* `STLOC <local>`: Pops the top operand and stores it in the given local.
* `CALL <name> <numargs>`: Calls the given function with the given amount of arguments. The arguments are popped from the evaluation stack.
* `LDARG <arg>`: Loads the given function argument and pushes it to the evaluation stack.
* `BR <target>`: Branches to target.
* `BEQ <target>`: Pops two operands, compares them and jump to target if equal.
* `BNE <target>`: Pops two operands, compares them and jump to target if not equal.
* `BGT <target>`: Pops two operands, compares them and jump to target if greater than.
* `BGE <target>`: Pops two operands, compares them and jump to target if greater or equal than.
* `BLT <target>`: Pops two operands, compares them and jump to target if less than.
* `BLE <target>`: Pops two operands, compares them and jump to target if less or equal than.


##Platforms##
Supports Linux x64.
<br>
Tested on Linux Mint 16 & 17 64-bits.
