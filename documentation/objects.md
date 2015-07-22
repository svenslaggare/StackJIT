#Objects#

###Arrays###
The VM supports arrays of both primitive types and other reference types. When the arrays is created the elements are default initialized to zero for primitive types and null for reference types.

###Classes###
A class is a reference type and can only be manipulated via references. The fields are referenced in the following way: `<class name>::<field name>`. A class is defined in the following way:
```
class <name>
{
    <field 1> <type 1>
    <field 2> <type 1>
}
```

To create a class, a constructor must be called. A constructor is defined as:
```
member <name>::.constructor(<arg type 1> <arg type 1>) Void
{

}
```
A constructor works like a member function (eg arg 0 is the 'this' reference).

###Null ref###
Dereferencing a null reference will result in a null reference error. Both array and object instructions can result in a null reference error.
