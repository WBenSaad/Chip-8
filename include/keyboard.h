#if !defined(KEYBOARD_H)
#define KEYBOARD_H

#include <stdint.h>
#include <SDL.h>
#include <main.h>

#define KEY_PRESSED             1
#define KEY_NOT_PRESSED         0

static SDL_Event e ;
static uint8_t key_press_index ;

typedef struct 
{
    uint8_t Key_previous_state ;
    uint8_t Key_current_state ;
}Keyboard_event ;

uint8_t key_press_wait_event ;

Keyboard_event Keyboard[16] ;

void Keyboard_init();
void update_key_state(SDL_Event);
void wait_key_press(SDL_Event);

#endif
