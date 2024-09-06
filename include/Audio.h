#if !defined(AUDIO_H)
#define AUDIO_H

#include <SDL.h>

SDL_AudioDeviceID dev ;

void audio_init();
void audio_play();
void audio_pause();




#endif AUDIO_H