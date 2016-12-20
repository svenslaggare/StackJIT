Garbage Collector
================================
The garbage collector uses a mark-and-compact collector using the Lisp 2 algorithm, and divides the heap into an young and old generation.

## When collection happens
A collection happens when 1000 objects (or supplied via a command line argument) has been allocated. This needs to be changed so that collections when the GC needs more free space.

## Allocator
The allocator is implemented using the "bump the pointer" technique. This works by when a new object needs to be allocated, the current next pointer is returned as the location of the new object, and is incremented after.

## Heap size
The heap size is fixed, and will not grow if the heap runs out of space. The size of the different generations are:
* Young: 4 MB
* Old: 8 MB

## Generations
There exists two generations: young and old. If an object has survived 5 collections, it will be promoted to the old generation. To track references between generation, the card marking algorithm is used. The size of a card is 1024 bytes.

## GC Info
The format for the GC info is the following:

![](images/GCInfo.png "GC info format")
