# Objects

### Arrays
Array instructions are bounds checked. When an array is created, the elements are default initialized to zero for primitive types and null for reference types.

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
A constructor works like a member function (the first argument is the 'this' reference).

#### Access modifiers
There are two type of access modifiers: `public` and `private`.  The default modifier is `public`.
Member function/field marked as `private` can only be called/accessed by member functions of the class.

An access modifier is an attribute with the name `AccessModifier`: `AccessModifier(value=private)`.

### Null ref
Dereferencing a null reference will result in a null reference error.
