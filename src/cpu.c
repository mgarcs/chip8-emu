#include <cpu.h>
#include <instructions.h>

cpu_t* init_cpu() {
  cpu_t *cpu = (cpu_t *)calloc(1, sizeof(cpu_t));
  cpu->regs.sp = STACK_START;
  cpu->regs.pc = 0x200;

  return cpu;
}


int main(int argc, char *argv[]){
  cpu_t *cpu = init_cpu();

  STACK_PUSH(cpu, 3);

  printf("Stack pop: %d\n", STACK_POP(cpu));

  printf("Current stack location: %lX \n", &cpu->mem[cpu->regs.sp] - &cpu->mem[0]);
  return 0;
}
