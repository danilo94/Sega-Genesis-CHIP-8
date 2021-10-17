#ifndef TILES_INCLUDE_H
#define TILES_INCLUDE_H
#include "types.h"
#include "chip8.h"
#include "tileprocessing.h"
#include "input.h"

#define MENU_OPTIONS 3
typedef struct 
{
    bool gameInProgress ;
    u16 timeCounter;
    u8 selectedOption;
    Sprite *cursor;
    /* data */
}gameController;


typedef struct {
    u16 x;
    u16 y;
    char label[20];
}menuOption;

gameController myGameController;

menuOption myMenuOption[MENU_OPTIONS];

void initGameController();
void initMenu();
void loadMenu();
void selectGame();
void runGame();
void moveMenuCursor(u8 movement);
void moveCursorUp();
void moveCursorDown();
void clearChipFrame();


#endif