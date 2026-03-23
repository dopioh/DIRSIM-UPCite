CC = gcc
CFLAGS = -Wall -Wextra

main: main.c include/noeud.h include/liste_noeud.h
	$(CC) $(CFLAGS) -o programme main.c

clean:
	rm -f *.o programme