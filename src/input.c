#include "input.h"
void initJoyHandler(){
	JOY_init();
	JOY_setEventHandler( &joyHandler );
}

void joyHandler( u16 joy, u16 changed, u16 state){

	if (joy == JOY_1)
	{
        clearkeys();
		if (state & BUTTON_UP)
		{
           myChip8.key[UP]=1;
		}
		else if (state & BUTTON_DOWN)
		{
            myChip8.key[DOWN]=1;
        }
        else if (state & BUTTON_LEFT){
           myChip8.key[LEFT]=1;

        }
        else if (state & BUTTON_RIGHT){
            myChip8.key[RIGHT]=1;
        }
        else if (state & BUTTON_A){
            myChip8.key[A]=1;
        }
        else if (state & BUTTON_B){

            myChip8.key[B]=1;
        }
        else if (state & BUTTON_C){

            myChip8.key[C]=1;
        }
        else if (state & BUTTON_START){

        }
	}
}