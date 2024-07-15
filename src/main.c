#include "cpu.h"
#include <main.h>
#include <stdio.h>
#include <pixel.h>


#define FPS 16 
#define CPUSPEED 4 
#define INSTRUCTIONS_PER_REFRESH_CYCLE  15 
SDL_TimerID timer_id ;
uint8_t execute_Code = 1 ;


uint32_t timer_callback (uint32_t interval , void* param)
{
    timer_decrement();
    update_screen();
    execute_Code = 1 ;
    return (interval);
}

uint8_t load_rom(char* rom_name){

    FILE *rom = NULL ;
    rom = fopen(rom_name,"rb");
    if (rom != NULL)
    {
        fread(&cpu.memory[START_ADDRESS],sizeof(uint8_t)*(MEMORY_MAX - START_ADDRESS),1,rom);
        fclose(rom);
        fprintf(stderr,"Couldn't open ROM");
        cpu.pc =START_ADDRESS;
        fflush(stdout);
        return 1 ;
    }
    else
    {
        //fprintf(stderr,"Couldn't open ROM");
        //fflush(stdout);
        return 0 ;
    }
}

int main(int argc, char* argv[]) {


    SDL_Event event;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) 
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    init_SDL_Obj();
    initiliaze_cpu();
    init_Opcodetable();
    init_pixel();
    load_rom("3-corax+.ch8");
    SDL_AddTimer(17, timer_callback, NULL);
    int quit = 0;
    while (!quit) {
        execute_rom();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }
    SDL_Quitt();
    return 0;
}

void SDL_Quitt()
{

    SDL_RemoveTimer(timer_id);
    SDL_FreeSurface(carre[0]);
    SDL_FreeSurface(carre[1]);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void execute_rom()
{
    if (execute_Code)
    {
        for (int i = 0 ; i < INSTRUCTIONS_PER_REFRESH_CYCLE ; i++ )
        {
            uint16_t Opcode = getOpcode();
            //printf("Opcode = %x \n",Opcode);
            //fflush(stdout);
            executeOpcode(Opcode);
        }
        execute_Code = 0 ;
    }
}
/*
void pause(){
    uint8_t pause_ = 1 ;
    do 
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: 
                pause = 0 ;
                break;
            case SDL_KEYDOWN :
                pause = 0 ;
                break ;
            default :
                break ;
        }
    }while(pause==1);
}
*/