#ifndef GFX_H
#define GFX_H 

#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define SCREEN_DEPTH 32

typedef struct {
   SDL_Surface *display;
   SDL_Event event;

   int keypress;
   uint8_t x;
   uint8_t y;
   uint8_t c;
} graphics_t;  


int init_gfx(graphics_t *graphics);
void clear_screen(graphics_t *graphics);


#endif




