StackJIT
========

A simple JIT compiler for a stack-based VM.
<br>
The JIT part is based on a blog entry by [Josh Haberman](http://blog.reverberate.org/2012/12/hello-jit-world-joy-of-simple-jits.html).

###Branches###
Only branches within the current function is supported.

###Types###
The VM supports the following types:

__Primitive types__
* Int: 32 bit integers.
* Float: 32 bits floating point.
* Bool: True or false.
* Void: Only allowed in return type which indicates no return value.

__Reference types__
* Arrays: `Ref.Array[<Element type>]`.
* Structs: `Ref.Struct.<Struct name>`.

###Locals###
The VM supports per stack-frame locals. The locals are typed where the type either is determined the first time the local is stored (at compile time, not runtime) or explicity: `.local <index> <type>`. Loading
a local without type results in an error.
The number of locals a function has _should_ be defined in the beginning of the body with the following
syntax: `.locals <count>`. If the number of locals isn't defined, zero is chosen.

###Function calls###
The arguments to call with are popped from the evaluation stack where the top operand is the last argument and so on. Only 4 arguments are supported. The VM supports function overloads. The signature of a function is defined as: `<name>(<type 1> <type 2> ...)`.

###Functions###
Functions can be defined using the following syntax:
```
func <name>(<arg type 1> <arg type 2> ...) <return type>
{
    <function body>
}
```
When a function returns, there must be only _one_ (zero if void) operand on the evalutation stack.

####Main function####
The main function _must_ and have the following signature: `func main() Int` and _must_ be defined.
The returned value from the main function will be the output for the program.

###Arrays###
The VM supports arrays of both primitive types and other reference types. When the arrays is created the elements are default initialized to zero for primitive types and null for reference types.

###Structs###
A structure is a reference type and can only be manipulated via references. The fields are referenced in the following way: `<struct name>::<field name>`. A structure is defined in the following way:
```
struct <name>
{
    <field 1> <type 1>
    <field 2> <type 1>
}
```

###Null ref###
Dereferencing a null reference will result in a null reference error. Both array and object instructions can result in a null reference error.

##Instruction set##
###Basic###
* `POP`: Pops the top value from the evalutation stack.

###Int & Float###
* `PUSHINT <value>`: Pushes a 32-bits integer to the evaluation stack.
* `PUSHFLOAT <value>`: Pushes a 32-bits floating point to the evaluation stack.

###Arithmetic###
* `ADD`: Pops two operands, adds them and pushes the result to the evaluation stack.
* `SUB`: Pops two operands, subtracts the second one from the one and pushes the result to the evaluation stack.
* `MUL`: Pops two operands, multiplies them and pushes the result to the evaluation stack.
* `DIV`: Pops two operands, divides the first one with the second one and pushes the result to the evaluation stack.

###Boolean###
* `PUSHTRUE`: Pushes the boolean value _true_ to the evaluation stack.
* `PUSHFALSE`: Pushes the boolean value false to the evaluation stack.
* `AND`: Pops two boolean operands, ands them and pushes the result to the evaluation stack.
* `OR`: Pops two boolean operands, ors them and pushes the result to the evaluation stack.
* `NOT`: Pops one boolean operand, inverts it and pushes the result to the evaluation stack.

###Locals###
* `LDLOC <local>`: Pushes the given local to the evaluation stack.
* `STLOC <local>`: Pops the top operand and stores it in the given local.

###Functions###
* `CALL <signature>`: Calls the given function. The arguments are popped from the evaluation stack.
* `RET`: Returns from the current function, popping the return value from the evalutation stack.
* `LDARG <arg>`: Loads the given function argument and pushes it to the evaluation stack.

###Branch###
* `BR <target>`: Branches to target.
* `BEQ <target>`: Pops two operands, compares them and jump to target if equal.
* `BNE <target>`: Pops two operands, compares them and jump to target if not equal.
* `BGT <target>`: Pops two operands, compares them and jump to target if greater than.
* `BGE <target>`: Pops two operands, compares them and jump to target if greater or equal than.
* `BLT <target>`: Pops two operands, compares them and jump to target if less than.
* `BLE <target>`: Pops two operands, compares them and jump to target if less or equal than.

###Compare###
* `CMPEQ`: Pops two operands, if the first operand is equal to the second pushes _true_ else _false_.
* `CMPNE`: Pops two operands, if the first operand is not equal to the second pushes _true_ else _false_.
* `CMPGT`: Pops two operands, if the first operand is greater than the second pushes _true_ else _false_.
* `CMPGE`: Pops two operands, if the first operand is greater than or equal to the second pushes _true_ else _false_.
* `CMPLT`: Pops two operands, if the first operand is less than the second pushes _true_ else _false_.
* `CMPLE>`: Pops two operands, if the first operand is less than or equal to the second pushes _true_ else _false_.

###Reference types###
* `PUSHNULL`: Pushes a null reference unto the operand stack.
* `GC`: Invokes the garbage collector. This instruction may be removed in the future.

###Arrays###
* `NEWARR <type>`: Pops the size of the array and creates a new array of the given type and pushes the reference on the stack.
* `STELEM <type>`: Pops the value, index and array reference from the stack and stores the value in the array.
* `LDELEM <type>`: Pops the index and array reference from the stack and loads the given element from the array.
* `LDLEN`: Pops an array reference from the stack and pushes the length of the array.

###Structs###
* `NEWOBJ <type>` Creates a new object of the given type and pushes the reference to the stack.
* `LDFIELD <field>` Pops a struct ref from the stack and loads a value from the given field pushing unto the stack.
* `STFIELD <field>` Pops a struct ref from the stack, a value and stores the value at the given field.

##Platforms##
Supports Linux x64.
At the moment, the VM only works properly compiled with G++. Using Clang++ gives strange errors when using the GC.
<br>
Tested on Linux Mint 16 & 17 64-bits.
