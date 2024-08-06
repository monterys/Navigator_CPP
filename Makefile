CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -fno-elide-constructors
LDFLAGS = -lgtest -lpthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GENINFOFLAGS = --no-external -c -d . --exclude `pwd`/tests_\* --exclude `pwd`/my_matrix.cc

PROJECTNAME = simple_navigator
CONSOLENAME = simple_navigator
SRC_DIR = .
SRC_TEST_DIR = .
OBJ_DIR = obj
GCOV_HTML_DIR = report

LIBS = my_graph my_graph_algorithms my_stack my_queue
LIBS_A = $(addsuffix .a, $(LIBS))
LIBS_INCLUDE_TARGET = my_stack my_queue
LIBS_INCLUDE = my_stack.a my_queue.a

SRC = my_graph.cc my_graph_algorithms.cc my_ant_algorithm.cc my_matrix.cc
SRC_CONSOLE = console_application.cc my_ant_algorithm.cc my_matrix.cc
SRC_TEST = $(wildcard $(SRC_TEST_DIR)/tests_*.cc)
SRC_EXECUTABLE = $(SRC_TEST) $(SRC_DIR)/$(SRC) $(LIBS_INCLUDE)

EXECUTABLE = $(addprefix test_, $(PROJECTNAME))
COVERAGE_INFO = $(addsuffix .info, $(PROJECTNAME))

OS := $(shell uname)

ifeq ($(OS),Darwin)
	GENINFOFLAGS += --ignore-errors mismatch --ignore-errors inconsistent
endif

all: $(LIBS)

clean:
	@echo '[34mCleaning up ...[0m'
	rm -rf *.o $(EXECUTABLE) $(OBJ_DIR) $(GCOV_HTML_DIR) *.gc* *.dSYM *.dot

test: clean $(EXECUTABLE)
	@echo "[34mRunning tests...[0m"
	./$(EXECUTABLE)

$(LIBS): %: $(OBJ_DIR)/%.o
	@echo "[34mBuilding the static library: $@.a ...[0m"
	ar rc $@.a $(OBJ_DIR)/$@.o
	ranlib $@.a

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo '[34mCompiling the library source file $^ ...[0m'
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(LIBS_INCLUDE_TARGET)
	@echo "[34mBuilding tests...[0m"
	$(CC) $(CFLAGS) $(SRC_EXECUTABLE) -o $@ $(LDFLAGS) $(GCOVFLAGS) $(I)

console: $(LIBS)
	$(CC) $(CFLAGS) $(SRC_CONSOLE) $(LIBS_A) -o $(CONSOLENAME)
	./$(CONSOLENAME)

gcov_report: test
	@echo "[34mGenerating HTML coverage report...[0m"
	@mkdir -p $(GCOV_HTML_DIR)

	lcov -t $(EXECUTABLE) -o $(GCOV_HTML_DIR)/$(COVERAGE_INFO) $(GENINFOFLAGS)
	genhtml $(GCOV_HTML_DIR)/$(COVERAGE_INFO) -o $(GCOV_HTML_DIR)
	open $(GCOV_HTML_DIR)/index.html

test_memory: $(EXECUTABLE)
	@echo "[34mChecking leaks ...[0m"
ifeq ($(OS),Linux)
	valgrind --tool=memcheck --leak-check=yes -s ./$(EXECUTABLE) --check-full -s  --leak-check=full
endif
ifeq ($(OS),Darwin) 
	CK_FORK=no leaks -quiet --atExit -- ./$(EXECUTABLE)
endif

test_format:
	@echo "[34mChecking styles...[0m"
	clang-format -n -style=Google *.cc *.h

format:
	@echo "[34mFormatting...[0m"
	clang-format -i -style=Google *.cc *.h

.PHONY: all clean test $(LIBS) gcov_report test_memory test_format format
