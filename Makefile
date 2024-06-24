C_COMPILER       = gcc
C_OPTIONS        = -Wall -pedantic -g -Iinclude
C_LINK_OPTIONS   = -lm
CUNIT_LINK       = -lcunit
C_COV            = -fprofile-arcs -ftest-coverage
LFLAGS           = -lgcov --coverage
GCOV             = gcov
LCOV             = lcov
COV_HTML         = genhtml
VALGRIND         = valgrind
VALGRIND_FLAGS   = --leak-check=full
PROFILING_FLAGS  = -pg
PROFILE_DIR      = profileout
OBJ_DIR          = obj

SRC_DIR          = src
INCLUDE_DIR      = include
TESTS_DIR        = tests

OBJS             = $(OBJ_DIR)/linked_list.o
TEST_OBJS        = $(OBJ_DIR)/linked_list_test.o

all: linked_list

linked_list: $(OBJ_DIR)/linked_list.o
	$(C_COMPILER) $^ -o $@ $(C_LINK_OPTIONS) -c 

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(C_COMPILER) $(C_OPTIONS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJ_DIR)
	$(C_COMPILER) $(C_OPTIONS) -c $< -o $@

$(PROFILE_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(C_COMPILER) $(C_OPTIONS) $(PROFILING_FLAGS) -c $< -o $@

linked_list_test: $(OBJ_DIR)/linked_list_test.o $(OBJ_DIR)/linked_list.o
	$(C_COMPILER) $^ -o $@ $(CUNIT_LINK)

test: linked_list_test
	./linked_list_test

memtest: test
	$(VALGRIND) $(VALGRIND_FLAGS) ./linked_list_test

test_coverage: clean
	$(C_COMPILER) $(C_OPTIONS) $(LFLAGS) -o test $(TESTS_DIR)/linked_list_test.c $(SRC_DIR)/linked_list.c $(CUNIT_LINK)
	./test
	$(GCOV) $(TESTS_DIR)/linked_list_test.c $(SRC_DIR)/linked_list.c
	$(GCOV) -abcfu $(SRC_DIR)/linked_list.c
	$(LCOV) -c -d . -o linked_list.info
	$(COV_HTML) linked_list.info -o linked_list-lcov

clean:
	-$(RMDIR) $(PROFILE_DIR)
	-$(RMDIR) *-lcov
	-$(RM) $(OBJ_DIR)/*.o $(SRC_DIR)/*.o $(TESTS_DIR)/*.o *.gcda gmon.out *.gcno *.info linked_list linked_list_test
	-$(RMDIR) $(OBJ_DIR)

RM = rm -f
RMDIR = rm -rf

.PHONY: all clean