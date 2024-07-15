#include <stdint.h>
#include <SDL.h>

#if !defined(PIXEL_H)
#define PIXEL_H

#define l 64 
#define L 32 

#define DIMPIXEL 8 

#define screen_width   l*DIMPIXEL
#define screen_length  L*DIMPIXEL 

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

uint8_t frame_buffer[l][L]  ;//={0};
//PIXEL chip8_buffer[l][L];

uint8_t screen[screen_width][screen_length];

uint8_t sprite[15];

/*
const struct 
{
    uint8_t sprite_0[5] ;
    uint8_t sprite_1[5] ;
    uint8_t sprite_2[5] ;
    uint8_t sprite_3[5] ;
    uint8_t sprite_4[5] ;
    uint8_t sprite_5[5] ;
    uint8_t sprite_6[5] ;
    uint8_t sprite_7[5] ;
    uint8_t sprite_8[5] ;
    uint8_t sprite_9[5] ;
    uint8_t sprite_A[5] ;
    uint8_t sprite_B[5] ;
    uint8_t sprite_C[5] ;
    uint8_t sprite_D[5] ;
    uint8_t sprite_E[5] ;
    uint8_t sprite_F[5] ;

}default_sprites = {
    {0xF0,0x90,0x90,0x90,0xF0},
    {0x20,0x60,0x20,0x20,0x70},
    {0xF0,0x10,0xF0,0x80,0xF0},
    {0xF0,0x10,0xF0,0x10,0xF0},
    {0x90,0x90,0xF0,0x10,0x10},
    {0xF0,0x80,0xF0,0x10,0xF0},
    {0xF0,0x80,0xF0,0x90,0xF0},
    {0xF0,0x10,0x20,0x40,0x40},
    {0xF0,0x90,0xF0,0x90,0xF0},
    {0xF0,0x90,0xF0,0x10,0xF0},
    {0xF0,0x90,0xF0,0x90,0x90},
    {0xE0,0x90,0xE0,0x90,0xE0},
    {0xF0,0x80,0x80,0x80,0xF0},
    {0xE0,0x90,0x90,0x90,0xE0},
    {0xF0,0x80,0xF0,0x80,0xF0},
    {0xF0,0x80,0xF0,0x80,0x80}
};
*/
void init_pixel();
void DrawPixel(uint8_t,uint8_t);
int init_SDL_Obj ();
void clear_screen();
void update_screen(); 


#endif // PIXEL_H
