#include <cpu.h>
#include <instructions.h>


static inline uint16_t fetch_dword(uint8_t *mem, uint8_t pc) {
  return mem[pc] << 8 | mem[pc + 1];
}


cpu_t* init_cpu() {
  cpu_t *cpu = (cpu_t *)calloc(1, sizeof(cpu_t));
  cpu->regs.sp = STACK_START;
  cpu->regs.pc = 0x200;

  memcpy(cpu->mem, fontset, sizeof(fontset));
    
  return cpu;
}


void execute_cycle(cpu_t *cpu) {
  cpu->opcode = fetch_dword(cpu->mem, cpu->regs.pc);
  cpu->regs.index = cpu->opcode & 0xFFF;
  cpu->regs.pc += 2;

  switch(cpu->opcode & 0xF000){
    case 0x0000:
      switch(cpu->opcode & 0x0FF){
        case 0xE0: EXEC_INSTRUCTION(cls, cpu); break; /* CLS */
        case 0xEE: EXEC_INSTRUCTION(rts, cpu); break; /* RTS */
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0x1000: EXEC_INSTRUCTION(jmp, cpu);    break; /* JMP */
    case 0x2000: EXEC_INSTRUCTION(jsr, cpu);    break; /* JSR */ 
    case 0x3000: EXEC_INSTRUCTION(skeq, cpu);   break; /* SKEQ */
    case 0x4000: EXEC_INSTRUCTION(skne, cpu);   break; /* SKNE */
    case 0x5000: EXEC_INSTRUCTION(skeq2, cpu);  break; /* SKEQ */
    case 0x6000: EXEC_INSTRUCTION(mov, cpu);    break; /* MOV  VX, C*/
    case 0x7000: EXEC_INSTRUCTION(add, cpu);    break; /* ADD */

    case 0x8000:
      switch(cpu->opcode & 0x000F){
        case 0x0000: EXEC_INSTRUCTION(mov2, cpu);   break; /* MOV VX,VY */
        case 0x0001: EXEC_INSTRUCTION(or, cpu);     break; /* OR */
        case 0x0002: EXEC_INSTRUCTION(and, cpu);    break; /* AND */
        case 0x0003: EXEC_INSTRUCTION(xor,cpu);     break; /* XOT */
        case 0x0004: EXEC_INSTRUCTION(add2, cpu);   break;
        case 0x0005: EXEC_INSTRUCTION(sub, cpu);    break;
        case 0x0006: EXEC_INSTRUCTION(shr, cpu);    break;
        case 0x0007: EXEC_INSTRUCTION(rsb, cpu);    break;
        case 0x000E: EXEC_INSTRUCTION(shl, cpu);    break;
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0x9000: EXEC_INSTRUCTION(skne2, cpu);  break;
    case 0xA000: EXEC_INSTRUCTION(mvi, cpu);    break;
    case 0xB000: EXEC_INSTRUCTION(jmi, cpu);    break;
    case 0xC000: EXEC_INSTRUCTION(rand, cpu);   break;
    case 0xD000: 
        switch(cpu->opcode & 0x000F){
          case 0x0000: EXEC_INSTRUCTION(sprite, cpu);  break;
          case 0x000E: EXEC_INSTRUCTION(xsprite, cpu); break;
          default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);             
        }
        break;
          
    case 0xE000: 
      switch(cpu->opcode & 0x00FF){
        case 0x9E: EXEC_INSTRUCTION(skpr, cpu);  break;
        case 0xA1: EXEC_INSTRUCTION(skup, cpu);     break;
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0xF000:
      switch(cpu->opcode & 0x00FF){
        case 0x0007: EXEC_INSTRUCTION(gdelay, cpu);   break;
        case 0x000A: EXEC_INSTRUCTION(key, cpu); break;
        case 0x0015: EXEC_INSTRUCTION(sdelay, cpu);    break;
        case 0x0018: EXEC_INSTRUCTION(ssound, cpu); break;
        case 0x001E: EXEC_INSTRUCTION(adi, cpu); break;
        case 0x0029: EXEC_INSTRUCTION(font, cpu);    break;
        case 0x0033: EXEC_INSTRUCTION(bcd, cpu);   break;
        case 0x0055: EXEC_INSTRUCTION(str, cpu);  break;
        case 0x0065: EXEC_INSTRUCTION(ldr, cpu);    break;
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
  }
}



/***********************************************************************
 *                              Utils   
 ***********************************************************************/

void dump_memory(cpu_t *cpu){
  unsigned hex_per_row = 32;

  int i,j ;
  for (i = 0x000; i < 0xFFF; i += hex_per_row){   
    for (j = i; j < (i + hex_per_row); ++j){
      printf("%02X ", cpu->mem[j]);
    }
    printf("\n");
  }

}
