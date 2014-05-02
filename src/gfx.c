#include <gfx.h>


int init_gfx(graphics_t *graphics) {
  graphics = (graphics_t *) calloc(1, sizeof(graphics_t));  
  
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

int is_pixel_set(graphics_t *graphics, int x, int y){
  Uint32 *pixels = (Uint32 *)graphics->display->pixels;
  
  return pixels[(y * graphics->display->pitch) + x] == 0xFF ? 1 : 0;
}

void set_pixel(graphics_t *graphics, int x, int y) {
  int i,j;
  
  x *= PIXEL_SIZE;
  y *= PIXEL_SIZE;

  Uint32 *pixels = (Uint32 *)graphics->display->pixels;

  for (j = 0; j < PIXEL_SIZE; ++j){
    for (i = 0; i < PIXEL_SIZE; ++i){
      pixels[(y * graphics->display->pitch) + x] ^= 0xFF;    
    }
  }

  
  
   
}



