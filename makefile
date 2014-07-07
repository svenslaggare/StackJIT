CC=clang++
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=stackjit.cpp instructions.cpp parser.cpp standardlibrary.cpp codegenerator.cpp amd64.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=stackjit

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)