#include "Audio.h"

void audioCallback(void* userdata, float* stream, int len)
{

    int samples = len / sizeof(float);
    for (int i = 0 ; i < samples ; i++)
    {
        stream[i]= 2 * SDL_sinf(2* M_PI * i / 1000);
    }

}
void audio_pause()
{

    SDL_PauseAudioDevice(dev, SDL_TRUE);

}
void audio_play()
{

    SDL_PauseAudioDevice(dev, SDL_FALSE);

}
void audio_init()
{

    if (SDL_Init(SDL_INIT_AUDIO) < 0) 
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_AudioSpec spec;

    SDL_memset(&spec, 0, sizeof(spec));

    spec.freq = 96000; // 96 000 Hz(standard) 
    spec.format = AUDIO_F32SYS;
    spec.channels = 1; // mono
    spec.samples = 4096; 
    spec.callback = audioCallback ;

    dev = SDL_OpenAudioDevice(NULL, 0, &spec, &spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);

}