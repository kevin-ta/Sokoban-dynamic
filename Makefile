CC=gcc
CFLAGS=-Wall -ansi -pedantic
LDFLAGS=
EXEC=sokoban
BIN=sokoban.o pileGrille.o main.o
SRC=sokoban.c pileGrille.c main.c
HEAD=sokoban.h pileGrille.h
 
all: $(EXEC)
 
sokoban: $(BIN)
	$(CC) -o sokoban $(BIN) $(LDFLAGS)
 
%.o: %.c $(HEAD)
	$(CC) -c $< $(CFLAGS)
 
clean:
	rm -f *.o *~ 2> /dev/null
 
clear: clean
	rm -f $(EXEC) $(USER)_sokoban.tgz 2> /dev/null
 
zip: clear
	mkdir -p $(USER)_sokoban
	cp Makefile *.c *.h *.sok $(USER)_sokoban
	tar czf $(USER)_sokoban.tgz $(USER)_sokoban
	rm -rf $(USER)_sokoban