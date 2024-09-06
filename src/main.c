#include <main.h>


#define FPS 16 
#define CPUSPEED 4 
#define INSTRUCTIONS_PER_REFRESH_CYCLE  50

void poll_inputs()
{
    while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                update_key_state(event);
            }
        }
}

uint8_t load_rom(char* rom_name){

    FILE *rom = NULL ;
    rom = fopen(rom_name,"rb");
    if (rom != NULL)
    {
        fread(&cpu.memory[START_ADDRESS],sizeof(uint8_t)*(MEMORY_MAX - START_ADDRESS),1,rom);
        fclose(rom);
        cpu.pc =START_ADDRESS;
        return 1 ;
    }
    else
    {
        return 0 ;
    }
}
void Quit()
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
            uint8_t result  = executeOpcode(Opcode);
            if (!result)
            {
                quit = 1 ;
                break ;   
            }
            // After Drawing a sprite we leave the execution loop to ensure that we Draw one Sprite per frame refresh
            if (wait_state == 1)
            {
                break ;
            }
        }
        execute_Code = 0 ;
    }
}
int main(int argc, char* argv[]) {

    quit = 0;
    cpu_init();
    video_init();
    Keyboard_init();
    audio_init();
    timer_init();
    if (argc < 2) 
    {
        printf("No Rom name provided.\n");
        quit = 1 ;
    }
    if(!load_rom(argv[1]))
    {
        Quit();
    }
    timer_start();
    while (!quit) 
    {
        poll_inputs() ;
        execute_rom();
        (cpu.sound_timer > 0) ? audio_play() : audio_pause() ;
    }
    Quit();
    return 0;
}
