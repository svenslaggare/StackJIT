StackJIT
========

A simple JIT compiler for a stack-based VM.
<br>

###Execution###
All programs must always end with _one_ operand on the evaluation stack, which will be printed
to the stdout.

###Locals###
The VM supports 8 locals, indexed from 0 to 7.

##Instruction set##
* `PUSH <value>`: Pushes a 32-bits integer to the evaluation stack.
* `ADD`: Pops the two operands, adds them and pushes to the evaluation stack.
* `SUB`: Pops the two operands, subtracts the second one from the one and pushes to the evaluation stack.
* `MUL`: Pops the two operands, multiplies them and pushes to the evaluation stack.
* `LDLOC <local>`: Pushes the given local to the evaluation stack.
* `STLOC <local>`: Pops the top operand and stores it in the given local.

##Platforms##
Supports Linux x64.
<br>
Tested on Linux Mint 16 & 17 64-bits.
