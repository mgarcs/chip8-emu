#include <cpu.h>
#include <gfx.h>


int main(int argc, char *argv[]){
    
  if(argc < 2) {
		fprintf(stderr, "Usage: ./chip8 <rom>\n");
		return 1;
	}
  
  cpu_t *cpu = init_cpu();

  if(!init_gfx(cpu->gfx)){
    perror("Unable to initialize display");
    exit(1);
  }

  // Load Rom to memory
  FILE *rom = fopen(argv[1], "rb");
  fread(&cpu->mem[0x200], MEMORY_SIZE - 0x200, 1, rom);  
  fclose(rom);


 
  int i;
  for (i = 0; i < 300; ++i){
    execute_cycle(cpu);
  }

  printf("==== Memory Dump ==== \n");
  dump_memory(cpu);
  printf("===================== \n");
  
 


  return 0;
}
