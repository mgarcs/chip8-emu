#include <instructions.h>

/* 00E0	 cls	 Clear the screen */
INSTRUCTION(cls) {
  clear_screen(cpu->gfx); 
}

/* 00EE	 rts	 return from subroutine call */
INSTRUCTION(rts) {
   cpu->regs.pc = STACK_POP(cpu);
   
   if(IS_STACK_SMASHED(cpu->regs.sp)) {
      fprintf(stderr, "[Fatal Error] Stack smashing detected.\n");
      fprintf(stderr, "========== Memory Dump ===========\n");
      dump_memory(cpu);
      exit(1);
   }
}

/* 1xxx	 jmp xxx	 jump to address xxx */
INSTRUCTION(jmp) {
  cpu->regs.pc = cpu->opcode & 0xFFF;     
}

/* 2xxx	 jsr xxx	 jump to subroutine at address xxx */
INSTRUCTION(jsr) {
  STACK_PUSH(cpu, cpu->regs.pc);
  if(IS_STACK_SMASHED(cpu->regs.sp)) {
      fprintf(stderr, "[Fatal Error] Stack smashing detected.\n");
      fprintf(stderr, "========== Memory Dump ===========\n");
      dump_memory(cpu);
      exit(1);
   }

  cpu->regs.pc = cpu->opcode & 0xFFF;
}

/* 3rxx	 skeq vr,xx	 skip if register r = constant */
INSTRUCTION(skeq) {
  (cpu->opcode & 0x0F00) >> 8 == (cpu->opcode & 0xFF) ? cpu->regs.pc += 2 : 0;
}

/* 4rxx	 skne vr,xx	 skip if register r <> constant */
INSTRUCTION(skne) {
  (cpu->opcode & 0x0F00) >> 8 != (cpu->opcode & 0xFF) ? cpu->regs.pc += 2 : 0;
}

