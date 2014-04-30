#include <cpu.h>
#include <instructions.h>

static inline uint16_t fetch_dword(uint8_t *mem, uint16_t pc) {
  return (mem[pc] << 8) | mem[pc + 1];
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

  printf("opcode = %04x\n", cpu->opcode);
  
  switch(cpu->opcode & 0xF000){
    case 0x0000:
      switch(cpu->opcode & 0x0FF){
        case 0xE0: EXEC_INSTRUCTION(cpu, cls); break; /* CLS */
        case 0xEE: EXEC_INSTRUCTION(cpu, rts); break; /* RTS */
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0x1000: EXEC_INSTRUCTION(cpu, jmp);    break; /* JMP */
    case 0x2000: EXEC_INSTRUCTION(cpu, jsr);    break; /* JSR */ 
    case 0x3000: EXEC_INSTRUCTION(cpu, skeq);   break; /* SKEQ */
    case 0x4000: EXEC_INSTRUCTION(cpu, skne);   break; /* SKNE */
    case 0x5000: EXEC_INSTRUCTION(cpu, skeq2);  break; /* SKEQ */
    case 0x6000: EXEC_INSTRUCTION(cpu, mov);    break; /* MOV  VX, C*/
    case 0x7000: EXEC_INSTRUCTION(cpu, add);    break; /* ADD */

    case 0x8000:
      switch(cpu->opcode & 0x000F){
        case 0x0000: EXEC_INSTRUCTION(cpu, mov2);   break; /* MOV VX,VY */
        case 0x0001: EXEC_INSTRUCTION(cpu, or);     break; /* OR */
        case 0x0002: EXEC_INSTRUCTION(cpu, and);    break; /* AND */
        case 0x0003: EXEC_INSTRUCTION(cpu, xor);    break; /* XOT */
        case 0x0004: EXEC_INSTRUCTION(cpu, add2);   break;
        case 0x0005: EXEC_INSTRUCTION(cpu, sub);    break;
        case 0x0006: EXEC_INSTRUCTION(cpu, shr);    break;
        case 0x0007: EXEC_INSTRUCTION(cpu, rsb);    break;
        case 0x000E: EXEC_INSTRUCTION(cpu, shl);    break;
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0x9000: EXEC_INSTRUCTION(cpu, skne2);  break;
    case 0xA000: EXEC_INSTRUCTION(cpu, mvi);    break;
    case 0xB000: EXEC_INSTRUCTION(cpu, jmi);    break;
    case 0xC000: EXEC_INSTRUCTION(cpu, rand);   break;
    case 0xD000: 
        switch(cpu->opcode & 0x000F){
          case 0x0000: EXEC_INSTRUCTION(cpu, sprite);  break;
          case 0x000E: EXEC_INSTRUCTION(cpu, xsprite); break;
          default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);             
        }
        break;
          
    case 0xE000: 
      switch(cpu->opcode & 0x00FF){
        case 0x9E: EXEC_INSTRUCTION(cpu, skpr); break;
        case 0xA1: EXEC_INSTRUCTION(cpu, skup); break;
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0xF000:
      switch(cpu->opcode & 0x00FF){
        case 0x0007: EXEC_INSTRUCTION(cpu, gdelay); break;
        case 0x000A: EXEC_INSTRUCTION(cpu, key);    break;
        case 0x0015: EXEC_INSTRUCTION(cpu, sdelay); break;
        case 0x0018: EXEC_INSTRUCTION(cpu, ssound); break;
        case 0x001E: EXEC_INSTRUCTION(cpu, adi);    break;
        case 0x0029: EXEC_INSTRUCTION(cpu, font);   break;
        case 0x0033: EXEC_INSTRUCTION(cpu, bcd);    break;
        case 0x0055: EXEC_INSTRUCTION(cpu, str);    break;
        case 0x0065: EXEC_INSTRUCTION(cpu, ldr);    break;
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
