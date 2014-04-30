#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gfx.h>

#define MEMORY_SIZE 4096

#define STACK_START 0xEA0
#define STACK_END 0xEFF
#define STACK_PUSH(cpu, val) cpu->mem[++(cpu)->regs.sp] = val
#define STACK_POP(cpu) (cpu)->mem[(cpu)->regs.sp--]
#define IS_STACK_SMASHED(sp) (sp < STACK_START || sp > STACK_END) ? 1 : 0


static uint8_t fontset[80] = { 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

typedef struct reg{
  uint16_t pc;
  uint16_t sp;

  uint16_t index;
  uint8_t v[16];  
} reg_t;

typedef struct cpu{
  uint8_t mem[MEMORY_SIZE];
  uint16_t opcode;
  
  reg_t regs;
  
  uint8_t delay_timer;
  uint8_t sound_timer;

  graphics_t *gfx;
  uint8_t keypad;
} cpu_t;


cpu_t* init_cpu();
void execute_cycle(cpu_t *cpu);

void dump_memory(cpu_t *cpu);

#endif
