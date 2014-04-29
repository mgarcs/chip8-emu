#include <gfx.h>


int init_gfx(graphics_t *graphics) {
  
  if(SDL_Init(SDL_INIT_VIDEO) < 0) return 0;
  
  if(!(graphics->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_HWSURFACE))){
    SDL_Quit();
    return 0;
  }
  
  return 1;
}



