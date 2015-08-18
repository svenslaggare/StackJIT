CC=clang++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=-std=c++11 -Wall

SRCDIR=src
OBJDIR=obj
EXECUTABLE=stackjit
FOLDERS = $(OBJDIR)/linux
FOLDERS = $(OBJDIR)/windows

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
HEADERS=$(wildcard $(SRCDIR)/*.h)

SOURCES += $(wildcard $(SRCDIR)/*/*.cpp)
HEADERS += $(wildcard $(SRCDIR)/*/*.h)

TEMPLATE_HEADERS=$(wildcard $(SRCDIR)/*.hpp)

_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(_OBJECTS))

TESTS_DIR=tests
TEST_RUNNERS_DIR=$(TESTS_DIR)/runners
AMD64_TEST_EXECUTABLE=amd64-test
VM_TEST_EXECUTABLE=vm-test
TEST_WITH_VALGRIND=0

all: $(OBJDIR) $(SOURCES) $(EXECUTABLE)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(FOLDERS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) $(TEMPLATE_HEADERS)
	$(CC) $(CFLAGS) $< -o $@

test: test-amd64 test-vm

valgrind-flags:
	$(eval TEST_WITH_VALGRIND = 1)

test-valgrind: valgrind-flags test-amd64 test-vm

test-amd64: $(TESTS_DIR)/amd64-test.h $(OBJDIR) $(OBJDIR)/amd64.o
	mkdir -p $(TEST_RUNNERS_DIR)
	cxxtestgen --error-printer -o $(TEST_RUNNERS_DIR)/amd64test_runner.cpp $(TESTS_DIR)/amd64-test.h
	$(CC) $(LDFLAGS) -o $(AMD64_TEST_EXECUTABLE) $(OBJDIR)/amd64.o -I $(CXXTEST) $(TEST_RUNNERS_DIR)/amd64test_runner.cpp
	./$(AMD64_TEST_EXECUTABLE)

test-vm: $(TESTS_DIR)/vm-test.h  $(OBJDIR) $(EXECUTABLE)
	mkdir -p $(TEST_RUNNERS_DIR)
	cxxtestgen --error-printer -o $(TEST_RUNNERS_DIR)/vmtest_runner.cpp $(TESTS_DIR)/vm-test.h
	$(CC) $(LDFLAGS) -o $(VM_TEST_EXECUTABLE) -I $(CXXTEST) $(TEST_RUNNERS_DIR)/vmtest_runner.cpp -DUSE_VALGRIND=$(TEST_WITH_VALGRIND)
	./$(VM_TEST_EXECUTABLE)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(TEST_RUNNERS_DIR)
	rm -f $(EXECUTABLE)
	rm -f $(AMD64_TEST_EXECUTABLE)
	rm -f $(VM_TEST_EXECUTABLE)
