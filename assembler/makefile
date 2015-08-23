CC=clang++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=-std=c++11 -Wall

SRCDIR=src
OBJDIR=obj
EXECUTABLE=stackasm

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
HEADERS=$(wildcard $(SRCDIR)/*.h)

TEMPLATE_HEADERS=$(wildcard $(SRCDIR)/*.hpp)

_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(_OBJECTS))

TESTS_DIR=tests
TEST_RUNNERS_DIR=$(TESTS_DIR)/runners
TEST_EXECUTABLE=test

all: $(OBJDIR) $(SOURCES) $(EXECUTABLE)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) $(TEMPLATE_HEADERS)
	$(CC) $(CFLAGS) $< -o $@

test: $(TESTS_DIR)/assembler-test.h $(OBJDIR) $(EXECUTABLE)
	mkdir -p $(TEST_RUNNERS_DIR)
	cxxtestgen --error-printer -o $(TEST_RUNNERS_DIR)/assembler-test-runner.cpp $(TESTS_DIR)/assembler-test.h
	$(CC) $(LDFLAGS) -o $(TEST_EXECUTABLE) -I $(CXXTEST) $(TEST_RUNNERS_DIR)/assembler-test-runner.cpp
	./$(TEST_EXECUTABLE)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(TEST_RUNNERS_DIR)
	rm -f $(EXECUTABLE)
	rm -f $(TEST_EXECUTABLE)
