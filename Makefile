CC = gcc
CFLAGS = -Wall 
INCLUDES = -I./include \
					 -I/usr/include/SDL/ \
					
VPATH = src includes

ifeq ($(DEBUG),1)
CFLAGS += -g
endif

CFLAGS += $(shell sdl-config --cflags)
LDFLAGS = $(shell sdl-config --libs)

all: chip8

chip8: cpu.c instructions.c gfx.c vm.c
	@mkdir -p ./bin
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $^ -o bin/$@

dis: disassembly.c
	$(CC) -Wall $^ -o bin/$@

clean:
	@rm -rf ./bin
