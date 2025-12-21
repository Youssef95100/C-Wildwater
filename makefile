CC = gcc
CFLAGS = -Wall -Wextra -std=c99
EXEC = c-wire

all: $(EXEC)

# Édition des liens
$(EXEC): main.o avl.o station.o graphe.o parser.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o avl.o station.o graphe.o parser.o

# Compilation des fichiers sources
main.o: main.c avl.h parser.h graphe.h
	$(CC) $(CFLAGS) -c main.c

station.o: station.c station.h
	$(CC) $(CFLAGS) -c station.c

avl.o: avl.c avl.h station.h
	$(CC) $(CFLAGS) -c avl.c

graphe.o: graphe.c graphe.h station.h
	$(CC) $(CFLAGS) -c graphe.c

parser.o: parser.c parser.h avl.h graphe.h
	$(CC) $(CFLAGS) -c parser.c

clean:
	rm -f *.o $(EXEC) *.csv *.png *.tmp

.PHONY: all clean