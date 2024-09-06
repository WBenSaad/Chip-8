#include "Timer.h"
#include "main.h"

uint32_t timer_callback (uint32_t interval , void* param)
{
    timer_decrement();
    update_screen();
    execute_Code = 1 ;
    wait_state = 0 ;
    return (interval);
}

int timer_init()
{
    if (SDL_Init(SDL_INIT_TIMER)< 0) 
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
}
void timer_start()
{
    timer_id = SDL_AddTimer(17, timer_callback, NULL);
}