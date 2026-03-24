CC = gcc
CFLAGS = -Wall -Wextra

SRC = src/main.c src/instruction/*.c

main: $(SRC) src/include/*.h src/instruction/*.h
	$(CC) $(CFLAGS) -o programme $(SRC)

clean:
	rm -f *.o programme