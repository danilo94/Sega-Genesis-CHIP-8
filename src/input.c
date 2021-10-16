#include "input.h"
void initJoyHandler(){
	JOY_init();
	JOY_setEventHandler( &joyHandler );
}

void joyHandler( u16 joy, u16 changed, u16 state){
	if (joy == JOY_1)
	{
		if (state & BUTTON_UP)
		{
		}
		else if (state & BUTTON_DOWN)
		{
        }
        else if (state & BUTTON_LEFT){
        }
        else if (state & BUTTON_RIGHT){
        }
        else if (state & BUTTON_A){
        }
        else if (state & BUTTON_B){
        }
        else if (state & BUTTON_C){
        }
        else if (state & BUTTON_START){

        }
	}
}