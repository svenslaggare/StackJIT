#Types#
The VM supports the following types:

###Primitive types###
* Int: 32 bit integer.
* Float: 32 bits floating point.
* Bool: True or false.
* Char: 8 bits integer.
* Void: Only allowed in return type which indicates no return value.

###Reference types###
* Arrays: `Ref.Array[<Element type>]`.
* Classes: `Ref.Class.<Class name>`.

###Strings###
A string is of type `Ref.Array[Char]`, this may change in the future. The syntax for declaring a string is `"string value"`.
