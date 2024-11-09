#include "cpu.h"
#include "stdint.h"
#include "stdio.h"


void cpu_init(){

    for (int i=START_ADDRESS ; i < MEMORY_MAX ;i++)
    {
        cpu.memory[i]=0;
    }
    for (int i=0 ; i < sizeof(default_sprites) ; i++)
    {
        cpu.memory[DEFAULT_SPRITE_ADDRESS + i] = default_sprites[i];
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
    cpu.I = 0 ;
    cpu.sp = 0;
    cpu.delay_timer=0;
    cpu.sound_timer=0;

    #if (defined(XOCHIP) || defined(SCHIP))
    for (int i = 0 ; i < sizeof(BigFont) ; i++)
    {
        cpu.memory[DEFAULT_SPRITE_ADDRESS + sizeof(default_sprites) + i] = BigFont[i]; 
    }
    for (int i = 0 ; i < 16 ;i++)
    {
        cpu.RPL[i]=0;
    }
    #endif
    Opcodetable_init();
} 

void timer_decrement(){

    if (cpu.delay_timer > 0){
        cpu.delay_timer --;
    }
    if (cpu.sound_timer > 0){
        cpu.sound_timer --;
    }
}

uint16_t getOpcode()
{

    return (cpu.memory[cpu.pc] << 8 | cpu.memory[cpu.pc+1]);

}
uint8_t getRegisterXnumber(uint16_t Opcode)
{

    return ((Opcode & 0x0F00) >> 8) ;

}
uint8_t getRegisterYnumber(uint16_t Opcode)
{

    return ((Opcode & 0x00F0) >> 4) ;

}
void Opcodetable_init()
{
  jp.mask[0]= 0x0000; jp.id[0]=0xFFFF;          /* 0NNN */ 
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
  jp.mask[23]= 0xF0FF; jp.id[23]=0xF085;          /* Fx85 */ 
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
  /*NEW STUFF*/
  jp.mask[35]= 0xFFF0; jp.id[35]=0x00C0;          /* 00CN */ 
  jp.mask[36]= 0xFFF0; jp.id[36]=0x00D0;          /* 00DN */ 
  jp.mask[37]= 0xFFFF; jp.id[37]=0x00FB;          /* 00FB */ 
  jp.mask[38]= 0xFFFF; jp.id[38]=0x00FC;          /* 00FC */ 
  jp.mask[39]= 0xFFFF; jp.id[39]=0x00FD;          /* 00FD */ 
  jp.mask[40]= 0xFFFF; jp.id[40]=0x00FE;          /* 00FE */ 
  jp.mask[41]= 0xFFFF; jp.id[41]=0x00FF;          /* 00FF */ 
  jp.mask[42]= 0xF00F; jp.id[42]=0x5002;          /* 5xy2 */ 
  jp.mask[43]= 0xF00F; jp.id[43]=0x5003;          /* 5xy3 */ 
  jp.mask[44]= 0xF00F; jp.id[44]=0xD000;          /* Dxy0 */ 
  jp.mask[45]= 0xF000; jp.id[45]=0xD000;          /* DXYN */ 
  jp.mask[46]= 0xFFFF; jp.id[46]=0xF000;          /* F000 */
  jp.mask[47]= 0xF0FF; jp.id[47]=0xF001;          /* Fx01 */ 
  jp.mask[48]= 0xFFFF; jp.id[48]=0xF002;          /* F002 */ 
  jp.mask[49]= 0xF0FF; jp.id[49]=0xF030;          /* Fx30 */ 
  jp.mask[50]= 0xF0FF; jp.id[50]=0xF03A;          /* Fx3A */ 
  jp.mask[51]= 0xF0FF; jp.id[51]=0xF075;          /* Fx75 */  
}

uint8_t getOpcodenum(uint16_t Opcode)
{
    for (int i = 0 ; i < NUMOPCODES ; i++)
    {
        if ((Opcode & jp.mask[i]) == jp.id[i])
        {
            return i ;
        }
    }
    return 255 ;
}
uint8_t executeOpcode(uint16_t Opcode)
{

    uint8_t action = getOpcodenum(Opcode);
    switch (action)
    {
    //0nnn - SYS addr
    case (0): 
        break;
    //00E0 - CLS
    case (1):
        for (int i = 0 ; i < NUM_PLANES ; i++)
        {
            if (planes[i] == 1)
            {
                plane_clear(i);
            }
        }
        break;
    //00EE - RET
    case (2):
        if (cpu.sp > 0) 
        {
            cpu.pc=cpu.stack[0];
            cpu.sp--;
            for (int i = 0 ; i < 15 ; i++) 
            {
                cpu.stack[i]=cpu.stack[i+1];
            }
        }
        break;
    //1nnn - JP addr
    case (3):
        jump_address = 0x0FFF & Opcode ;
        cpu.pc = jump_address ;
        cpu.pc -=2 ; 
        break;
    //2nnn - CALL addr
    case (4):
        for (int i = 15 ; i > 0 ; i--)
        {
            cpu.stack[i] = cpu.stack[i-1];
        }
        cpu.stack[0]=cpu.pc;
        cpu.sp ++ ;
        cpu.pc = 0x0FFF & Opcode ;
        cpu.pc -=2 ;
        break;
    //3xkk - SE Vx, byte
    case (5):
        registerXId = getRegisterXnumber(Opcode) ;
        if (cpu.V[registerXId] == (0x00FF & Opcode))
        {
            cpu.pc += 2 ;
        }
        break;
    //4xkk - SNE Vx, byte
    case (6):
        registerXId = getRegisterXnumber(Opcode) ;
        if (cpu.V[registerXId] != (0x00FF & Opcode))
        {
            cpu.pc += 2 ;
        }
        break;
    //5xy0 - SE Vx, Vy
    case (7):
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        if (cpu.V[registerXId] == cpu.V[registerYId])
        {
            cpu.pc += 2 ;
        }
        break;
    //6xkk - LD Vx, byte
    case (8):
        registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId] = (0x00FF & Opcode);
        break;
    //7xkk - ADD Vx, byte
    case (9):
        registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId] += (0x00FF & Opcode);
        break;
    //8xy0 - LD Vx, Vy
    case (10):
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] = cpu.V[registerYId] ;
        break;
    //8xy1 - OR Vx, Vy
    case (11):
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] |= cpu.V[registerYId] ;
        /* COSMAC based variants will reset VF */
        #if defined(CHIP8)
        cpu.V[F] = 0 ;
        #endif
        break;
    //8xy2 - AND Vx, Vy
    case (12):
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] &= cpu.V[registerYId] ;
        /* COSMAC based variants will reset VF */
        #if defined(CHIP8)
        cpu.V[F] = 0 ;
        #endif
        break;
    //8xy3 - XOR Vx, Vy
    case (13):
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        cpu.V[registerXId] ^= cpu.V[registerYId] ;
        /* COSMAC based variants will reset VF */
        #if defined(CHIP8)
        cpu.V[F] = 0 ;
        #endif
        break;
    //8xy4 - ADD Vx, Vy
    case (14):
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        uint16_t result = cpu.V[registerXId] + cpu.V[registerYId] ;
        cpu.V[registerXId] = (0x00FF & result) ;
        cpu.V[F] = (result > 255) ? 1 : 0 ;
        break ;
    //8xy5 - SUB Vx, Vy [TO BE DONE]
    case (15):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        int8_t temp = cpu.V[registerXId] - cpu.V[registerYId] ;
        cpu.V[registerXId] =  temp ;
        cpu.V[F] = (temp < 0) ? 0 : 1 ;     
        break;
    }
    //8xy6 - SHR Vx {, Vy}
    case (16):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        #ifndef SCHIP
        cpu.V[registerXId] = cpu.V[registerYId];
        #endif
        uint8_t VF_temp = (cpu.V[registerXId] & (uint8_t) 0x1) ? 1 : 0 ;
        cpu.V[registerXId] >>=  1 ;
        cpu.V[F] = VF_temp ;
        break;
    }
    //8xy7 - SUBN Vx, Vy
    case (17):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        int8_t temp = cpu.V[registerYId] - cpu.V[registerXId] ;
        cpu.V[registerXId] =  temp ;
        cpu.V[F] = (temp < 0) ? 0 : 1 ;   
        break;
    }
    //8xyE - SHL Vx {, Vy}
    case (18):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        #ifndef SCHIP
        cpu.V[registerXId] = cpu.V[registerYId];
        #endif
        uint8_t VF_temp = (cpu.V[registerXId] >> 7) ? 1 : 0 ;
        cpu.V[registerXId] <<= 1 ;
        cpu.V[F] = VF_temp ;
        break;
    }
    //9xy0 - SNE Vx, Vy
    case (19):
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        if (cpu.V[registerXId] != cpu.V[registerYId])
        {
            cpu.pc +=2 ;
        }
        break;
    //Annn - LD I, addr
    case (20):
        cpu.I = (Opcode & 0x0FFF) ;
        break;
    //Bnnn - JP V0, addr / Bxnn - JP VX, addr
    case (21):
    {
        registerXId = getRegisterXnumber(Opcode);
        uint8_t reg = cpu.V[0];
        #if defined(SCHIP)
        reg = cpu.V[registerXId] ;
        #endif
        cpu.pc = (Opcode & 0x0FFF) + reg ;
        cpu.pc -=2 ;
        break;
    }
    //Cxkk - RND Vx, byte [TO DO]
    case (22):
    {
        uint8_t rand = 10 ; // This needs to be implemented ;
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId] = (Opcode & 0x00FF) & rand ;
        break;
    }
    //Fx85 - Read V0..VX from RPL user flags    Read V0..VX from RPL user flags
    #if (defined(XOCHIP) || defined(SCHIP))
    case (23):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        #if defined(SCHIP)
        if (cpu.V[registerXId] > 7) 
        {
            printf("Err : For SCHIP x => [0..7]");
            break ;
        }
        #endif
        for (int i = 0 ; i <= cpu.V[registerXId] ; i++)
        {
            cpu.V[i] = cpu.RPL[i] ;
        }
        break;
    }
    #endif
    //Ex9E - SKP Vx 
    case (24):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t key_index  = cpu.V[registerXId] % 16;
        if (Keyboard[key_index].Key_current_state == KEY_PRESSED )
        {
            cpu.pc +=2 ;
        }
        break;   
    }
    //ExA1 - SKNP Vx
    case (25):
    {

        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t key_index = cpu.V[registerXId] % 16;
        if ((Keyboard[key_index].Key_current_state == KEY_NOT_PRESSED)) 
        {
            cpu.pc +=2 ;
        }
        break;  
    }
    //Fx07 - LD Vx, DT
    case (26):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        cpu.V[registerXId ] = cpu.delay_timer ;
        break;
    }
    //Fx0A - LD Vx, K 
    case (27):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        key_press_wait_event = 0 ;
        wait_key_press(e);
        for (int i = 0 ; i < 16 ; i++)
        {
            if (Keyboard[i].Key_previous_state == 1)
            {
                cpu.V[registerXId] = i ;
            } 
        }
        break;
    }    
    //Fx15 - LD DT, Vx
    case (28):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        cpu.delay_timer = cpu.V[registerXId] ;
        break;
    }
    //Fx18 - LD ST, Vx
    case (29):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        cpu.sound_timer = cpu.V[registerXId] ;
        break;
    }
    //Fx1E - ADD I, Vx
    case (30):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        cpu.I +=cpu.V[registerXId] ;
        cpu.I &= 0x0FFF;  
        break;
    }
    //Fx29 - LD F, Vx  TO BE IMPLEMENTED
    case (31):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.I = DEFAULT_SPRITE_ADDRESS + (5*(cpu.V[registerXId] & 0x0F));
        break;
    }
    //Fx33 - LD B, Vx
    case (32):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        uint8_t temp = cpu.V[registerXId];
        uint8_t hundreds = 0, tens = 0, units = 0;
        uint16_t address = cpu.I;
        while(temp > 100)
        {
            temp -= 100 ;
            hundreds++ ;
        }
        while (temp > 10)
        {
            temp -= 10;
            tens++ ;
        }
        units = temp ;
        cpu.memory[ address      & 0x0FFF] = hundreds ;
        cpu.memory[(address + 1) & 0x0FFF] = tens ;
        cpu.memory[(address + 2) & 0x0FFF] = units;
        break;
    }
    //Fx55 - LD [I], Vx
    case (33):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        uint16_t address = cpu.I;
        for (int i = 0 ; i <= registerXId ; i++  )
        {
            cpu.memory[(address + i) & 0x0FFF] = cpu.V[i] ;
        }
        #if !defined(SCHIP)
        cpu.I += (registerXId + 1) ;
        #endif 
        break;
    }
    //Fx65 - LD Vx, [I]
    case (34):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        uint16_t address = cpu.I;
        for (int i = 0 ; i <= registerXId ; i++  )
        {
            cpu.V[i] = cpu.memory[(address + i) & 0x0FFF] ;
        }
        #if !defined(SCHIP)
        cpu.I += (registerXId + 1) ;
        #endif 
        break;
    }
    //00CN   Scroll display N lines down
    #if (defined(XOCHIP) || defined(SCHIP))
    case (35):
    {
        uint8_t pixels_to_scroll = Opcode & (0xF) ;
        #if defined (XOCHIP)
        if (Resolution == LORES)
        {
           pixels_to_scroll *= 2 ;
        } 
        #endif
        for (int current_plane = 0 ; current_plane < NUM_PLANES ; current_plane++)
        {
            if (planes[current_plane] == 1)
            {   
                for (int x = 0 ; x < FRAME_WIDTH ; x++)
                {
                    for (int y = FRAME_HEIGHT-1 ; y >= 0 ; y--)
                    {
                        frame_buffer[current_plane][x][y] = (y >= pixels_to_scroll) ? frame_buffer[current_plane][x][y-pixels_to_scroll] : 0 ;
                    }
                }
            }
        }
        break ;
    }
    
    #endif
    //00Dn   Scroll screen content up N hires pixel
    #if defined(XOCHIP)
    case (36):
    {
        uint8_t pixels_to_scroll = (Opcode & (0x000F)) << Resolution ;
        for (int i = 0 ; i < NUM_PLANES ; i++)
        {
            if (planes[i] == 1)
            {
                for (int j = 0 ; j < FRAME_WIDTH ; j++ )
                {
                    for (int k=0 ; k <= FRAME_HEIGHT ; k++)
                    {

                        frame_buffer[i][j][k] = ( k <= FRAME_HEIGHT- pixels_to_scroll) ? frame_buffer[i][j][k + pixels_to_scroll] : 0 ;
                    }
                }
            }
        }
        break;
    }
    #endif
    //00FB    Scroll display 4 pixels right  
    #if (defined(XOCHIP) || defined(SCHIP))
    case (37):
    {
        uint8_t pixels_to_scroll = 4 ;
        #if defined(XOCHIP)
        if (Resolution == LORES)
        {
           pixels_to_scroll <<= 1 ;
        } 
        #endif 
        for (int i=0 ; i <NUM_PLANES ; i++)
        {
            if ( planes[i] == 1)
            {
                for (int k = 0 ; k < FRAME_HEIGHT ; k++)
                {
                    for (int j = FRAME_WIDTH - 1 ; j >= 0 ; j--)
                    {

                        frame_buffer[i][j][k] = (j >= pixels_to_scroll) ? frame_buffer[i][j-pixels_to_scroll][k] : 0;

                    }
                }
            }
        }
        break;
    }
    #endif
    //00FC    Scroll display 4 pixels left
    #if (defined(XOCHIP) || defined(SCHIP))
    case (38):
    {
        uint8_t pixels_to_scroll = 4 ;
        #if defined(XOCHIP)
        if (Resolution == LORES)
        {
           pixels_to_scroll <<= 1 ;
        } 
        #endif 
        for (int i=0 ; i <NUM_PLANES ; i++)
        {
            if ( planes[i] == 1)
            {
                for (int k = 0 ; k < FRAME_HEIGHT ; k++)
                {
                    for (int j = 0 ; j <= FRAME_WIDTH; j++)
                    {

                        frame_buffer[i][j][k] = (j <= FRAME_WIDTH - pixels_to_scroll ) ? frame_buffer[i][j+pixels_to_scroll][k] : 0 ;

                    }
                }
            }
        }
        break;
    }
    #endif
    //00FD    Exit CHIP interpreter
    #if (defined(XOCHIP) || defined(SCHIP))
    case (39):
    {
        Quit();
        break;
    }
    #endif
    //00FE    Disable extended screen mode
    #if (defined(XOCHIP) || defined(SCHIP))
    case (40):
    {
        Resolution = LORES ;
        #if defined (XOCHIP)
        clear_screen();
        #endif
        break;
    }
    #endif
    //00FF    Enable extended screen mode for full-screen graphics
    #if (defined(XOCHIP) || defined(SCHIP))
    case (41):
    {
        Resolution = HIRES ;
        #if defined (XOCHIP)
        clear_screen();
        #endif
        break;
    }
    #endif
    // Test These and F000 with ROM "An Evening To Die For"
    //5xy2 - save vX - vY
    #if defined(XOCHIP)
    case (42):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        uint16_t address = cpu.I & 0x0FFF ;
        if (registerXId > registerYId) 
        {
            for (int i = registerXId ; i > registerYId ; i--)
            {
                cpu.memory[address + i] = cpu.V[i];
            }
        }
        else 
        {
            for (int i = registerXId ; i <= registerYId ; i++ )
            {
                cpu.memory[address + i] = cpu.V[i];
            }
        }
        break;
    }
    #endif
    //5xy3 - load vX - vY
    #if defined(XOCHIP)
    case (43):
    {
        registerXId = getRegisterXnumber(Opcode) ;
        registerYId = getRegisterYnumber(Opcode) ;
        uint16_t address = cpu.I & 0x0FFF ;
        if (registerXId > registerYId) 
        {
            for (int i = registerXId ; i > registerYId ; i--)
            {
                cpu.V[i] = cpu.memory[address + i] ;
            }
        }
        else 
        {
            for (int i = registerXId ; i <= registerYId ; i++ )
            {
                cpu.V[i] = cpu.memory[address + i] ;
            }
        }
        break;
    }
    #endif
    
    //DXY0	sprite vX vY 0 CHECK if same mask !!!
    case (44):
    {
        uint8_t x,y,frame_byte,Xor_output;
        uint16_t sprite_bytes ;
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        uint16_t start_address = cpu.I;
        x = cpu.V[registerXId] ;
        y = cpu.V[registerYId] ;
        cpu.V[F]= 0 ;
        uint8_t sprite_width = 16 ;
        uint8_t Resolution_mask = 0x1 & ~Resolution ;
        uint8_t pixel_size = 1 + Resolution ;
        #if defined(SCHIP)
        if (Resolution == LORES)
        {
            sprite_width = 8 ;
        }
        #endif
        uint8_t* sprite = &(cpu.memory[start_address]);
        for (int current_plane = 0 ; current_plane < NUM_PLANES ; current_plane ++)
        {
            if (planes[current_plane] == 1)
            {    
                for (int row =0 ; row < 16 ; row++)
                {
                    #if defined(XOCHIP)
                    uint8_t yPos = (y % (32 * (1 + Resolution_mask)) + row) % (32 * (1 + Resolution_mask)) ;
                    #else
                    uint8_t yPos = (y % (32 * (1 + Resolution_mask)) + row) ;
                    if (yPos== 0x20 * (1 + Resolution_mask)){break;}
                    #endif
                    // In HIRES mode we fetch two bytes , in LORES we fetch 1 bytes
                    sprite_bytes = Resolution == LORES ? sprite[row] : ((sprite[row*2] << 8 ) | sprite[row*2+1]) ;
                    for (int col=0 ; col < 8 * (1 + Resolution_mask) ; col++)
                    {
                        #if defined(XOCHIP)
                        uint8_t xPos = ( x % (64 * (1 + Resolution_mask)) + col) % (64 * (1 + Resolution_mask)) ;
                        #else
                        uint8_t xPos = ( x % (64 * (1 + Resolution_mask)) + col) ;
                        if (xPos == 0x40*(1 + Resolution_mask)) {break;}
                        #endif
                        uint8_t frame_pixel_value  = frame_buffer[current_plane][xPos*pixel_size][yPos*pixel_size] ;
                        uint8_t sprite_pixel_value = ((sprite_bytes & (0x01 << (sprite_width-1-col))) >> (sprite_width-1-col)) ;
                        Xor_output = frame_pixel_value ^ sprite_pixel_value ;
                        
                        for (int i = 0 ; i < 2 ; i++)
                        {
                            for (int j = 0 ; j < 2 ; j++)
                            {
                                frame_buffer[current_plane][(xPos * pixel_size) + (i*Resolution)][(yPos * pixel_size) + (j*Resolution)] = Xor_output ;
                            }
                        }
                        // In case 1 Xor 1 we need to set V[F]
                        if ((Xor_output == 0 & frame_pixel_value == 1 )) 
                        {
                            cpu.V[F]= 1 ;
                        }

                    }
                }
            }
        sprite += 16 * (1 + Resolution_mask) ;
        }

        break;
    }
    //Dxyn - DRW Vx, Vy, nibble  [TO DO]
    case (45):
    {
        uint8_t x,y,sprite_byte,frame_byte,Xor_output,num_pixels_to_draw;
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        uint8_t registerYId = getRegisterYnumber(Opcode) ;
        uint8_t number_bytes = Opcode & 0x000F ;
        uint16_t start_address = cpu.I;
        uint8_t collision = 0 ;
        x = cpu.V[registerXId] ;
        y = cpu.V[registerYId] ;
        cpu.V[F]= 0 ;
        uint8_t* sprite = &(cpu.memory[start_address]);
        wait_state = 1 ;
        uint8_t Resolution_mask = 0x1 & ~Resolution ;
        /*
        printf("Opcode =%x\n",Opcode);
        printf("x =%x\n",x);
        printf("y =%x\n",y);
        printf("Resolution =%x\n",Resolution);
        fflush(stdout);
        */
        /*If LOW_RES , pixel will be stretched
        HIRES = 0 / LORES = 1 
        If in LORES mode , each "pixel" will be represented as 2x2 pixel .
        => In LORES mode , pixel_size = 2 while in HIRES mode , pixel_size = 1 ;
        */
        uint8_t pixel_size = 1 + Resolution ;
        for (int current_plane = 0 ; current_plane < NUM_PLANES ; current_plane ++)
        {
            if (planes[current_plane] == 1)
            {    
                for (int row=0 ; row < number_bytes ; row++ )
                {
                    /* For XO-CHIP and SCHIP wrap instead of clipping
                    If HIRES mode wrap around 64 , IF LORES mode wrap around 32
                    yPos and xPos will depend on the Resolution (HIRES/LORES) variable .
                    */
    
                    #if  (defined(XOCHIP))
                    uint8_t yPos = (y % (32 * (1 + Resolution_mask)) + row) % (32 * (1 + Resolution_mask)) ;
                    //uint8_t yPos = (y % 64 + row) % 64 ;
                    #else 
                    uint8_t yPos = (y % (32 * (1 + Resolution_mask)) + row) ;
                    if (yPos== 0x20 * (1 + Resolution_mask)){break;}
                    #endif
                    sprite_byte = sprite[row];
                    /*
                    if (Resolution == HIRES) 
                    {
                        num_pixels_to_draw = (128 - x >= 8) ? 8 : 128 - x ;
                    }
                    else 
                    {
                        num_pixels_to_draw = (64 - x >= 8) ? 8 : 64 - x ;
                    }
                    */
                    for (int col=0 ; col < 8 ; col++)
                    {
                        
                        // For XO-CHIP / SCHIP wrap instead of clipping
                        #if  defined(XOCHIP)
                        uint8_t xPos = ( x % (64 * (1 + Resolution_mask)) + col) % (64 * (1 + Resolution_mask)) ;
                        #else
                        uint8_t xPos = ( x % (64 * (1 + Resolution_mask)) + col);
                        if (xPos == 0x40*(1 + Resolution_mask)) {break;}
                        #endif
                        uint8_t frame_pixel_value  = frame_buffer[current_plane][xPos*pixel_size][yPos*pixel_size] ;
                        /*
                            1 - Retrieve value of the wanted Pixel
                            2 - Shift the result to the first digit  
                        */
                        uint8_t sprite_pixel_value = ((sprite_byte & (0x01 << (7-col))) >> (7-col)) ;
                        Xor_output = frame_pixel_value ^ sprite_pixel_value ;
                        
                        /*
                            By Default Screen is 128x64 , However for both LORES and Chip8 , the screen is 64x32
                            In those case pixels are represented by 2x2 on-screen pixels 
                        */
                        for (int i = 0 ; i < 2 ; i++)
                        {
                            for (int j = 0 ; j < 2 ; j++)
                            {
                                frame_buffer[current_plane][(xPos * pixel_size) + (i*Resolution)][(yPos * pixel_size) + (j*Resolution)] = Xor_output ;
                            }
                        }
                        // In case 1 Xor 1 we need to set V[F]
                        if ((Xor_output == 0 & frame_pixel_value == 1 )) 
                        {
                            cpu.V[F]= 1 ;
                        }
                    }
                }
            /*If Mutiple drawing planes are selected , the each plane will consume the same amount of bytes */    
            sprite += number_bytes ;
            }
        }
        break;
    }
    #if defined(XOCHIP)
    //F000	i := long NNNN
    case (46):
    {
        cpu.I = (cpu.memory[cpu.pc + 2] << 8 | cpu.memory[cpu.pc + 3]) ;
        cpu.pc +=2 ;
        break;
    }
    #endif
    #if defined(XOCHIP)
    //Fx01 - plane X
    case (47):
    {
        active_planes = getRegisterXnumber(Opcode) ;
        int i = 0 ;
        while (i < 4)
        {
            planes[i] = (active_planes >> i ) & 0x01 ; 
        }
        break;
    }
    #endif
    #if defined(XOCHIP)
    //F002 - audio
    case (48):
    {
        break ;
    }
    #endif
    //Fx30 - Point I to 10-byte font sprite
    case (49):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        cpu.I = DEFAULT_SPRITE_ADDRESS + sizeof(default_sprites) +(10*(cpu.V[registerXId] & 0x0F));
        break;
        break;
    }
    //Fx3A - pitch := vX
    case (50):
    {
        break;
    }
    #if (defined(XOCHIP) || defined(SCHIP))
    //Fx75 - Store V0..VX in RPL user flags
    case (51):
    {
        uint8_t registerXId = getRegisterXnumber(Opcode) ;
        #if defined(SCHIP)
        if (cpu.V[registerXId] > 7) 
        {
            printf("Err : For SCHIP x => [0..7]");
            break ;
        }
        #endif
        for (int i = 0 ; i <= cpu.V[registerXId] ; i++)
        {
            cpu.RPL[i] = cpu.V[i] ;
        }
        break;
    }
    #endif
    default:
        printf("Unsupported Opcode : %x\n",Opcode);
        return 0 ;
        break;
    }
    cpu.pc +=2 ;
    return (1);
}
