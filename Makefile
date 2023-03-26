PROG = main.exe 
SRC = main.c Define.h prompt.c common.c util.h util.c array.c array.h FileData.h input.c input.h generate.c
CFLAGS = -g
LIBS = 

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean