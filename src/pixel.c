#include "pixel.h"


void init_pixel(){

    for (int i = 0 ; i <= l ;i++){
        for (int j =0 ; j <= L ; j++){
            pixel[i][j].position.x *=DIMPIXEL ; 
            pixel[i][j].position.y *=DIMPIXEL ;
            pixel[i][j].color = BLACK ;
        }
    }

}

int init_SDL_Obj() 
{ 
    carre[0]=NULL; 
    carre[1]=NULL; 
    //Window initilization
    window = SDL_CreateWindow("SDL2 64x32 Window",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               screen_width, screen_length,
                               SDL_WINDOW_SHOWN);
    SDL_SetWindowTitle(window,"Chip8"); 

    if(window==NULL) 
    { 
        return 1 ;
    } 
    //Surface initilization
    carre[0]=SDL_CreateRGBSurface(0,DIMPIXEL,DIMPIXEL,32,0,0,0,0); 
    if(carre[0]==NULL) 
    { 
        return 1 ;
    } 
    SDL_FillRect(carre[0],NULL,SDL_MapRGB(carre[0]->format,0x00,0x00,0x00)); 

    carre[1]=SDL_CreateRGBSurface(0,DIMPIXEL,DIMPIXEL,32,0,0,0,0);
    if(carre[1]==NULL) 
    { 
       return 1; 
    } 

    SDL_FillRect(carre[1],NULL,SDL_MapRGB(carre[1]->format,0xFF,0xFF,0xFF));  //le pixel blanc 
    //Renderer initilization
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
} 

void DrawPixel(PIXEL pixel) {
    SDL_RenderClear(renderer);

    if (pixel.color == WHITE){
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    else if (pixel.color == BLACK){
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    }
        for (uint8_t i = 0 ; i < 8 ; i++){
            for (uint8_t j = 0 ; j < 8 ;j++){
               SDL_RenderDrawPoint(renderer,i + (pixel.position.x*DIMPIXEL), j + (pixel.position.y*DIMPIXEL)); 
        }
    }
}

void clear_screen()
{

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void update_screen()
{
     SDL_RenderPresent(renderer);
}