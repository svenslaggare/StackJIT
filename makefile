CC=clang++
CFLAGS=-c -std=c++11
EXECUTABLE=stackjit

all: stackjit

stackjit: stackjit.o
	$(CC) stackjit.o -o $(EXECUTABLE)

stackjit.o: stackjit.cpp
	$(CC) $(CFLAGS) stackjit.cpp

clean:
	rm -rf *o $(EXECUTABLE)