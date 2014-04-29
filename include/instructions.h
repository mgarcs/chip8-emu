#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <cpu.h>
#include <gfx.h>

#define INSTRUCTION(name) void instruction_##name(cpu_t *cpu)
#define EXEC_INSTRUCTION(name, cpu) instruction_##name(cpu)

INSTRUCTION(cls);
INSTRUCTION(rts);
INSTRUCTION(jmp);
INSTRUCTION(jsr);
INSTRUCTION(skeq);
INSTRUCTION(skne); 


#endif
