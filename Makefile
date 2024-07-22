.PHONY: build

CC = clang
APP = astar
OUTPUT = astar
LDFLAGS=-lncurses

run: build
	@./$(OUTPUT)

build:
	clang-format -i ./$(APP).c
	@$(CC) $(APP).c -o $(OUTPUT) -Wall -Wextra -pedantic -g -std=c99 $(LDFLAGS)

format:
	clang-format -i ./$(APP).c

clean:
	rm ./$(OUTPUT)
