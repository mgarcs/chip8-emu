#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cpu.h>
#include <gfx.h>

#define INSTRUCTION(name) void instruction_##name(cpu_t *cpu)
#define EXEC_INSTRUCTION(cpu, name) instruction_##name(cpu)

INSTRUCTION(cls);
INSTRUCTION(rts);
INSTRUCTION(jmp);
INSTRUCTION(jsr);
INSTRUCTION(skeq);
INSTRUCTION(skne); 
INSTRUCTION(skeq2);
INSTRUCTION(mov);
INSTRUCTION(add);
INSTRUCTION(mov2);
INSTRUCTION(or);
INSTRUCTION(and);
INSTRUCTION(xor);
INSTRUCTION(add2);
INSTRUCTION(sub);
INSTRUCTION(shr);
INSTRUCTION(rsb);
INSTRUCTION(shl);
INSTRUCTION(skne2);
INSTRUCTION(mvi);
INSTRUCTION(jmi);
INSTRUCTION(rand);
INSTRUCTION(sprite);
INSTRUCTION(skpr);
INSTRUCTION(skup);
INSTRUCTION(gdelay);
INSTRUCTION(key);
INSTRUCTION(sdelay);
INSTRUCTION(ssound);
INSTRUCTION(adi);
INSTRUCTION(font);
INSTRUCTION(xfont);
INSTRUCTION(bcd);
INSTRUCTION(str);
INSTRUCTION(ldr);

#endif
