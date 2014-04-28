CC = gcc
CFLAGS = -g -Wall
INCLUDES = -I./include

VPATH = ./src ./includes

all: chip8

chip8: cpu.c instructions.c
	@mkdir -p ./bin
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o bin/$@

disass: disassembly.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o bin/$@

clean:
	@rm -rf ./bin
