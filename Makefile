PROG=main.exe
TEST_PROG=test_main.exe
CC=gcc
CFLAGS=-g -Wall -Werror
CFLAGS2=-O3 -Wall -Werror
DEPS = file.h common.h FileData.h input.h prompt.h util.h menu.h
OBJ_CODE = file.c common.c input.c prompt.c util.c menu.c
OBJ = $(OBJ_CODE) main.o 

DEPS_TEST = test_util.c test_common.c file.h common.h FileData.h input.h prompt.h util.h menu.h
OBJ_CODE_TEST = test_util.c test_common.c file.c common.c input.c prompt.c util.c menu.c
OBJ_TEST = $(OBJ_CODE_TEST) test_main.o 

GTEST = . #gtest-1.7.0/include
#LIBGTEST = C:\msys64\mingw64\lib\libgtest_main.a C:\msys64\mingw64\lib\libgtest.a

%.o: %.c $(DEPS) $(DEPS_TEST)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROG) $(TEST_PROG) run_tests

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TEST_PROG): $(OBJ_TEST)
	$(CC) -o $@ $^ $(CFLAGS)

run_tests: $(TEST_PROG)
	./$(TEST_PROG)

clean:
	rm -f $(PROG) $(TEST_PROG) *.o

.PHONY: all clean run_tests

