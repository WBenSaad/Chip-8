#include "keyboard.h"
#include <SDL.h>

Keyboard_init()
{
    for (int i = 0; i < 16; ++i) 
    {
        Keyboard[i].Key_previous_state = 0;
        Keyboard[i].Key_current_state = 0;
    }

}
update_key_state(SDL_Event event)
{
            
            switch (event.key.keysym.sym) 
            {
                case  SDLK_x :
                {
                    Keyboard[0].Key_previous_state = Keyboard[0].Key_current_state ;
                    Keyboard[0].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;
                    break; 
                }
                case  SDLK_1 :
                {
                    Keyboard[1].Key_previous_state = Keyboard[1].Key_current_state ;
                    Keyboard[1].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ; 
                    break; 
                }
                case  SDLK_2 :
                {
                    Keyboard[2].Key_previous_state = Keyboard[2].Key_current_state ;
                    Keyboard[2].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break; 
                }   
                case  SDLK_3 :
                {
                    Keyboard[3].Key_previous_state = Keyboard[3].Key_current_state ;
                    Keyboard[3].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break;
                }
                case  SDLK_q :
                {
                    Keyboard[4].Key_previous_state = Keyboard[4].Key_current_state ;
                    Keyboard[4].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break;
                }
                case  SDLK_w :
                {
                    Keyboard[5].Key_previous_state = Keyboard[5].Key_current_state ;
                    Keyboard[5].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break;
                }
                case  SDLK_e :
                {
                    Keyboard[6].Key_previous_state = Keyboard[6].Key_current_state ;
                    Keyboard[6].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break;
                }
                case  SDLK_a :
                {
                    Keyboard[7].Key_previous_state = Keyboard[7].Key_current_state ;
                    Keyboard[7].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break;
                }
                case  SDLK_s :
                {
                    Keyboard[8].Key_previous_state = Keyboard[8].Key_current_state ;
                    Keyboard[8].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break;
                }
                case  SDLK_d :
                {
                    Keyboard[9].Key_previous_state = Keyboard[9].Key_current_state ;
                    Keyboard[9].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                    break;
                }
                case  SDLK_z :
                {
                Keyboard[10].Key_previous_state = Keyboard[10].Key_current_state ;
                Keyboard[10].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                break; 
                }
                case  SDLK_c :
                {
                Keyboard[11].Key_previous_state = Keyboard[11].Key_current_state ;
                Keyboard[11].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ; 
                break; 
                }
                case  SDLK_4 :
                {
                Keyboard[12].Key_previous_state = Keyboard[12].Key_current_state ;
                Keyboard[12].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ; 
                break; 
                }
                case  SDLK_r :
                {
                Keyboard[13].Key_previous_state = Keyboard[13].Key_current_state ;
                Keyboard[13].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ; 
                break; 
                }
                case  SDLK_f :
                {
                Keyboard[14].Key_previous_state = Keyboard[14].Key_current_state ;
                Keyboard[14].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ; 
                break; 
                }
                case  SDLK_v :
                {
                Keyboard[15].Key_previous_state = Keyboard[15].Key_current_state ;
                Keyboard[15].Key_current_state  = (event.type == SDL_KEYDOWN) ? 1 : 0 ;  
                break;
                } 
            default :
            break ;
            }
}

wait_key_press(SDL_Event e)
{
   
   while (!key_press_wait_event)
   { 
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                Quit();
            }
            else if (e.type == SDL_KEYDOWN)
            {
                update_key_state(e);
            }
            else if (e.type == SDL_KEYUP)
            {
                update_key_state(e);
                key_press_wait_event = 1 ;
            } 
        }
   }
}