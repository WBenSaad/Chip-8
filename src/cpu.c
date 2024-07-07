#include "cpu.h"

void initiliaze_cpu(){

    for (int i=0 ; i < MEMORY_MAX ;i++)
    {
        cpu.memory[i]=0;
    }
    cpu.pc = START_ADDRESS;
    for (int i=0 ; i < 16 ; i++)
    {
        cpu.V[i]=0;
    }
    for (int i = 0 ; i < 16 ;i++)
    {
        cpu.stack[i]=0;
    }
    cpu.nested_call=0;
    cpu.sp=0;
    cpu.delay_timer=0;
    cpu.sound_timer=0;
} 

void decrement(){

    if (cpu.delay_timer > 0){
        cpu.delay_timer --;
    }
    if (cpu.sound_timer > 0){
        cpu.sound_timer --;
    }
}

uint16_t getOpcode()
{

    return (cpu.memory[cpu.pc] << 8 + cpu.memory[cpu.pc+1]);

}
uint8_t getRegisterXnumber(uint16_t Opcode)
{

    return ((Opcode & 0x0F00) >> 8) ;

}
uint8_t getRegisterYnumber(uint16_t Opcode)
{

    return ((Opcode & 0x00F0) >> 4) ;

}
void init_Opcodetable()
{

  jp.mask[0]= 0x0000; jp.id[0]=0x0FFF;          /* 0NNN */ 
  jp.mask[1]= 0xFFFF; jp.id[1]=0x00E0;          /* 00E0 */ 
  jp.mask[2]= 0xFFFF; jp.id[2]=0x00EE;          /* 00EE */ 
  jp.mask[3]= 0xF000; jp.id[3]=0x1000;          /* 1NNN */ 
  jp.mask[4]= 0xF000; jp.id[4]=0x2000;          /* 2NNN */ 
  jp.mask[5]= 0xF000; jp.id[5]=0x3000;          /* 3XNN */ 
  jp.mask[6]= 0xF000; jp.id[6]=0x4000;          /* 4XNN */ 
  jp.mask[7]= 0xF00F; jp.id[7]=0x5000;          /* 5XY0 */ 
  jp.mask[8]= 0xF000; jp.id[8]=0x6000;          /* 6XNN */ 
  jp.mask[9]= 0xF000; jp.id[9]=0x7000;          /* 7XNN */ 
  jp.mask[10]= 0xF00F; jp.id[10]=0x8000;          /* 8XY0 */ 
  jp.mask[11]= 0xF00F; jp.id[11]=0x8001;          /* 8XY1 */ 
  jp.mask[12]= 0xF00F; jp.id[12]=0x8002;          /* 8XY2 */ 
  jp.mask[13]= 0xF00F; jp.id[13]=0x8003;          /* BXY3 */ 
  jp.mask[14]= 0xF00F; jp.id[14]=0x8004;          /* 8XY4 */ 
  jp.mask[15]= 0xF00F; jp.id[15]=0x8005;          /* 8XY5 */ 
  jp.mask[16]= 0xF00F; jp.id[16]=0x8006;          /* 8XY6 */ 
  jp.mask[17]= 0xF00F; jp.id[17]=0x8007;          /* 8XY7 */ 
  jp.mask[18]= 0xF00F; jp.id[18]=0x800E;          /* 8XYE */ 
  jp.mask[19]= 0xF00F; jp.id[19]=0x9000;          /* 9XY0 */ 
  jp.mask[20]= 0xF000; jp.id[20]=0xA000;          /* ANNN */ 
  jp.mask[21]= 0xF000; jp.id[21]=0xB000;          /* BNNN */ 
  jp.mask[22]= 0xF000; jp.id[22]=0xC000;          /* CXNN */ 
  jp.mask[23]= 0xF000; jp.id[23]=0xD000;          /* DXYN */ 
  jp.mask[24]= 0xF0FF; jp.id[24]=0xE09E;          /* EX9E */ 
  jp.mask[25]= 0xF0FF; jp.id[25]=0xE0A1;          /* EXA1 */ 
  jp.mask[26]= 0xF0FF; jp.id[26]=0xF007;          /* FX07 */ 
  jp.mask[27]= 0xF0FF; jp.id[27]=0xF00A;          /* FX0A */ 
  jp.mask[28]= 0xF0FF; jp.id[28]=0xF015;          /* FX15 */ 
  jp.mask[29]= 0xF0FF; jp.id[29]=0xF018;          /* FX18 */ 
  jp.mask[30]= 0xF0FF; jp.id[30]=0xF01E;          /* FX1E */ 
  jp.mask[31]= 0xF0FF; jp.id[31]=0xF029;          /* FX29 */ 
  jp.mask[32]= 0xF0FF; jp.id[32]=0xF033;          /* FX33 */ 
  jp.mask[33]= 0xF0FF; jp.id[33]=0xF055;          /* FX55 */ 
  jp.mask[34]= 0xF0FF; jp.id[34]=0xF065;          /* FX65 */ 

}

