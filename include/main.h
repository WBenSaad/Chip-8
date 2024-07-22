#if !defined(MAIN_H)
#define MAIN_H

#include <stdint.h>
#include <keyboard.h>
#include <stdio.h>
#include <pixel.h>
#include "cpu.h"
#include <string.h>

SDL_mutex* mutexx;
uint8_t wait_state;
uint8_t mutex ;
SDL_TimerID timer_id ;




uint8_t loadrom(char*);
uint32_t timer_callback(uint32_t,void*);
void execute_rom(void);


#endif 
