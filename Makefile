.PHONY: build

CC = clang
APP = main
OUTPUT = r
LDFLAGS=-lncurses -lm

build:
	clang-format -i ./$(APP).c ./astar.h
	@$(CC) $(APP).c -o $(OUTPUT) -Wall -Wextra -pedantic -g -std=c99 $(LDFLAGS)

run: build
	@./$(OUTPUT)

format:
	clang-format -i ./$(APP).c ./astar.h

clean:
	rm ./$(OUTPUT)
