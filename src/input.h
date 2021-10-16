#ifndef INPUT_H
#define INPUT_H
#include <genesis.h>
void initJoyHandler();
void joyHandler( u16 joy, u16 changed, u16 state);
#endif