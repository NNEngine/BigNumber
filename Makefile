CC=gcc
CFLAGS=-Wall -Wextra -O2 -Iincludes
SRC=main.c src/Arithmetic.c src/BigNumber.c src/Bitwise.c src/Comparison.c src/Unary.c src/utilities.c
TARGET=main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
