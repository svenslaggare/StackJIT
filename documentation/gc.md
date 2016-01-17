New Garbage Collector Design
============================
To design a complete new garbage collector and memory allocator.

Design goals:
* Genertional (young and old generation).
* Compacting.
* New allocator (instead of using new/delete).
* New object layout.

## Genertional
The new garbage collector will have two generations: young and old. The generations will represented by partion the heap.
The young generation will be placed before the old generation.

### Young Generation
The newly allocated objects will be placed in the young generation. If an object surves `x` number of collections, it will be promoted to the old generation.
The roots will be the same as in existing code + the old objects that has references into the young generation.
From the start, this generation will use a compacting collector. In the future, this generation may be changed to using a copying collector. 

### Old Generation
Will use a compacting collector.

### Intergenertional references
Will use the card marking algorithm.

## Compaction
The GC will use an compacting collector, maybe the Lisp 2 algorithm. However, this will only be implemented when the other parts has been implemented.

## New allocator
Implementing the new garbage collector will require a new memory allocatr, that does not use new/delete. The easiset solution is to use the "bump the pointer" algortihm, 
which work great with a compacting collector.

##New Object Layout
Instead of storing the object information in a handle, this information will be moved inside the object. The object layout will contain: pointer to the type of the object, GC information (mark bit, number of survived generations), and the data istelf.
Like the following: |pointer to type (8 bytes)|GC information: mark bit + num survived generations (1 byte)|object data|.

Improved Garbage Collector Design
=================================
To improve the existing garbage collector, reusing most of the code.

Design goals:
* Genertional (young and old generation).
* Reuse existing code.

## Genertional
The improved collector will contain two generations: young and old.
The generations are represented by lists, with each list containing the objects that belongs to the generation.

### Allocating
The object will be allocated as normal and placed in the young generation.

### Collection
__Young generation__: Roots same as in existing code + the old objects that has references into the young generation.
If a reference from the young goes to the old, it's ignored.

__Old generation__: Roots same as in existing code + the young objects that has references into the old generation?.
If a reference from the old goes to the young, it's ignored.

## Intergenertional references
Either scanning the old generations, or implementing card marking (this will require changes to the CodeGenerator).

### Object promotion
Implemented by moving an object from one list to another.

## Reusing code
Nothing in the CodeGenerator and JIT classes needs to be changed. It's only the GarbageCollector class that needs to be changed.


