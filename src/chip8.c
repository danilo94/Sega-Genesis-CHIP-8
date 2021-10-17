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

#include "chip8.h"
#include <genesis.h>
void emulationCycle(){
  // Fetch opcode
  myChip8.opcode = myChip8.memory[myChip8.pc] << 8 | myChip8.memory[myChip8.pc + 1];
  
  // Process opcode
  switch(myChip8.opcode & 0xF000)
  {   
    case 0x0000:
      switch(myChip8.opcode & 0x000F)
      {
        case 0x0000: // 0x00E0: Clears the screen
          for(int i = 0; i < 2048; ++i){
            myChip8.gfx[i] = 0x0;
          }
          myChip8.drawFlag = TRUE;
          myChip8.pc += 2;
        break;

        case 0x000E: // 0x00EE: Returns from subroutine
          --myChip8.sp;     // 16 levels of stack, decrease stack pointer to prevent overwrite
          myChip8.pc = myChip8.stack[myChip8.sp]; // Put the stored return address from thechip8 back into the program counter         
          myChip8.pc += 2;    // Don't forget to increase the program counter!
        break;

      }
    break;

    case 0x1000: // 0x1NNN: Jumps to address NNN
      myChip8.pc = myChip8.opcode & 0x0FFF;
    break;

    case 0x2000: // 0x2NNN: Calls subroutine at NNN.
      myChip8.stack[myChip8.sp] = myChip8.pc;     // Store current address instack
      ++myChip8.sp;         // Increment stack pointer
      myChip8.pc = myChip8.opcode & 0x0FFF; // Set the program counter to the address at NNN
    break;
    
    case 0x3000: // 0x3XNN: Skips the next instruction if VX equals NN
      if(myChip8.V[(myChip8.opcode & 0x0F00) >> 8] == (myChip8.opcode & 0x00FF))
        myChip8.pc += 4;
      else
        myChip8.pc += 2;
    break;
    
    case 0x4000: // 0x4XNN: Skips the next instruction if VX doesn't equal NN
      if(myChip8.V[(myChip8.opcode & 0x0F00) >> 8] != (myChip8.opcode & 0x00FF))
        myChip8.pc += 4;
      else
        myChip8.pc += 2;
    break;
    
    case 0x5000: // 0x5XY0: Skips the next instruction if VX equals VY.
      if(myChip8.V[(myChip8.opcode & 0x0F00) >> 8] == myChip8.V[(myChip8.opcode & 0x00F0) >> 4])
        myChip8.pc += 4;
      else
        myChip8.pc += 2;
    break;
    
    case 0x6000: // 0x6XNN: Sets VX to NN.
      myChip8.V[(myChip8.opcode & 0x0F00) >> 8] = myChip8.opcode & 0x00FF;
      myChip8.pc += 2;
    break;
    
    case 0x7000: // 0x7XNN: Adds NN to VX.
      myChip8.V[(myChip8.opcode & 0x0F00) >> 8] += myChip8.opcode & 0x00FF;
      myChip8.pc += 2;
    break;
    
    case 0x8000:
      switch(myChip8.opcode & 0x000F)
      {
        case 0x0000: // 0x8XY0: Sets VX to the value of VY
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] = myChip8.V[(myChip8.opcode & 0x00F0) >> 4];
          myChip8.pc += 2;
        break;

        case 0x0001: // 0x8XY1: Sets VX to "VX OR VY"
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] |= myChip8.V[(myChip8.opcode & 0x00F0) >> 4];
          myChip8.pc += 2;
        break;

        case 0x0002: // 0x8XY2: Sets VX to "VX AND VY"
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] &= myChip8.V[(myChip8.opcode & 0x00F0) >> 4];
          myChip8.pc += 2;
        break;

        case 0x0003: // 0x8XY3: Sets VX to "VX XOR VY"
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] ^= myChip8.V[(myChip8.opcode & 0x00F0) >> 4];
          myChip8.pc += 2;
        break;

        case 0x0004: // 0x8XY4: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't         
          if(myChip8.V[(myChip8.opcode & 0x00F0) >> 4] > (0xFF - myChip8.V[(myChip8.opcode & 0x0F00) >> 8])) 
            myChip8.V[0xF] = 1; //carry
          else 
            myChip8.V[0xF] = 0;         
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] += myChip8.V[(myChip8.opcode & 0x00F0) >> 4];
          myChip8.pc += 2;          
        break;

        case 0x0005: // 0x8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
          if(myChip8.V[(myChip8.opcode & 0x00F0) >> 4] > myChip8.V[(myChip8.opcode & 0x0F00) >> 8]) 
            myChip8.V[0xF] = 0; // there is a borrow
          else 
            myChip8.V[0xF] = 1;         
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] -= myChip8.V[(myChip8.opcode & 0x00F0) >> 4];
          myChip8.pc += 2;
        break;

        case 0x0006: // 0x8XY6: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift
          myChip8.V[0xF] = myChip8.V[(myChip8.opcode & 0x0F00) >> 8] & 0x1;
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] >>= 1;
          myChip8.pc += 2;
        break;

        case 0x0007: // 0x8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
          if(myChip8.V[(myChip8.opcode & 0x0F00) >> 8] > myChip8.V[(myChip8.opcode & 0x00F0) >> 4]) // VY-VX
            myChip8.V[0xF] = 0; // there is a borrow
          else
            myChip8.V[0xF] = 1;
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] = myChip8.V[(myChip8.opcode & 0x00F0) >> 4] - myChip8.V[(myChip8.opcode & 0x0F00) >> 8];        
          myChip8.pc += 2;
        break;

        case 0x000E: // 0x8XYE: Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift
          myChip8.V[0xF] = myChip8.V[(myChip8.opcode & 0x0F00) >> 8] >> 7;
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] <<= 1;
          myChip8.pc += 2;
        break;

      }
    break;
    
    case 0x9000: // 0x9XY0: Skips the next instruction if VX doesn't equal VY
      if(myChip8.V[(myChip8.opcode & 0x0F00) >> 8] != myChip8.V[(myChip8.opcode & 0x00F0) >> 4])
        myChip8.pc += 4;
      else
        myChip8.pc += 2;
    break;

    case 0xA000: // ANNN: Sets I to the address NNN
      myChip8.I = myChip8.opcode & 0x0FFF;
      myChip8.pc += 2;
    break;
    
    case 0xB000: // BNNN: Jumps to the address NNN plus V0
      myChip8.pc = (myChip8.opcode & 0x0FFF) + myChip8.V[0];
    break;
    
    case 0xC000: // CXNN: Sets VX to a random number and NN
      myChip8.V[(myChip8.opcode & 0x0F00) >> 8] = ( random() % 0xFF) & (myChip8.opcode & 0x00FF);
      myChip8.pc += 2;
    break;
  
    case 0xD000: // DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. 
           // Each row of 8 pixels is read as bit-coded starting from myChip8.memory location I; 
           // I value doesn't change after the execution of this instruction. 
           // VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, 
           // and to 0 if that doesn't happen
    {
      unsigned short x = myChip8.V[(myChip8.opcode & 0x0F00) >> 8];
      unsigned short y = myChip8.V[(myChip8.opcode & 0x00F0) >> 4];
      unsigned short height = myChip8.opcode & 0x000F;
      unsigned short pixel;

      myChip8.V[0xF] = 0;
      for (int yline = 0; yline < height; yline++)
      {
        pixel = myChip8.memory[myChip8.I + yline];
        for(int xline = 0; xline < 8; xline++)
        {
          if((pixel & (0x80 >> xline)) != 0)
          {
            if(myChip8.gfx[(x + xline + ((y + yline) * 64))] == 1)
            {
              myChip8.V[0xF] = 1;                                    
            }
            myChip8.gfx[x + xline + ((y + yline) * 64)] ^= 1;
          }
        }
      }
            
      myChip8.drawFlag = TRUE;      
      myChip8.pc += 2;
    }
    break;
      
    case 0xE000:
      switch(myChip8.opcode & 0x00FF)
      {
        case 0x009E: // EX9E: Skips the next instruction if the myChip8.key stored in VX is pressed
          if(myChip8.key[myChip8.V[(myChip8.opcode & 0x0F00) >> 8]] != 0)
            myChip8.pc += 4;
          else
            myChip8.pc += 2;
        break;
        
        case 0x00A1: // EXA1: Skips the next instruction if the myChip8.key stored in VX isn't pressed
          if(myChip8.key[myChip8.V[(myChip8.opcode & 0x0F00) >> 8]] == 0)
            myChip8.pc += 4;
          else
            myChip8.pc += 2;
        break;
      }
    break;
    
    case 0xF000:
      switch(myChip8.opcode & 0x00FF)
      {
        case 0x0007: // FX07: Sets VX to the value of the delay timer
          myChip8.V[(myChip8.opcode & 0x0F00) >> 8] = myChip8.delayTimer;
          myChip8.pc += 2;
        break;
                
        case 0x000A: // FX0A: A myChip8.key press is awaited, and then stored in VX   
        {
          bool keyPress = FALSE;

          for(int i = 0; i < 16; ++i)
          {
            if(myChip8.key[i] != 0)
            {
              myChip8.V[(myChip8.opcode & 0x0F00) >> 8] = i;
              keyPress = TRUE;
            }
          }

          // If we didn't received a myChip8.keypress, skip this cycle and try again.
          if(!keyPress)           
            return;

          myChip8.pc += 2;          
        }
        break;
        
        case 0x0015: // FX15: Sets the delay timer to VX
          myChip8.delayTimer = myChip8.V[(myChip8.opcode & 0x0F00) >> 8];
          myChip8.pc += 2;
        break;

        case 0x0018: // FX18: Sets the sound timer to VX
          myChip8.soundTimer = myChip8.V[(myChip8.opcode & 0x0F00) >> 8];
          myChip8.pc += 2;
        break;

        case 0x001E: // FX1E: Adds VX to I
          if(myChip8.I + myChip8.V[(myChip8.opcode & 0x0F00) >> 8] > 0xFFF) // VF is set to 1 when range overflow (I+VX>0xFFF), and 0 when there isn't.
            myChip8.V[0xF] = 1;
          else
            myChip8.V[0xF] = 0;
          myChip8.I += myChip8.V[(myChip8.opcode & 0x0F00) >> 8];
          myChip8.pc += 2;
        break;

        case 0x0029: // FX29: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font
          myChip8.I = myChip8.V[(myChip8.opcode & 0x0F00) >> 8] * 0x5;
          myChip8.pc += 2;
        break;

        case 0x0033: // FX33: Stores the Binary-coded decimal representation of VX at the addresses I, I plus 1, and I plus 2
          myChip8.memory[myChip8.I]     = myChip8.V[(myChip8.opcode & 0x0F00) >> 8] / 100;
          myChip8.memory[myChip8.I + 1] = (myChip8.V[(myChip8.opcode & 0x0F00) >> 8] / 10) % 10;
          myChip8.memory[myChip8.I + 2] = (myChip8.V[(myChip8.opcode & 0x0F00) >> 8] % 100) % 10;         
          myChip8.pc += 2;
        break;

        case 0x0055: // FX55: Stores V0 to VX in myChip8.memory starting at address I         
          for (int i = 0; i <= ((myChip8.opcode & 0x0F00) >> 8); ++i)
            myChip8.memory[myChip8.I + i] = myChip8.V[i]; 

          // On the original interpreter, when the operation is done, I = I + X + 1.
          myChip8.I += ((myChip8.opcode & 0x0F00) >> 8) + 1;
          myChip8.pc += 2;
        break;

        case 0x0065: // FX65: Fills V0 to VX with values from myChip8.memory starting at address I          
          for (int i = 0; i <= ((myChip8.opcode & 0x0F00) >> 8); ++i)
            myChip8.V[i] = myChip8.memory[myChip8.I + i];     

          // On the original interpreter, when the operation is done, I = I + X + 1.
          myChip8.I += ((myChip8.opcode & 0x0F00) >> 8) + 1;
          myChip8.pc += 2;
        break;

      }
  } 
  // Update timers
  if(myChip8.delayTimer > 0)
    --myChip8.delayTimer;
  if(myChip8.soundTimer > 0)
  {
    if(myChip8.soundTimer == 1)
    --myChip8.soundTimer;
  }
    
}
void initializeSystem(){
  myChip8.pc = 0x200;
  myChip8.opcode = 0;
  myChip8.I=0;
  myChip8.sp=0;
  initFontSet();
  clearMemory();
  clearScreen();
  clearkeys();
  for (int i=0; i<16; i++){
    myChip8.stack[i]=0;
  }
  
  for (int i=0; i<16; i++){
      myChip8.key[i]=0;
  }
}

void clearMemory(){
   for (int i=0; i<4096; i++){
    myChip8.memory[i]=0;
  } 
}
void clearScreen(){
    for (int i=0; i<64*32; i++){
    myChip8.gfx[i]=0;
  }
}


void loadGame(unsigned char *game, u16 gameSize){
  int i;
  for (i=0; i<gameSize; i++){
    myChip8.memory[512+i] = game[i];
  }
}

void clearkeys(){
  for (int i=0; i<16; i++){
    myChip8.key[i]=0;
  }
}

void initFontSet(){
  unsigned char myFontSet[80] = { 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

  for (int i=0; i<80; i++){
     myChip8.fontSet[i]=myFontSet[i];
  }
}


void resetChip8(){
  initializeSystem();
}
