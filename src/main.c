#include <main.h>


#define FPS 16 
#define CPUSPEED 4 
#define INSTRUCTIONS_PER_REFRESH_CYCLE  50
SDL_Event event ;
uint8_t execute_Code = 1 ;

int quit;
int i = 0 ;
uint32_t timer_callback (uint32_t interval , void* param)
{

    timer_decrement();
    update_screen();
    execute_Code = 1 ;
    wait_state = 0 ;
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
        return 0 ;
    }
    else
    {
        return 1 ;
    }
}
void audioCallback(void* userdata, float* stream, int len)
{

    int samples = len / sizeof(float);
    for (int i = 0 ; i < samples ; i++)
    {
        stream[i]= 2 * SDL_sinf(2* M_PI * i / 1000);
    }

}

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) 
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_AudioSpec spec;

    SDL_memset(&spec, 0, sizeof(spec));

    spec.freq = 96000; // 4 100 Hz, 48 000 Hz, 96 000 Hz, 192 000 Hz (standard) 
    spec.format = AUDIO_F32SYS;
    spec.channels = 1; // mono
    spec.samples = 4096; // Oublier pas que ce sa doit être en puissance de deux 2^n
    spec.callback = audioCallback ;

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &spec, &spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    SDL_PauseAudioDevice(dev, SDL_TRUE);
    Keyboard_init();
    init_video();
    initiliaze_cpu();
    init_Opcodetable();
    if(load_rom("Pong (1 player).ch8"))
    {
        SDL_Quitt();
    }
    SDL_AddTimer(17, timer_callback, NULL);
    quit = 0;
    while (!quit) {
        execute_rom();
        if (cpu.sound_timer > 0)
        {
            SDL_PauseAudioDevice(dev, SDL_FALSE);  
        }
        else if (cpu.sound_timer == 0)
        {
            SDL_PauseAudioDevice(dev, SDL_TRUE);
        }
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
            uint8_t result = executeOpcode(Opcode);
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