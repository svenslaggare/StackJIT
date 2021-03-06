# Functions

### Locals
Each stack frame supports _locals_, which works like variables. The locals are typed where the type either is determined the first time the local is stored (at compile time, not runtime) or explicitly using: `.local <index> <type>`.

The number of locals a function has _should_ be defined in the beginning of the body with the following
syntax: `.locals <count>`. If the number of locals isn't defined, zero is chosen.

### Function calls
The call arguments are popped from the evaluation stack, where the top operand is the last argument. The signature of a function is defined as: `<name>(<type 1> <type 2> ...)`.

### Syntax
Functions are defined using the following syntax:
```
func <name>(<arg type 1> <arg type 2> ...) <return type>
{
    <function body>
}
```
When a function returns, there must be only _one_ (zero if void) operand on the evaluation stack. The last instruction of a function body _must_ be the return instruction.

### Main function
The main function _must_ have the following signature: `main() Int` and _must_ be defined if the assembly is a program.
The returned value from the main function will be the output of the program.

### Member functions
A member function works like a normal function except that the first argument (argument 0) is bound to the "this reference" of the class. The signature for a member function is: `<class name>::<name>(<arg type 1> <arg type 2> ...)`.

Member functions are defined using:
```
member <class name>::<name>(<arg type 1> <arg type 2> ...) <return type>
{
    <function body>
}
```
