# Config
CXXC=clang++
CXXFLAGS=-std=c++11 -Wall

SRC_DIR=src
OBJ_DIR=obj
TESTS_DIR=tests
EXECUTABLE=stackjit
FOLDERS=$(OBJ_DIR)/linux $(OBJ_DIR)/windows $(OBJ_DIR)/compiler $(OBJ_DIR)/loader $(OBJ_DIR)/runtime $(OBJ_DIR)/test $(OBJ_DIR)/type

ASSEMBLER_DIR=assembler
RTLIB=rtlib

TEST_WITH_VALGRIND=0

WINDOWS_DIR=Windows2

# Rules
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
HEADERS=$(wildcard $(SRC_DIR)/*.h)

SOURCES += $(wildcard $(SRC_DIR)/*/*.cpp)
HEADERS += $(wildcard $(SRC_DIR)/*/*.h)

TEMPLATE_HEADERS=$(wildcard $(SRC_DIR)/*.hpp)

_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(_OBJECTS))

TEST_RUNNERS_DIR=$(TESTS_DIR)/runners

MAIN_OBJ=$(OBJ_DIR)/$(EXECUTABLE).o
TEST_OBJECTS=$(filter-out $(MAIN_OBJ), $(OBJECTS))

TESTS=$(wildcard $(TESTS_DIR)/*-test.h)
TEST_EXECUTABLES=$(patsubst $(TESTS_DIR)/%.h,$(TEST_RUNNERS_DIR)/%, $(TESTS))

RTLIB_FILES=$(wildcard $(RTLIB)/*.sbc)
RTLIB_OUT=$(RTLIB)/rtlib.simg

$(TEST_RUNNERS_DIR):
	mkdir $(TEST_RUNNERS_DIR)

all: $(OBJ_DIR) $(SOURCES) $(EXECUTABLE) $(RTLIB_OUT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(FOLDERS)

$(EXECUTABLE): $(OBJECTS)
	$(CXXC) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) $(TEMPLATE_HEADERS)
	$(CXXC) -c $(CXXFLAGS) $< -o $@

$(RTLIB_OUT): $(RTLIB_FILES)
	make -C $(ASSEMBLER_DIR) all
	$(ASSEMBLER_DIR)/stackasm -o rtlib/rtlib.simg $(RTLIB_FILES)

valgrind-flags:
	$(eval TEST_WITH_VALGRIND = 1)

test-valgrind: valgrind-flags test

test: $(TEST_RUNNERS_DIR) $(TEST_EXECUTABLES)

$(TEST_RUNNERS_DIR)/%: $(TESTS_DIR)/%.h $(OBJ_DIR) $(EXECUTABLE) $(RTLIB_OUT) $(TEST_OBJECTS)
	cxxtestgen --error-printer -o $@-runner.cpp $<
	$(CXXC) $(CXXFLAGS) -o $@ -I $(CXXTEST) $(TEST_OBJECTS) $@-runner.cpp -DUSE_VALGRIND=$(TEST_WITH_VALGRIND)
	./$@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_RUNNERS_DIR)
	rm -f $(EXECUTABLE)
	make -C $(ASSEMBLER_DIR) clean
	rm -f $(RTLIB_OUT)
