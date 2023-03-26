PROG = main.exe 
TEST_PROG = test_main.exe
SRC = main.c prompt.c common.c util.c util.h file.h file.c FileData.h input.c input.h
TEST_SRC = test_card_reader.c test_util.c test_common.c common.c
CFLAGS = -g
LIBS = 

all: $(PROG) $(TEST_PROG)


$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) 

$(TEST_PROG): $(TEST_SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(TEST_SRC) $(LIBS)

clean:
	rm -f $(PROG) $(TEST_PROG)

.PHONY: all clean