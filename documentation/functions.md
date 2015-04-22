#Functions#

###Branches###
Only branches within the current function is supported.

###Locals###
The VM supports per stack-frame locals. The locals are typed where the type either is determined the first time the local is stored (at compile time, not runtime) or explicity: `.local <index> <type>`. Loading
a local without type results in an error.
The number of locals a function has _should_ be defined in the beginning of the body with the following
syntax: `.locals <count>`. If the number of locals isn't defined, zero is chosen.

###Function calls###
The arguments to call with are popped from the evaluation stack where the top operand is the last argument and so on. Only 6 arguments are supported. The VM supports function overloads. The signature of a function is defined as: `<name>(<type 1> <type 2> ...)`.

###Functions###
Functions can be defined using the following syntax:
```
func <name>(<arg type 1> <arg type 2> ...) <return type>
{
    <function body>
}
```
When a function returns, there must be only _one_ (zero if void) operand on the evalutation stack.

__Main function__

The main function _must_ and have the following signature: `main() Int` and _must_ be defined.
The returned value from the main function will be the output for the program.

###Member functions###
A member function works like a normal function except that fist argument (arg 0) is bound to the "this reference". The signature for a member function is: `<struct name>::<name>(<type 1> <type 2> ...)`. A member function is defined as:
```
member <struct name>::<name>(<arg type 1> <arg type 2> ...) <return type>
{
    <function body>
}
```
