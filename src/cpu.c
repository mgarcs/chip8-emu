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
        case 0xE0:  EXEC_INSTRUCTION(cls, cpu); break; /* CLS */
        case 0xEE:  EXEC_INSTRUCTION(rts, cpu); break; /* RTS */
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0x1000: EXEC_INSTRUCTION(jmp, cpu); break; /* JMP */
    case 0x2000: break; 
    case 0x3000: break;
    case 0x4000: break;
    case 0x5000: break;
    case 0x6000: break;
    case 0x7000: break;

    case 0x8000:
      switch(cpu->opcode & 0x000F){
        case 0x0001: break;
        case 0x0002: break;
        case 0x0003: break;
        case 0x0004: break;
        case 0x0005: break;
        case 0x0006: break;
        case 0x0007: break;
        case 0x0008: break;
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0x9000: break;
    case 0xA000: break;
    case 0xC000: break;
    case 0xD000: break;

    case 0xE000: 
      switch(cpu->opcode & 0x00FF){
        case 0x9E: break;
        case 0xA1: break;
        default: fprintf(stderr, "Unknown opcode: %04X\n", cpu->opcode);
      }
      break;

    case 0xF000:
      switch(cpu->opcode & 0x00FF){
        case 0x0007: break;
        case 0x000A: break;
        case 0x0015: break;
        case 0x0018: break;
        case 0x001E: break;
        case 0x0029: break;
        case 0x0033: break;
        case 0x0055: break;
        case 0x0065: break;
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
