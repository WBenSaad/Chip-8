#if !defined(KEYBOARD_H)
#define KEYBOARD_H
#include <stdint.h>

#define KEY_PRESSED             1
#define KEY_NOT_PRESSED         0


uint8_t Keyboard[16];


typedef struct 
{
    uint8_t Keyboard_event = 0 ;
    uint8_t Key_index ;
}Keyboard_event ;

//needs to be reset after each change 
Keyboard_event Key_event ;

#endif
