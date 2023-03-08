PROG = main.exe 
SRC = main.c Define.h prompt.c common.c file.h file.c FileData.h Player.h Score.h input.h input.c
CFLAGS = -g
LIBS = 

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean