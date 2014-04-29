#include <cpu.h>
#include <gfx.h>


int main(int argc, char *argv[]){
    
  if(argc < 2) {
		fprintf(stderr, "Usage: ./chip8 <rom>\n");
		return 1;
	}

  cpu_t *cpu = init_cpu();
  
  /* graphics_t gfx; */
  /*  */
  /* if(!init_gfx(&gfx)){ */
  /*   perror("Unable to initialize display"); */
  /*   exit(1); */
  /* } */


  // Load Rom to memory
  FILE *rom = fopen(argv[1], "rb");
  fread(cpu->mem, MEMORY_SIZE, 1, rom);  
  fclose(rom);

  int i;
  for (i = 0; i < MEMORY_SIZE; ++i){
    printf("%X\n",cpu->mem[i]);
  }


  return 0;
}
