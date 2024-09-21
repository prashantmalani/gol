CC = gcc
CFLAGS = -Wall -Wextra -g

TEST_SRC = test.c

TEST_EXEC = test_program

# Targets
all: $(EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXEC) $(TEST_EXEC)

.PHONY: all test clean

