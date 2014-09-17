StackJIT
========

A simple JIT compiler for a stack-based VM.
<br>
The JIT part is based on a blog entry by [Josh Haberman](http://blog.reverberate.org/2012/12/hello-jit-world-joy-of-simple-jits.html).

###Branches###
Only branches within the current function is supported.

###Types###
The VM supports the given types: Array references (ArrayRef) and 32bits integers (Int).
It also supports the special type 'Void' which is only allowed as return type which indicates no return value.
Two types of reference types are supported, arrays and structures.
* Ref.Array[<Element type>].
* Ref.Struct.<Struct name>.

###Locals###
The VM supports per stack-frame locals. The locals are typed, but not explicitly typed. The type
of the local is determined the first time the local is stored (at compile time, not runtime). Loading
a local without type results in an error.
The number of locals a function has _should_ be defined in the beginning of the body with the following
syntax: `.locals <count>`. If the number of locals isn't defined, zero is choosen.

###Function calls###
Both native and user defined functions can be called. The arguments are popped from
the evaluation stack where the top operand is the last argument and so on. Only 4 arguments are supported.

###Functions###
Functions can be defined using the following syntax:
```
func <name>(<arg type 1> <arg type 2> ...) <return type>
{
    <function body>
}
```
When a function returns, there must be only _one_ (zero if void) operands on the evalutation stack.
If not, the program will not be executed.
There must be a function called 'main' which will be the entry point for the program.

####Main function####
The main function must have the following signature: `func main() Int`.
The returned value from the main function will be the output for the program.

##Instruction set##
* `PUSH <value>`: Pushes a 32-bits integer to the evaluation stack.
* `POP`: Pops the top value from the evalutation stack.
* `ADD`: Pops two operands, adds them and pushes the result to the evaluation stack.
* `SUB`: Pops two operands, subtracts the second one from the one and pushes the result to the evaluation stack.
* `MUL`: Pops two operands, multiplies them and pushes the result to the evaluation stack.
* `DIV`: Pops two operands, divides the first one with the second one and pushes the result to the evaluation stack.
* `LDLOC <local>`: Pushes the given local to the evaluation stack.
* `STLOC <local>`: Pops the top operand and stores it in the given local.
* `CALL <name>`: Calls the given function. The arguments are popped from the evaluation stack.
* `RET`: Returns from the current function, popping the return value from the evalutation stack.
* `LDARG <arg>`: Loads the given function argument and pushes it to the evaluation stack.
* `BR <target>`: Branches to target.
* `BEQ <target>`: Pops two operands, compares them and jump to target if equal.
* `BNE <target>`: Pops two operands, compares them and jump to target if not equal.
* `BGT <target>`: Pops two operands, compares them and jump to target if greater than.
* `BGE <target>`: Pops two operands, compares them and jump to target if greater or equal than.
* `BLT <target>`: Pops two operands, compares them and jump to target if less than.
* `BLE <target>`: Pops two operands, compares them and jump to target if less or equal than.
* `NEWARR <type>`: Pops the size of the array and creates a new array of the given type and pushes the reference on the stack.
* `STELEM <type>`: Pops the value, index and array reference from the stack and stores the value in the array.
* `LDELEM <type>`: Pops the index and array reference from the stack and loads the given element from the array.
* `LDLEN`: Pops the array reference from the stack and pushes the length of the array.

##Platforms##
Supports Linux x64.
<br>
Tested on Linux Mint 16 & 17 64-bits.
