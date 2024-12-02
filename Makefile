# comp & comp flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wno-stringop-overread -fprofile-arcs -ftest-coverage

# for diff linking on MacOS and Linux
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    LDFLAGS := -lcheck -fprofile-arcs --coverage -pthread -lcheck_pic -lrt -lm -lsubunit
    LIBLINK := -L. -l:s21_string.a
else ifeq ($(UNAME), Darwin)  # MacOS
    LDFLAGS := -lcheck -fprofile-arcs --coverage
    LIBLINK := s21_string.a
else
    $(error Unsupported platform: $(UNAME))
endif

# source files/dirs
SRCDIR = .
LIB_OBJDIR = lib_obj
TEST_OBJDIR = tests_obj

SRC = $(filter-out $(SRCDIR)/s21_sprintf.c, $(wildcard $(SRCDIR)/s21_*.c))  # REMOVE FILTER-OUT FOR S21_SSPTINF LATER
LIB_OBJ = $(patsubst $(SRCDIR)/%.c, $(LIB_OBJDIR)/%.o, $(SRC))
LIB = s21_string.a

# for testing & gcov report
TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/test_s21_*.c)  
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJDIR)/%.o, $(TEST_SRC))
TEST_EXEC = s21_string_test

# default target
all: clean $(LIB)
	@rm -f *.gcda *.gcno

# creating directories for objects
$(LIB_OBJDIR):
	mkdir -p $(LIB_OBJDIR)

$(TEST_OBJDIR):
	mkdir -p $(TEST_OBJDIR)

# building static lib from obj files
$(LIB): $(LIB_OBJDIR) $(LIB_OBJ)
	ar rcs $@ $(LIB_OBJ)

# library object files
$(LIB_OBJDIR)/%.o: $(SRCDIR)/%.c | $(LIB_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# test object files
$(TEST_OBJDIR)/%.o: $(TEST_DIR)/%.c | $(TEST_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# build and run tests
test: $(LIB) $(TEST_OBJDIR) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBLINK) -o $(TEST_EXEC) $(LDFLAGS)

# general gcov report in HTML format
gcov_report: test
# 	rm -rf gcov_report; mkdir gcov_report
# 	gcov -o $(SRCDIR)/s21_*.c
# # lcov report
# 	lcov -c -d . --output-file coverage/coverage.info
# # generating html
# 	genhtml coverage/coverage.info --output-directory coverage/html
# 	@echo "GCOV REPORT IS DONE"

# clean objects without deleting the library and test executable
clean_obj_gcov:
	rm -f $(LIB_OBJDIR)/*.o $(TEST_OBJDIR)/*.o *.gcda *.gcno
	rm -f $(TEST_OBJDIR)/*.gcda $(TEST_OBJDIR)/*.gcno

# clean target
clean:
	rm -rf $(LIB_OBJDIR) $(TEST_OBJDIR) $(LIB) $(TEST_EXEC) *.gcda *.gcno

.PHONY: all clean test gcov_report
