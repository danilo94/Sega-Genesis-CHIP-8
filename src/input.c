#include "input.h"
void initJoyHandler(){
	JOY_init();
	JOY_setEventHandler( &joyHandler );
}

void joyHandler( u16 joy, u16 changed, u16 state){
    u16 key =0x0;
	if (joy == JOY_1)
	{
        clearkeys();
		if (state & BUTTON_UP)
		{
            key = UP;
		}
		else if (state & BUTTON_DOWN)
		{
            key = DOWN;
        }
        else if (state & BUTTON_LEFT){
           key = LEFT; 
        }
        else if (state & BUTTON_RIGHT){
            key = RIGHT; 
        }
        else if (state & BUTTON_A){
            key = A; 
        }
        else if (state & BUTTON_B){
            key = B;
        }
        else if (state & BUTTON_C){
            key =C;
        }
        else if (state & BUTTON_START){
            key = RESET;
        }
        if (myGameController.gameInProgress){
            if (key != RESET){
                myChip8.key[key]=1;
            }
            else{
                moveMenuCursor(key);
            }
        }
        else{
            moveMenuCursor(key);
        }
	}
}