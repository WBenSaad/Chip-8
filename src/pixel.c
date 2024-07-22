#include "pixel.h"
SDL_Texture* BlackTexture ;
SDL_Texture* WhiteTexture ;

void init_framebuffer()
{

    for (int i = 0 ; i < l ;i++)
    {
        for (int j =0 ; j < L ; j++)
        {
            frame_buffer[i][j] = 0 ;  
        }
    }
}
int init_video() 
{ 
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Window initialization
    window = SDL_CreateWindow("SDL2 64x32 Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screen_width, screen_length,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_SetWindowTitle(window, "Chip8");

    // Renderer initialization
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Surface initialization
    SDL_Surface* whiteSurface = SDL_CreateRGBSurface(0, 8, 8, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_Surface* blackSurface = SDL_CreateRGBSurface(0, 8, 8, 32, 0x00, 0x00, 0x00, 0x00);
    if (whiteSurface == NULL || blackSurface == NULL)
    {
        printf("Surfaces couldn't be created !SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
    } 
    SDL_FillRect(whiteSurface, NULL, SDL_MapRGB(whiteSurface->format, 0xFF, 0xFF, 0xFF));  // White pixel
    SDL_FillRect(blackSurface, NULL, SDL_MapRGB(blackSurface->format, 0x00, 0x00, 0x00));  // Black pixel

    WhiteTexture = SDL_CreateTextureFromSurface(renderer, whiteSurface);
    BlackTexture = SDL_CreateTextureFromSurface(renderer, blackSurface);
    if (WhiteTexture == NULL || BlackTexture == NULL)
    {
        printf("Textures couldn't be created !SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
    } 
    SDL_FreeSurface(whiteSurface);
    SDL_FreeSurface(blackSurface);
} 

void DrawPixel(uint8_t x , uint8_t y, uint8_t color) {
    
    SDL_Rect pixel;
    pixel.x = x*8;
    pixel.y = y*8;
    pixel.w = 8;
    pixel.h = 8;
    if (color == WHITE){
    SDL_RenderCopy(renderer,WhiteTexture,NULL,&pixel);
    }
    else if (color == BLACK)
    {
    SDL_RenderCopy(renderer,BlackTexture,NULL,&pixel);
    }
}

void clear_screen()
{
    init_framebuffer();
}

void update_screen()
{

     for (int i =0 ; i < l ;i++)
     {
        for (int j=0 ; j < L ; j++)
        {
            DrawPixel(i,j,frame_buffer[i][j]);
        }
     }
     SDL_RenderPresent(renderer); 
}