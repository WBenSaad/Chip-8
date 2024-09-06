#if !defined(MAIN_H)
#define MAIN_H

#include <stdint.h>
#include <keyboard.h>
#include <stdio.h>
#include <pixel.h>
#include <audio.h>
#include <Timer.h>
#include <cpu.h>
#include <string.h>


static char* rom_name = "Pong (1 player).ch8";
SDL_Event event ; 
int quit;

uint8_t load_rom(char*);
void execute_rom(void);
void poll_inputs (void);


#endif 
