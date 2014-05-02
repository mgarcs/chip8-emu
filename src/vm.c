#include <cpu.h>
#include <gfx.h>


int event_handler(cpu_t *cpu) {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch(event.type) {
    case SDL_QUIT: return SDL_QUIT;
    case SDL_KEYDOWN: 
      switch (event.key.keysym.sym) {
        case SDLK_q: return SDLK_q;
        case SDLK_p: return SDLK_p;
      }
      break;
  }
  
  return -1;
}


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

  // Execution Loop
  int pause = 1;
  while(1){
    int event = event_handler(cpu);

    if(event == SDLK_q) {
      break;
    } else if(event != SDLK_p) {
      pause ^= 1;
    }

    if(pause){
      execute_cycle(cpu);

      if(cpu->delay_timer > 0)
        cpu->delay_timer--;

      if(cpu->sound_timer > 0)
        cpu->sound_timer--;
    }

  }

  /* free(cpu); */

  return 0;
}
