Current Garbage Collector Design
================================
The current GC uses a mark-and-compact collector using the Lisp 2 algorithm.

## Collection happens
A collection happens when 1000 objects (or supplied via a command line argument) has been allocated. This needs to be changed so that collections when the GC needs more free space.

## Allocator
The allocator is implemented using the "bump the pointer" technique. This works by when a new object needs to be allocated, the current next pointer is returned as the location of the new object, and is incremented after.

## Heap
The heap is of fixed size (10 MB), and will not grow if the heap runs out of space.

New Garbage Collector Design
============================
To design a new garbage collector.

Design goals:
* Generational (young and old generation).
* Compacting.
* Growing.
* Change when collection happens

## Generational
The new garbage collector will have two generations: young and old. The generations will represented by a partition of the heap. The young generation will be placed before the old generation.

### Young Generation
The newly allocated objects will be placed in the young generation. If an object survives `x` number of collections, it will be promoted to the old generation.
The roots will be the same as in existing code + the old objects that has references into the young generation.
From the start, this generation will use a compacting collector. In the future, this generation may be changed to using a copying collector.

### Old Generation
Will use a compacting collector.

### Intergenerational references
Will use the card marking algorithm.
