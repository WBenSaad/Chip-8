#include "cpu.h"
#include <stdio.h>
#include <pixel.h>

#define FPS 16 
#define CPUSPEED 4 ;
uint8_t pause = 1 ;
int main(int argc, char* argv[]) {


    SDL_Event event;
    init_SDL_Obj();
    PIXEL pixel ;
    pixel.position.x=0 ;
    pixel.position.y=0 ;
    pixel.color =WHITE ;
    DrawPixel(pixel);
    update_screen();
    do
    {
    update_screen();
    SDL_Delay(FPS);/* code */
    } while (pause == 1);
    
    pause();




    return 0;
}

void SDL_Quit(){

    SDL_FreeSurface(carre[0]);
    SDL_FreeSurface(carre[1]);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void pause(){
    uint8_t pause = 1 ;
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