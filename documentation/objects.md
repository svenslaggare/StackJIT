# Objects

### Arrays
The arrays are bounds checked and when an array is created, the elements are default initialized to zero for primitive types and null for reference types.

### Classes
Classes are references types may consists of both member function and fields. A field are referenced in the following way: `<class name>::<field name>`. A class are defined in the following way:
```
class <name>
{
    <field 1> <type 1>
    <field 2> <type 1>
}
```

To create an instance of a class, a constructor must be called. Constructors are defined as:
```
member <name>::.constructor(<arg type 1> <arg type 1>) Void
{

}
```
A constructor works like a member function (the first argument (arg 0) is the 'this' reference).

###Null ref###
Dereferencing a null reference will result in a null reference error. Both array and object instructions can result in a null reference error.
