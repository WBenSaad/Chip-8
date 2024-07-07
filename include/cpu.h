#if !defined(CPU_H)
#define CPU_H
#include <stdint.h>
#include <pixel.h>


#define MEMORY_MAX          4096
#define START_ADDRESS       0x200
#define NUMOPCODES          35
#define A                   10
#define B                   11
#define C                   12
#define D                   13
#define E                   14
#define F                   15
#define I                   16
/*
struct Register {
    uint8_t V0  ;
    uint8_t V1  ;
    uint8_t V2  ;  
    uint8_t V3  ;
    uint8_t V4  ;
    uint8_t V5  ;
    uint8_t V6  ;
    uint8_t V7  ;
    uint8_t V8  ;
    uint8_t V9  ;
    uint8_t VA  ;
    uint8_t VB  ;
    uint8_t VC  ;
    uint8_t VD  ;
    uint8_t VE  ;
    uint8_t VF  ;
    uint16_t I  ;
};
*/
typedef struct {

    uint8_t  memory[MEMORY_MAX] ;
    uint16_t pc ;
    uint8_t V[16] ;
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

void initiliaze_cpu();
void decrement();
uint16_t getOpcode();
uint8_t getRegisterXnumber(uint16_t);
uint8_t getRegisterYnumber(uint16_t);
void init_Opcodetable();
uint8_t getOpcodenum(uint16_t);
void executeOpcode(uint16_t);
//uint8_t Keyboard_Pressed();
#endif // CPU_H
