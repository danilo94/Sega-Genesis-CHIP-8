	///////////////////////////////////////////////////////////////////////////////
// Project description
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// Name: myChip8
//
// Author: Laurence Muller
// Contact: laurence.muller@gmail.com
//
// License: GNU General Public License (GPL) v2 
// ( http://www.gnu.org/licenses/old-licenses/gpl-2.0.html )
//
// Copyright (C) 2011 Laurence Muller / www.multigesture.net
///////////////////////////////////////////////////////////////////////////////
#ifndef CHIP8_INCLUDE_H
#define CHIP8_INCLUDE_H
#include <genesis.h>


typedef struct {
u8 fontSet[80];
u16 opcode;
u8 memory[4096];
u8 V[16];
u16 I;
u16 pc;
u8 gfx[64*32];
u16 stack[16];
u16 sp;
u8 key[16]; 
u8 delayTimer;
u8 soundTimer;	
bool drawFlag;
u8 keyPress;
}chip8;


chip8 myChip8;
void start();
void loadGame(u8 *game, u16 gameSize);
void emulationCycle();
void clearMemory();
void clearScreen();
void initializeSystem();
void initFontSet();
void clearkeys();
void resetChip8();
#endif
