#Instruction set#
Defines the instruction set used by the VM.

###Basic###
* `POP`: Pops the top value from the evaluation stack.

###Int & Float###
* `PUSHINT <value>`: Pushes a 32-bits integer to the evaluation stack.
* `PUSHFLOAT <value>`: Pushes a 32-bits floating point to the evaluation stack.
* `CONVINTTOFLOAT`: Pops an int from the evaluation stack and converts it to a float, pushing the result to the evaluation stack.
* `CONVFLOATTOINT`: Pops a float from the evaluation stack and converts it to a int, pushing the result to the evaluation stack.

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
* `CALLINST <struct name>::<signature>`: Calls the given member function. The first argument must be a reference of the called Struct. The arguments are popped from the evaluation stack.
* `RET`: Returns from the current function, popping the return value from the evaluation stack.
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
* `CMPLE`: Pops two operands, if the first operand is less than or equal to the second pushes _true_ else _false_.

###Reference types###
* `PUSHNULL`: Pushes a null reference unto the operand stack.

###Arrays###
* `NEWARR <type>`: Pops the size of the array and creates a new array of the given type and pushes the reference on the stack.
* `STELEM <type>`: Pops the value, index and array reference from the stack and stores the value in the array.
* `LDELEM <type>`: Pops the index and array reference from the stack and loads the given element from the array.
* `LDLEN`: Pops an array reference from the stack and pushes the length of the array.

###Structs###
* `NEWOBJ <type>` Creates a new object of the given type and pushes the reference to the stack.
* `LDFIELD <field>` Pops a struct ref from the stack and loads a value from the given field pushing unto the stack.
* `STFIELD <field>` Pops a struct ref from the stack, a value and stores the value at the given field.

###String###
* `LDSTR <string>` Creates a new string and pushes the reference to the string to the evaluation stack.
* `PUSHCHAR <char value>` Pushes a char to the evaluation stack.
