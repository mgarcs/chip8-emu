#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 0xFFF

#define STACK_START 0xEA0
#define STACK_PUSH(cpu, val) cpu->mem[++(cpu)->regs.sp] = val
#define STACK_POP(cpu) (cpu)->mem[(cpu)->regs.sp--]


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
  uint8_t keypad;
} cpu_t;


cpu_t* init_cpu();
void execute_cycle(cpu_t *cpu);


#endif
