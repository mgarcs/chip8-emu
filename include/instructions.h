#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <cpu.h>

#define INSTRUCTION(name) void instruction_##name(cpu_t *cpu)
#define EXEC_INSTRUCTION(name, cpu) instruction_##name(cpu)


INSTRUCTION(jmp);


#endif
