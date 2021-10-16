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
           myChip8.key[0x1]=1;
		}
		else if (state & BUTTON_DOWN)
		{
            myChip8.key[0x5]=1;
        }
        else if (state & BUTTON_LEFT){
           myChip8.key[0x4]=1;

        }
        else if (state & BUTTON_RIGHT){
            myChip8.key[0x6]=1;
        }
        else if (state & BUTTON_A){
            myChip8.key[0x0]=1;
        }
        else if (state & BUTTON_B){
            myChip8.key[0x2]=1;
        }
        else if (state & BUTTON_C){
            myChip8.key[0x3]=1;
        }
        else if (state & BUTTON_START){

        }
	}
}