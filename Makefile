CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -O2 -Iincludes
DEBUG_FLAGS=-g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer

SRC=main.c src/Arithmetic.c src/BigNumber.c src/Bitwise.c src/Comparison.c src/Unary.c src/utilities.c
LIB_SRC=$(filter-out main.c,$(SRC))

TARGET=main

TEST_CATEGORY=$(word 2,$(MAKECMDGOALS))
TEST_NAME=$(word 3,$(MAKECMDGOALS))
TEST_SRC=tests/$(TEST_CATEGORY)/$(TEST_NAME).c
TEST_BIN=build/tests/$(TEST_CATEGORY)/$(TEST_NAME)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: CFLAGS += $(DEBUG_FLAGS)
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(LIB_SRC)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB_SRC) -o $@

ifneq ($(TEST_CATEGORY),)
.PHONY: $(TEST_CATEGORY)
$(TEST_CATEGORY):
	@:
endif

ifneq ($(TEST_NAME),)
.PHONY: $(TEST_NAME)
$(TEST_NAME):
	@:
endif

clean:
	rm -rf $(TARGET) build/

.PHONY: all run test clean
