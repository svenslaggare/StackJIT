CC=clang++
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=stackjit.cpp instructions.cpp program.cpp parser.cpp standardlibrary.cpp codegenerator.cpp typechecker.cpp amd64.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=stackjit

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

test: amd64-test.cpp 
	$(CC) -std=c++11 $< amd64.cpp -o $@
	./$@
	
clean:
	rm -rf *o $(EXECUTABLE)