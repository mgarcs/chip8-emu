#ifndef GFX_H
#define GFX_H 

#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define SCREEN_DEPTH 32
#define BPP 4
#define PIXEL_SIZE 10


typedef struct {
   SDL_Surface *display;
  
   uint8_t x;
   uint8_t y;
} graphics_t;  


int init_gfx(graphics_t *graphics);
void clear_screen(graphics_t *graphics);

int is_pixel_set(graphics_t *graphics, int x, int y);
void set_pixel(graphics_t *graphics, int x, int y);


#endif




