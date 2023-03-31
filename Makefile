PROG=main.exe
CC=gcc
CFLAGS=-g -Wall -Werror
CFLAGS2=-O3 -Wall -Werror
DEPS = file.h common.h FileData.h input.h prompt.h util.h
OBJ_CODE = file.c common.c input.c prompt.c util.c
OBJ = $(OBJ_CODE) main.o 

GTEST = . #gtest-1.7.0/include
LIBGTEST = C:\msys64\mingw64\lib\libgtest_main.a C:\msys64\mingw64\lib\libgtest.a

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)