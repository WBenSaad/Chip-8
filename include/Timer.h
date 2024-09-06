#if !defined(TIMER_H)
#define TIMER_H

#include "stdint.h"
#include "SDL.h"

SDL_TimerID timer_id ;
int wait_state;
int execute_Code ;


uint32_t timer_callback (uint32_t interval , void* param) ;
int timer_init(void);


#endif TIMER_H