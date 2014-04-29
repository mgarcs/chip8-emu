#include <gfx.h>


int init_gfx(graphics_t *graphics) {
  graphics = (graphics_t *) malloc(sizeof(graphics_t));  
  
  if(SDL_Init(SDL_INIT_VIDEO) < 0) return 0;
  
  if(!(graphics->display = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_HWSURFACE))){
    SDL_Quit();
    return 0;
  }
  
  return 1;
}


void clear_screen(graphics_t *graphics){
    SDL_FillRect(graphics->display, NULL, SDL_MapRGB(graphics->display->format, 0, 0, 0));
}
