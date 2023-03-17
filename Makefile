PROG = main.exe 
SRC = main.c Define.h prompt.c common.c util.c util.h file.h file.c FileData.h input.c input.h
CFLAGS = -g
LIBS = 

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean