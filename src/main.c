/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/

#define SFX_BEEP 64


#include <genesis.h>
#include "chip8.h"
#include "tileprocessing.h"
#include "resources.h"
#include "input.h"

unsigned char game[224] = {0xa2,0xcd,0x69,0x38,0x6a,0x8,0xd9,0xa3,0xa2,0xd0,0x6b,0x0,0x6c,0x3,0xdb,0xc3,0xa2,0xd6,0x64,0x1d,0x65,0x1f,0xd4,0x51,0x67,0x0,0x68,0xf,0x22,0xa2,0x22,0xac,0x48,0x0,0x12,0x22,0x64,0x1e,0x65,0x1c,0xa2,0xd3,0xd4,0x53,0x6e,0x0,0x66,0x80,0x6d,0x4,0xed,0xa1,0x66,0xff,0x6d,0x5,0xed,0xa1,0x66,0x0,0x6d,0x6,0xed,0xa1,0x66,0x1,0x36,0x80,0x22,0xd8,0xa2,0xd0,0xdb,0xc3,0xcd,0x1,0x8b,0xd4,0xdb,0xc3,0x3f,0x0,0x12,0x92,0xa2,0xcd,0xd9,0xa3,0xcd,0x1,0x3d,0x0,0x6d,0xff,0x79,0xfe,0xd9,0xa3,0x3f,0x0,0x12,0x8c,0x4e,0x0,0x12,0x2e,0xa2,0xd3,0xd4,0x53,0x45,0x0,0x12,0x86,0x75,0xff,0x84,0x64,0xd4,0x53,0x3f,0x1,0x12,0x46,0x6d,0x8,0x8d,0x52,0x4d,0x8,0x12,0x8c,0x12,0x92,0x22,0xac,0x78,0xff,0x12,0x1e,0x22,0xa2,0x77,0x5,0x12,0x96,0x22,0xa2,0x77,0xf,0x22,0xa2,0x6d,0x3,0xfd,0x18,0xa2,0xd3,0xd4,0x53,0x12,0x86,0xa2,0xf8,0xf7,0x33,0x63,0x0,0x22,0xb6,0x0,0xee,0xa2,0xf8,0xf8,0x33,0x63,0x32,0x22,0xb6,0x0,0xee,0x6d,0x1b,0xf2,0x65,0xf0,0x29,0xd3,0xd5,0x73,0x5,0xf1,0x29,0xd3,0xd5,0x73,0x5,0xf2,0x29,0xd3,0xd5,0x0,0xee,0x1,0x7c,0xfe,0x7c,0x60,0xf0,0x60,0x40,0xe0,0xa0,0xf8,0xd4,0x6e,0x1,0x6d,0x10,0xfd,0x18,0x0,0xee, };

int main()
{
    XGM_setPCM(SFX_BEEP , sfx_beep, sizeof(sfx_beep));

    int counter = 60;
    initJoyHandler();
    initTiles();
    initializeSystem();
    loadGame(game,224);
    while(1)
    {
      emulationCycle();
      if (counter==0 && myChip8.drawFlag){
        processGraphics(myChip8.gfx);
        myChip8.drawFlag = FALSE;
        counter=60;
      }
      counter--;
    }
    return (0);
}

