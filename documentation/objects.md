#Objects#

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
