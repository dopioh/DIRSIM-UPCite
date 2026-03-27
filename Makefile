CC = gcc
CFLAGS = -Wall -Wextra
BIN_DIR = build/bin
TARGET = $(BIN_DIR)/programme

SRC = src/*.c src/instruction/*.c

main: $(SRC) src/include/*.h src/instruction/*.h
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f *.o $(TARGET)

run:
	./build/bin/programme instructions.txt