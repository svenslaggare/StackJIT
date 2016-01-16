# Config
CXXC=clang++
CXXFLAGS=-std=c++11 -Wall

SRC_DIR=src
OBJ_DIR=obj
TESTS_DIR=tests
EXECUTABLE=stackjit

ASSEMBLER_DIR=assembler
RTLIB_DIR=rtlib

TEST_WITH_VALGRIND=0

# Rules
_FOLDERS=$(sort $(dir $(wildcard $(SRC_DIR)/*/)))
FOLDERS=$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(_FOLDERS))

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

RTLIB_FILES=$(wildcard $(RTLIB_DIR)/*.sbc)
RTLIB_OUT=$(RTLIB_DIR)/rtlib.simg

all: $(OBJ_DIR) $(SOURCES) $(EXECUTABLE) $(RTLIB_OUT)

$(TEST_RUNNERS_DIR):
	mkdir $(TEST_RUNNERS_DIR)

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
