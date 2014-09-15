CC=clang++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=
SOURCES=stackjit.cpp instructions.cpp program.cpp parser.cpp standardlibrary.cpp codegenerator.cpp type.cpp typechecker.cpp amd64.cpp objects.cpp
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(SOURCES:.cpp=.h)
EXECUTABLE=stackjit

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#.cpp.o: $(HEADERS)
#	$(CC) $(CFLAGS) $< -o $@
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@	

test: amd64-test.cpp 
	$(CC) -std=c++11 $< amd64.cpp -o $@
	./$@
	
clean:
	rm -rf *o $(EXECUTABLE)