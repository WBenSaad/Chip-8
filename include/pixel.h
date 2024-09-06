#if !defined(PIXEL_H)
#define PIXEL_H

#include <stdint.h>
#include <SDL.h>


#define l 64 
#define L 32 

#define DIMPIXEL 8 

#define screen_width   l*DIMPIXEL
#define screen_length  L*DIMPIXEL 

#define TOTAL_SPRITE_BYTES (16 * 5) // 16 sprites, 5 bytes each

#define BLACK  0
#define WHITE  1

typedef struct {
    SDL_Rect position ;
    uint8_t  color;
}PIXEL;

SDL_Surface *carre[2];
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

uint8_t frame_buffer[l][L]  ;

uint8_t screen[screen_width][screen_length];

uint8_t sprite[15];
static const uint8_t default_sprites[90]    = {0xF0,0x90,0x90,0x90,0xF0,
                                               0x20,0x60,0x20,0x20,0x70, 
                                               0xF0,0x10,0xF0,0x80,0xF0,
                                               0xF0,0x10,0xF0,0x10,0xF0,
                                               0x90,0x90,0xF0,0x10,0x10,
                                               0xF0,0x80,0xF0,0x10,0xF0,
                                               0xF0,0x80,0xF0,0x90,0xF0,
                                               0xF0,0x10,0x20,0x40,0x40,
                                               0xF0,0x90,0xF0,0x90,0xF0,
                                               0xF0,0x90,0xF0,0x10,0xF0,
                                               0xF0,0x90,0xF0,0x90,0x90,
                                               0xE0,0x90,0xE0,0x90,0xE0,
                                               0xF0,0x80,0x80,0x80,0xF0,
                                               0xE0,0x90,0x90,0x90,0xE0,
                                               0xF0,0x80,0xF0,0x80,0xF0,
                                               0xF0,0x80,0xF0,0x80,0x80};               

void framebuffer_init();
void DrawPixel(uint8_t,uint8_t,uint8_t);
int  video_init ();
void clear_screen();
void update_screen(); 


#endif // PIXEL_H
