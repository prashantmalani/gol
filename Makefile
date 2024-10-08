# Boilerplate generated by ChatGPT

CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = main.c gol.c
TEST_SRC = test.c gol.c

EXEC = gol
TEST_EXEC = test_program

# Targets
all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXEC) $(TEST_EXEC)

.PHONY: all test clean

