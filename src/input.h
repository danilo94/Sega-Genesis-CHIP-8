#ifndef INPUT_H
#define INPUT_H
#include <genesis.h>
#include "chip8.h"


#define UP 0x8
#define DOWN 0x2
#define LEFT 0x4

#define RIGHT 0x6
#define A 0x5
#define B 0x2

#define C 0x3



void initJoyHandler();
void joyHandler( u16 joy, u16 changed, u16 state);
#endif