uint8_t getOpcodenum(uint16_t Opcode)
{
    for (int i = 0 ; i < NUMOPCODES ; i++)
    {
        if (Opcode & jp.mask[i] == jp.id[i])
        {
            return i ;
        }
    }
    return 255 ;
}
void executeOpcode(uint16_t Opcode)
{
    uint8_t action = getOpcodenum(Opcode);
    switch (action)
    {
    //0nnn - SYS addr
    case (0): 
        break;
    //00E0 - CLS
    case (1):
        clear_screen(); 
        break;
    //00EE - RET
    case (2):
        if (cpu.nested_call > 0) 
        {
            cpu.pc=cpu.stack[0];
            cpu.sp--;
        }
        break;
    //1nnn - JP addr
    case (3):
        uint16_t jump_address = 0x0FFF & Opcode ;
        cpu.pc = jump_address ;
        break;
    //2nnn - CALL addr
    case (4):
        cpu.sp ++ ;
        cpu.stack[0]=cpu.pc ;
        cpu.pc = 0x0FFF & Opcode ;
        break;
    //3xkk - SE Vx, byte
    case (5):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        if (cpu.V[registerXId] == (0x00FF & Opcode))
        {
            cpu.pc += 2 ;
        }
        break;
    //4xkk - SNE Vx, byte
    case (6):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        if (cpu.V[registerXId] != (0x00FF & Opcode))
        {
            cpu.pc += 2 ;
        }
        break;
    //5xy0 - SE Vx, Vy
    case (7):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        if (registerXId == registerYId)
        {
            cpu.pc += 2 ;
        }
        break;
    //6xkk - LD Vx, byte
    case (8):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId] = (0x00FF & Opcode);
        break;
    //7xkk - ADD Vx, byte
    case (9):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId] += (0x00FF & Opcode);
        break;
    //8xy0 - LD Vx, Vy
    case (10):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] = cpu.V[registerYId] ;
        break;
    //8xy1 - OR Vx, Vy
    case (11):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] |= cpu.V[registerYId] ;
        break;
    //8xy2 - AND Vx, Vy
    case (12):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] &= cpu.V[registerYId] ;
        break;
    //8xy3 - XOR Vx, Vy
    case (13):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] ^= cpu.V[registerYId] ;
        break;
    //8xy4 - ADD Vx, Vy
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        if (cpu.V[registerXId] + cpu.V[registerYId] > 255)
        {
            cpu.V[registerXId] = 0xFFFF ;
            cpu.V[F] = 1 ;
        }
        else 
        {
            cpu.V[registerXId] += cpu.V[registerYId] ;
        }
    //8xy5 - SUB Vx, Vy [TO BE DONE]
    case (14):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        int8_t temp = cpu.V[registerXId] - cpu.V[registerYId] ;
        cpu.V[registerXId] =  temp ;
        cpu.V[F] = (temp < 0) ? 0 : 1 ;     
        break;
    //8xy6 - SHR Vx {, Vy}
    case (15):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[F] = (cpu.V[registerXId] & (uint16_t) 0x01) ? 1 : 0 ;
        cpu.V[registerXId] = cpu.V[registerXId] >> 2 ;
        break;
    //8xy7 - SUBN Vx, Vy
    case (16):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        int8_t temp = cpu.V[registerYId] - cpu.V[registerXId] ;
        cpu.V[registerXId] =  temp ;
        cpu.V[F] = (temp < 0) ? 0 : 1 ;   
        break;
    //8xyE - SHL Vx {, Vy}
    case (17):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[F] = (cpu.V[registerXId] >> 15 ) ? 1 : 0 ;
        cpu.V[registerXId] = cpu.V[registerXId] << 2 ;
        break;
    //9xy0 - SNE Vx, Vy
    case (18):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        if (cpu.V[registerXId] != cpu.V[registerYId])
        {
            cpu.pc +=2 ;
        }
        break;
    //Annn - LD I, addr
    case (19):
        cpu.V[I] = (Opcode & 0x0FFF) ;
        break;
    //Bnnn - JP V0, addr
    case (20):
        cpu.pc = (Opcode & 0x0FFF) + cpu.V[0];
        break;
    //Cxkk - RND Vx, byte [TO DO]
    case (21):
        uint8_t rand = 10 ; // This needs to be implemented ;
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId] = (Opcode & 0x00FF) & rand ;
        break;
    //Dxyn - DRW Vx, Vy, nibble  [TO DO]
    case (22):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        uint8_t number_bytes = Opcode & 0x000F ;
        //uint8_t* address = cpu.V[I];
        for (int i=0 ; i <number_bytes ; i++ )
        {

        }
        break;
    //Ex9E - SKP Vx
    case (23):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t key_number  = cpu.V[registerXId];
        if (Keyboard[key_number] == KEY_PRESSED ) // To be implemented
        {
            cpu.pc +=2 ;
        }
        break;
    //ExA1 - SKNP Vx
    case (24):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t key_number  = cpu.V[registerXId];
        if (Keyboard[key_number] == KEY_NOT_PRESSED ) // To be implemented
        {
            cpu.pc +=2 ;
        }
        break;
    //Fx07 - LD Vx, DT
    case (25):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId ] = cpu.delay_timer ;
        break;
    //Fx0A - LD Vx, K
    case (26):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        while (!Key_event.Keyboard_event) ;
        cpu.V[registerXId] =Keyboard[Key_event.Key_index];
        break;
    //Fx15 - LD DT, Vx
    case (27):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.delay_timer = cpu.V[registerXId] ;
        break;
    //Fx18 - LD ST, Vx
    case (28):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.sound_timer = cpu.V[registerXId] ;
        break;
    //Fx1E - ADD I, Vx
    case (29):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[I] += cpu.V[registerXId] ;
        break;
    //Fx29 - LD F, Vx
    case (30):
        break;
    //Fx33 - LD B, Vx
    case (31):
        break;
    //Fx55 - LD [I], Vx
    case (32):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t address = cpu.V[I];
        for (int i = 0 ; i < registerXId ; i++  )
        {
            cpu.memory[address + i] = cpu.V[i] ;
        }
        cpu.V[I] += (registerXId + 1) ; 
        break;
    //Fx65 - LD Vx, [I]
    case (33):
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t address = cpu.V[I];
        for (int i = 0 ; i < registerXId ; i++  )
        {
            cpu.V[i] = cpu.memory[address + i] ;
        }
        cpu.V[I] += (registerXId + 1) ; 
        break;
        break;
    case (34):
        break;
    default:
        break;
    }

}
