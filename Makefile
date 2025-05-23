CFLAGS := -std=c++20 -Wall -Wextra -pedantic -Iinclude
CC := clang++
SOURCE_FILES := src/lexer.cpp src/token.cpp
TEST_FILES := tests/lexer_test.cpp tests/simple_test.cpp
build:
	$(CC) $(CFLAGS) $(SOURCE_FILES) src/main.cpp -o colon

test:
	$(CC) $(CFLAGS) $(SOURCE_FILES) $(TEST_FILES) -o test
	./test

.PHONY: build test
