#if !defined(CPU_H)
#define CPU_H
#include <stdint.h>
#include <pixel.h>
#include <keyboard.h>
#include <main.h>


#define MEMORY_MAX                  4096
#define START_ADDRESS               0x200
#define NUMOPCODES                  35
#define DEFAULT_SPRITE_ADDRESS      0x50
#define A                           10
#define B                           11
#define C                           12
#define D                           13
#define E                           14
#define F                           15

typedef struct {

    uint8_t  memory[MEMORY_MAX] ;
    uint16_t pc ;
    uint8_t V[16] ;
    uint16_t I ;
    uint16_t stack[16];
    uint8_t nested_call ;
    uint8_t sp ;
    uint8_t delay_timer;
    uint8_t sound_timer;
}CPU;

CPU cpu ;
typedef struct {

    uint16_t mask[NUMOPCODES] ;
    uint16_t id[NUMOPCODES] ;
}JUMP ;

JUMP jp ;

uint8_t key_state ;
uint16_t jump_address;
uint8_t registerXId;
uint8_t registerYId;

void initiliaze_cpu();
void timer_decrement();
uint16_t getOpcode();
uint8_t getRegisterXnumber(uint16_t);
uint8_t getRegisterYnumber(uint16_t);
void init_Opcodetable();
uint8_t getOpcodenum(uint16_t);
uint8_t executeOpcode(uint16_t);
//uint8_t Keyboard_Pressed();
#endif // CPU_H
