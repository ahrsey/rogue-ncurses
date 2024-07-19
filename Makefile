.PHONY: build

CC = clang
APP = main
OUTPUT = r
LDFLAGS=-lncurses

build:
	clang-format -i ./$(APP).c
	@$(CC) $(APP).c -o $(OUTPUT) -Wall -Wextra -pedantic -g -std=c99 $(LDFLAGS)

format:
	clang-format -i ./$(APP).c

run: build
	@./$(OUTPUT)

clean:
	rm ./$(OUTPUT)
