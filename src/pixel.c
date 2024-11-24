#include "pixel.h"

uint32_t pixel_buffer[FRAME_WIDTH * FRAME_HEIGHT];
uint8_t planes[NUM_PLANES] = {0};

void plane_clear(int plane)
{
    for (int i = 0 ; i < FRAME_WIDTH ;i++)
    {
        for (int j =0 ; j < FRAME_HEIGHT ; j++)
        {
            frame_buffer[plane][i][j] = 0 ;  
        }
    }
}

void framebuffer_init()
{
    for (int i = 0 ; i < 4 ; i++)
    {
        plane_clear(i);
    }
}

int video_init() 
{ 
    /* By Default frame buffer should be 64x32 */
    Resolution = LORES ;

    /* By Default only plane 1 is active */
    planes[0] = 1 ;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Window initialization
    window = SDL_CreateWindow("Chip8",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screen_width, screen_length,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Renderer initialization
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    ScreenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_STREAMING, 128, 64);

    // Create texture for pixel rendering
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 0);
    if (surface == NULL) 
    {
        printf("Unable to create surface! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    
    PixelTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (PixelTexture == NULL) 
    {
        printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_FreeSurface(surface);    
}

void DrawPixel(uint8_t x , uint8_t y, uint8_t color_index) 
{
    /*
    uint32_t* pixels;
    int pitch;
    SDL_LockTexture(ScreenTexture, NULL, (void**)&pixels, &pitch);

    unsigned int color = Palette[color_index];
    pixels[y * FRAME_WIDTH + x] = color;
    SDL_UnlockTexture(ScreenTexture);
    */
    pixel_buffer[y * FRAME_WIDTH + x] = Palette[color_index];

    
}
    /*
    SDL_Rect pixel;
    pixel.x = x*8;
    pixel.y = y*8;
    pixel.w = 8;
    pixel.h = 8;
    
    unsigned int color = Palette[color_index];
    uint8_t r = (color >> 16) & 0xFF; // Extract Red
    uint8_t g = (color >> 8) & 0xFF;  // Extract Green
    uint8_t b = color & 0xFF;         // Extract Blue
    

    SDL_SetTextureColorMod(PixelTexture, r, g, b);
    SDL_RenderCopy(renderer,PixelTexture, NULL, &pixel);
    
}*/

void clear_screen()
{
    framebuffer_init();
}

void update_screen()
{
    uint8_t color = 0;
    for (int i =0 ; i < FRAME_WIDTH ;i++)
    {
        for (int j=0 ; j < FRAME_HEIGHT ; j++)
        {
            color = frame_buffer[3][i][j] << 3 | frame_buffer[2][i][j] << 2 | frame_buffer[1][i][j] << 1 | frame_buffer[0][i][j] ;
            DrawPixel(i,j,color);
        }
    }
    //SDL_RenderCopy(renderer, ScreenTexture, NULL, NULL);
    SDL_UpdateTexture(ScreenTexture, NULL, pixel_buffer, FRAME_WIDTH * sizeof(uint32_t));
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = screen_width;
    dstRect.h = screen_length;

    // Render the scaled texture
    SDL_RenderCopy(renderer, ScreenTexture, NULL, &dstRect);
    SDL_RenderPresent(renderer); 
}
