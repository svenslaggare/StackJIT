CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=-std=c++11

SRCDIR=src
OBJDIR=obj
EXECUTABLE=stackjit

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
HEADERS=$(wildcard $(SRCDIR)/*.h)

_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(_OBJECTS))

TESTS_DIR=tests
TEST_RUNNERS_DIR=$(TESTS_DIR)/runners
AMD64_TEST_EXECUTABLE=amd64-test
VM_TEST_EXECUTABLE=vm-test

all: $(OBJDIR) $(SOURCES) $(EXECUTABLE)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@	

test: test-amd64 test-vm

test-amd64: $(TESTS_DIR)/amd64-test.cpp src/amd64.cpp src/amd64.h
	$(CC) -std=c++11 $(TESTS_DIR)/amd64-test.cpp src/amd64.cpp -o $(AMD64_TEST_EXECUTABLE)
	./$(AMD64_TEST_EXECUTABLE)

test-vm: $(TESTS_DIR)/vm-test.h
	mkdir -p $(TEST_RUNNERS_DIR)
	cxxtestgen --error-printer -o $(TEST_RUNNERS_DIR)/vmtest_runner.cpp $(TESTS_DIR)/vm-test.h
	$(CC) $(LDFLAGS) -o $(VM_TEST_EXECUTABLE) -I $(CXXTEST) $(TEST_RUNNERS_DIR)/vmtest_runner.cpp
	./$(VM_TEST_EXECUTABLE)

clean:
	rm -rf $(OBJDIR)
	rm $(EXECUTABLE)
	rm $(AMD64_TEST_EXECUTABLE)
	rm $(VM_TEST_EXECUTABLE)